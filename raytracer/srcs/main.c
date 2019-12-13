/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 05:55:14 by mbrunel           #+#    #+#             */
/*   Updated: 2019/12/13 02:04:07 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

int get_p(t_p *p, char *path)
{
	int fd;
	int status;
	int type;
	int incs[7];
	char *buf;

	if (!(fd = open(path, O_RDONLY)))
		return error(NULL, "open_eror\n");
	ft_memset(incs, 0, sizeof(int) * 6);
	while ((status = get_next_line(fd, &buf)) > 0 && ++incs[LINES_OF_FILE] < MAX_LENGTHG_FILE)
	{
		if ((type = (chr("spRlAc", buf[0]))) == -1)
			return (error(buf, "object not found in database\n"));
		else if (type == RESOLUTION)
			if (incs[RESOLUTION] || get_vp(buf, &(p->vp)) == -1)
				return (error(buf, "the vp is badly registered\n"));
		else if (type == AMBIANTE || type == LIGHT)
			if (incs[AMBIANTE] || get_lights(buf, &(p->lights[incs[AMBIANTE] + incs[LIGHT]]), type) == -1)
				return (error(buf, "light parameters are badly registered\n"));
		else if (type == CAMERA)
			if (get_cam(buf, &(p->cam[incs[CAMERA]])) == -1)
				return (error(buf, "camera parameters are badly registered\n"));
		else
		{
			if ((get_obj[type])(buf, &(p->objs[incs[type]].o)) == -1)
				return (error(buf, "objs parameters are badly registered\n"));
			p->objs[incs[type]].type = type;
		}
		incs[type]++;
	}
	return (0);
}

t_vec	normalray(t_vec r, t_vec n)
{
	return (sub_vec(mult_vec_d(mult_vec_d(n, prod_scal(r, n)), 2), r));
}

t_inter	interpl(t_ray ray, void *ptr, double start, double max)
{
	t_pl pl;
	t_inter rt;

	pl = *(t_pl*)ptr;
	rt.inter = (pl.a * pl.p.x + pl.b * pl.p.y + pl.c * pl.p.z) / (pl.a * ray.dir.x + pl.b * ray.dir.y + pl.c * ray.dir.z);
	rt.color = pl.color;
	rt.o = pl.p;
	if (rt.inter < start || rt.inter > max)
		rt.inter = 0;
	return (rt);
}

t_inter intersp(t_ray ray, void *ptr, double start, double max)
{
	double t1;
	double t2;
	double a;
	double b;
	double c;
	double dis;
	t_inter rt;
	t_sp sp;
	t_vec oc;
	
	sp = *(t_sp*)ptr;
	oc = sub_vec(ray.o, sp.o);
	a = prod_scal(ray.dir, ray.dir);
	b = 2 * prod_scal(oc, ray.dir);
	c = prod_scal(oc, oc) - sp.r * sp.r;
	dis = b * b - 4 * a * c;
	if (dis > 0)
	{
		t1 = (-b + sqrt(dis)) / (2 * a);
		t2 = (-b - sqrt(dis)) / (2 * a);
		rt.inter = t1 < t2 ? t1 : t2;
	}
	else if (dis == 0)
		rt.inter = -b / 2 * a;
	else
		rt.inter = 0;
	rt.color = sp.color;
	rt.o = sp.o;
	rt.spec = sp.spec;
	rt.reflect = sp.reflect;
	if (rt.inter < start || rt.inter > max)
		rt.inter = 0;
	return (rt);
}

t_inter	min_inter(t_ray ray, t_p p, double start, double max)
{
	t_inter min;
	t_inter inter;
	int j;

	j = -1;

	min.color = BACKGROUND_COLOR;
	min.inter = max;
	while (p.objs[++j].o)
	{
		inter = (get_inter[p.objs[j].type])(ray, p.objs[j].o, start, max);
		if (inter.inter < min.inter && inter.inter > start)
			min = inter;
	}
	min.inter = (min.inter == max ? 0 : min.inter);
	return (min);
}

t_vec	light_intensity(t_vec ipoint, t_vec normal, t_light light, t_p p, double spec, t_vec invray)
{
	t_vec i;
	double coeff;
	double	p_scal;
	t_vec	l;
	t_inter closest;
	t_ray shadow;

	i = create_vec(0, 0, 0);
	l = sub_vec(light.pos, ipoint);
	shadow.o = ipoint;
	shadow.dir = l;
	closest = min_inter(shadow, p, 0.0000001, norm_vec(l));
	if (closest.inter)
		return (i);
	p_scal = prod_scal(normal, l);
	if (p_scal > 0)
	{
		coeff = light.intensity * p_scal / (norm_vec(normal) * norm_vec(l));
		i = create_vec(coeff * light.rgb.x / 255, coeff * light.rgb.y / 255, coeff * light.rgb.z / 255);
	}
	if (spec != -1)
	{
		l = sub_vec(mult_vec_d(mult_vec_d(normal, prod_scal(normal, l)), 2), l); 
		if ((p_scal = prod_scal(l, invray)) > 0)
		{
			coeff = light.intensity * pow(p_scal / (norm_vec(l) * norm_vec(invray)), spec);
			i = add_vec(i, mult_vec_d(i, coeff));
		}
	}
	return (i);
}

int		find_pix_color(t_ray ray, t_p p, int depth)
{
	t_vec intensity;
	t_vec ipoint;
	t_inter min;
	t_vec normal;
	int i;
	int color;

	i = -1;
	intensity = create_vec(0.0, 0.0, 0.0);
	min = min_inter(ray, p, 0.000000000001, __DBL_MAX__);
	if (!min.inter)
		return (BACKGROUND_COLOR);
	ipoint = add_vec(ray.o, mult_vec_d(ray.dir, min.inter));
	normal = normalize(sub_vec(ipoint, min.o));
	while (++i < NB_LIGHT)
	{
		intensity = add_vec(intensity, ((p.lights[i].type == POINT) ? light_intensity(ipoint, normal, p.lights[i], p, min.spec, mult_vec_d(ray.dir, -1)) : mult_vec_d(div_vec(p.lights[i].rgb, create_vec(255, 255, 255)), p.lights[i].intensity)));
	}
	color = prod_color_vec(min.color, intensity);
	if (!depth || min.reflect <= 0)
		return (color);
	ray.dir = normalray(mult_vec_d(ray.dir, -1), normal);
	ray.o = ipoint;
	return (add_color_to_color(prod_color_float(color, 1 - min.reflect), prod_color_float(find_pix_color(ray, p, depth - 1), min.reflect)));
}

t_vec	c_to_vp(int i, int j)
{
	t_vec dir;

	dir.x = (j - RES_X / 2.0) * (VP_W / MEDIUM);
	dir.y = (RES_Y / 2.0 - i) * (VP_H / MEDIUM);
	dir.z = VP_D;
	return (dir);
}

t_vec cam_rot()
{
	t_vec rotate;

	rotate.x = 1;
	rotate.y = 1;
	rotate.z = 1; 
	return(rotate);
}

void	fill_img(int *img, t_info info, t_p p)
{
	int i;
	int j;
	t_ray ray;
	int len;
	 
	len = info.l / 4;
	i = -1;
	ray.o = p.cam[0].o;
	
	while (++i < RES_Y)
	{
		j = -1;
		while (++j < RES_X)
		{
			ray.dir = mult_vec(c_to_vp(i, j), cam_rot());
			img[i * len + j] = find_pix_color(ray, p, RECURS_DEPTH);
		}
	}
}

int quit(t_mlx *mlx)
{
	(void)mlx;
	exit(0);
}

int		main(int argc, char *argv[])
{
	t_mlx	mlx;
	t_info	info;
	t_p		p;
	int 	*img;

	mlx.ptr = mlx_init();
	if (!(argv[1] && !get_p(&p, argv[1])))
		exit (0);
	if ((mlx.win = mlx_new_window(mlx.ptr, RES_X, RES_Y, "RT")))
	{
		if (!(mlx.img = mlx_new_image(mlx.ptr, RES_X, RES_Y)))
			return (-1);
		if (!(img = (int*)mlx_get_data_addr(mlx.img, &(info.n), &(info.l) , &(info.e))))
			return (-1);
		fill_img(img, info, p);
		mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
		mlx_key_hook(mlx.win, &quit, &mlx);
		mlx_loop(mlx.ptr);
	}
	return (0);
}
