/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 01:16:49 by yvanat            #+#    #+#             */
/*   Updated: 2019/12/16 06:00:55 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

t_vec	retray(t_vec r, t_vec n)
{
	return (sub_vec(mult_vec_d(mult_vec_d(n, prod_scal(r, n)), 2), r));
}

t_inter intertr(t_ray ray, void *ptr, double start, double max)
{
	t_tr tr;
	t_inter rt;

	tr = *(t_tr*)ptr;
	(void)ray;
	(void)start;
	(void)max;
	rt.inter = 0;
	return (rt);
}

t_inter	interpl(t_ray ray, void *ptr, double start, double max)
{
	t_pl pl;
	t_inter rt;

	pl = *(t_pl*)ptr;
	rt.inter = (pl.a * pl.p.x + pl.b * pl.p.y + pl.c * pl.p.z) / (pl.a * ray.dir.x + pl.b * ray.dir.y + pl.c * ray.dir.z);
	rt.color = pl.color;
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
	rt.spec = sp.spec;
	rt.reflect = sp.reflect;
	if (rt.inter < start || rt.inter > max)
		rt.inter = 0;
	rt.ipoint = add_vec(ray.o, mult_vec_d(ray.dir, rt.inter));
	rt.normal = normalize(sub_vec(rt.ipoint, sp.o));
	return (rt);
}

t_inter	min_inter(t_ray ray, t_p p, double start, double max)
{
	t_inter min;
	t_inter inter;
	int j;

	j = -1;

	min.color = p.bg_color;
	min.inter = max;
	while (++j < p.nb_objs)
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
	double max;

	i = create_vec(0, 0, 0);
	l = light.type == POINT ? sub_vec(light.pos, ipoint) : light.pos;
	max = light.type == POINT ? norm_vec(l) : __DBL_MAX__;
	shadow.o = ipoint;
	shadow.dir = l;
	closest = min_inter(shadow, p, MIN_D, max);
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
	t_inter min;
	int i;
	int color;

	i = -1;
	intensity = create_vec(0.0, 0.0, 0.0);
	min = min_inter(ray, p, MIN_D, __DBL_MAX__);
	if (!min.inter)
		return (p.bg_color);
	while (++i < p.nb_lights)
	{
		intensity = add_vec(intensity, ((p.lights[i].type != AMBIENT) ? light_intensity(min.ipoint, min.normal, p.lights[i], p, min.spec, mult_vec_d(ray.dir, -1)) : mult_vec_d(div_vec(p.lights[i].rgb, create_vec(255, 255, 255)), p.lights[i].intensity)));
	}
	color = prod_color_vec(min.color, intensity);
	if (!depth || min.reflect <= 0)
		return (color);
	ray.dir = retray(mult_vec_d(ray.dir, -1), min.normal);
	ray.o = min.ipoint;
	return (add_color_to_color(prod_color_float(color, 1 - min.reflect), prod_color_float(find_pix_color(ray, p, depth - 1), min.reflect)));
}

t_vec	c_to_vp(double i, double j, t_vp vp, double dist)
{
	t_vec dir;
	int mid;

	mid = vp.res_x < vp.res_y ? vp.res_x : vp.res_y;
	dir.x = (j - vp.res_x / 2.0) * (VP_W / mid);
	dir.y = (vp.res_y / 2.0 - i) * (VP_H / mid);
	dir.z = dist;
	return (normalize(dir));
}

t_vec cam_rot(t_vec dir, t_vec cam)
{
	t_vec rotate;
	double theta = 0;
	int boo;

	boo = 0;
	if (cam.z < 0)
	{
		boo = 1;
		cam.z *= -1;
		mult_vec_d(dir, -1);
	}
	theta = acos(cam.z / sqrt(cam.y * cam.y + cam.z * cam.z));
	if (cam.y < 0)
		theta *= -1;
	rotate.x = dir.x;
	rotate.z = cos(theta) * dir.z - sin(theta) * dir.y;
	rotate.y = sin(theta) * dir.z + cos(theta) * dir.y;
	theta = acos(cam.z / sqrt(cam.x * cam.x + cam.z * cam.z));
	if (cam.x < 0)
		theta *= -1;
	rotate.x += cos(theta) * dir.x - sin(theta) * dir.z;
	rotate.z += sin(theta) * dir.x + cos(theta) * dir.z;
	rotate.y += dir.y;
	// on peut rajouter la rotate en z ici
	if (boo)
		rotate.z *= -1;
	return(normalize(rotate));
}

int abs(int nb)
{
	return (nb >= 0 ? nb : -nb);
}

int		check_diff(int i, int j, int *tab, int len, double delta)
{
	int k;
	int m;

	k = -2;
	while (++k < 2)
	{
		m = -2;
		while (++m < 2)
			if (comp_cols(tab[(i - k) * len + (j - m)], tab[i * len + j], delta) == -1)
				return (-1);
	}
	return (0);
}

int recalc_img(int i, int j, t_p p, int actualpix, int i_img)
{
	int nb;
	nb = ((p.bonus.coeff_aliasing * 2) - 1) * ((p.bonus.coeff_aliasing * 2) - 1);
	int *color;
	t_ray ray;
	int k;
	int m;
	int n;

	if (!(color = malloc(nb * sizeof(int))))
		exit (0);
	n = 0;
	ray.o = p.cam[i_img].o;
	k = -p.bonus.coeff_aliasing;
	while (++k < p.bonus.coeff_aliasing)
	{
		m = -p.bonus.coeff_aliasing;
		while (++m < p.bonus.coeff_aliasing)
		{
			if (k || m)
			{
				ray.dir = c_to_vp((double)(((double)k / (p.bonus.coeff_aliasing) * 2)) + i, (double)(j + ((double)m / (p.bonus.coeff_aliasing * 2))), p.vp, p.cam[i_img].dist);
				color[n] = find_pix_color(ray, p, p.bonus.recurse_reflect);
			}
			else
				color[n] = actualpix;
			n++;
		}
	}
	return (mid_color(color, nb));
}

void		aliasing(int *img, int len, t_p p, int i_img)
{
	int i;
	int j;
	i = 0;
	while (++i < p.vp.res_y - 1)
	{
		j = 0;
		while (++j < p.vp.res_x - 1)
			if (check_diff(i, j, img, len, p.bonus.delta_aliasing) == -1)
				img[i * len + j] = recalc_img(i, j, p, img[i * len + j], i_img);
	}
}
void	fill_img(int *img, t_info info, t_p p, int i_img)
{
	int i;
	int j;
	t_ray ray;
	int len;
	 
	len = info.l / 4;
	i = -1;
	ray.o = p.cam[i_img].o;
	while (++i < p.vp.res_y)
	{
		j = -1;
		while (++j < p.vp.res_x)
		{
			ray.dir = cam_rot(c_to_vp((double)i, (double)j, p.vp, p.cam[i_img].dist), p.cam[i_img].vec_dir);
			img[i * len + j] = find_pix_color(ray, p, p.bonus.recurse_reflect);
		}
	}
	if (p.bonus.coeff_aliasing)
		aliasing(img, len, p, i_img);
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
	if (!argv[1] || argc > 2)
		exit (error(NULL, "manque ou surplus d'args \n"));
	if (get_p(&p, argv[1]) == -1)
		return (-1);
	/*int i = -1;
	printf("res : %d %d\n", p.vp.res_x, p.vp.res_y);
	while (++i < p.nb_lights)
	printf("light %d : %f %f %f		%f		%f %f %f	%d	%x\n", i, p.lights[i].pos.x, p.lights[i].pos.y, p.lights[i].pos.z, p.lights[i].intensity, p.lights[i].rgb.x, p.lights[i].rgb.y, p.lights[i].rgb.z, p.lights[i].type,p.lights[i].color);
	*//*cam %d : %f %f %f		%f %f %f		%f %f %f\n", i, p.ob.x, p.cam[i].o.y, p.cam[i].o.z, p.cam[i].fov, p.cam[i].vec_dir.x, p.cam[i].vec_dir.y, p.cam[i].vec_dir.z);
	*///int i = -1;
		//printf("obj : %f %f %f %d	%x\n", ((t_tr*)(p.objs[5].o))->ang3.x, ((t_tr*)(p.objs[5].o))->ang3.y, ((t_tr*)(p.objs[5].o))->ang3.z, p.objs[5].type, ((t_tr*)(p.objs[5].o))->color);
	if ((mlx.win = mlx_new_window(mlx.ptr, p.vp.res_x, p.vp.res_y, "RT")))
	{
		if (!(mlx.img = mlx_new_image(mlx.ptr, p.vp.res_x, p.vp.res_y)))
			return (-1);
		if (!(img = (int*)mlx_get_data_addr(mlx.img, &(info.n), &(info.l) , &(info.e))))
			return (-1);
		fill_img(img, info, p, 0);
		mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img, 0, 0);
		mlx_key_hook(mlx.win, &quit, &mlx);
		mlx_loop(mlx.ptr);
	}
	return (0);
}
