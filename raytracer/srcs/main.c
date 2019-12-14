/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 05:55:14 by mbrunel           #+#    #+#             */
/*   Updated: 2019/12/13 10:22:16 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"


void get_p(t_p *p)
{
	t_sp *sp1;
	t_sp *sp2;
	t_sp *sp3;
	t_sp *sp4;
	t_sp *sp5;
	t_pl *pl1;/*
	t_pl *pl2;*/

	sp1 = malloc(sizeof(t_sp));
	sp2 = malloc(sizeof(t_sp));
	sp3 = malloc(sizeof(t_sp));
	sp4 = malloc(sizeof(t_sp));
	sp5 = malloc(sizeof(t_sp));
	pl1 = malloc(sizeof(t_pl));
	/*pl2 = malloc(sizeof(t_pl));*/

	sp1->r = 1.0;
	sp1->o.x = 0.0; //sphere 1
	sp1->o.y = -1.0;
	sp1->o.z = 3.0;
	sp1->color = 0xda7010;
	sp1->spec = 10;
	sp1->reflect = 0.05;

	sp2->r = 1.0;
	sp2->o.x = 2.0; // sphere 2
	sp2->o.y = 0.0;
	sp2->o.z = 4.0;
	sp2->color = 0xfff00f;
	sp2->spec = 20;
	sp2->reflect = 0.1;
	
	sp3->r = 1.0;
	sp3->o.x = -2.0; // sphere 3
	sp3->o.y = 0.0;
	sp3->o.z = 4.0;
	sp3->color = 0xf0f0ff;
	sp3->spec = 10;
	sp3->reflect = 0.05;

	sp4->r = 5000;
	sp4->o.x = 0.0; // sphere 
	sp4->o.y = -5001.0;
	sp4->o.z = 0.0;
	sp4->color = 0xffffff;
	sp4->spec = 1000;
	sp4->reflect = 0.15;

	sp5->r = 5000;
	sp5->o = create_vec(0,0,5250);
	sp5->color = 0xff;
	sp5->spec = 0;
	sp5->reflect = 0; 

	/*pl1->a = 0;
	pl1->b = 1;
	pl1->c = 0;
	pl1->d = 0; 	// plan1
	pl1->p.x = 0;
	pl1->p.y = -10;
	pl1->p.z = 0;
	pl1->color = 0xffffff;

	pl2->a = 0;
	pl2->b = 1;
	pl2->c = 0;
	pl2->d = 0; 	// plan2
	pl2->p.x = 0;
	pl2->p.y = -100;
	pl2->p.z = 0;
	pl2->color = 0xffff;*/

	p->cam.o.x = 0;
	p->cam.o.y = 0;  //cam1
	p->cam.o.z = 0;

	p->objs[0].o = sp1;
	p->objs[0].type = SPHERE;

	p->objs[1].o = sp2;
	p->objs[1].type = SPHERE;

	p->objs[2].o = sp3;
	p->objs[2].type = SPHERE;

	p->objs[3].o = sp4;
	p->objs[3].type = SPHERE;
	p->objs[4].o = sp5;
	p->objs[4].type = SPHERE;
/*
	p->objs[4].o = pl2;
	p->objs[4].type = PLANE;*/

	p->objs[5].o = NULL;

	p->lights[0].intensity = 0.2;
	p->lights[0].type = AMBIENT;
	p->lights[0].rgb = create_vec(255, 255, 255);

	p->lights[1].intensity = 0.0;
	p->lights[1].type = POINT;
	p->lights[1].pos.x = 2;
	p->lights[1].pos.y = 4;
	p->lights[1].pos.z = 0;
	p->lights[1].rgb = create_vec(0, 0, 255);

	p->lights[2].intensity = 0.3;
	p->lights[2].type = POINT;
	p->lights[2].pos.x = 2;
	p->lights[2].pos.y = 1;
	p->lights[2].pos.z = 0;
	p->lights[2].rgb = create_vec(0,255, 0);

	p->lights[3].intensity = 0.3;
	p->lights[3].type = POINT;
	p->lights[3].pos.x = -2;
	p->lights[3].pos.y = 1;
	p->lights[3].pos.z = 1;
	p->lights[3].rgb = create_vec(255 ,0, 0);

	p->lights[4].intensity = 0.2;
	p->lights[4].type = DIRECTIONAL;
	p->lights[4].pos.x = 0;
	p->lights[4].pos.y = 8;
	p->lights[4].pos.z = -1;
	p->lights[4].rgb = create_vec(127,0,127);
}

t_vec	retray(t_vec r, t_vec n)
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

int		prod_color_float(int objcol, double i)
{
	int rt;

	rt = 0;
	rt |= (int)(((objcol & 0xFF0000) >> 16) * i) << 16;
	rt |= (int)(((objcol & 0x00FF00) >> 8) * i) << 8;
	rt |= (int)((objcol & 0x0000FF) * i);
	return (rt);
}

int		add_color_to_color(int col1, int col2)
{
	int rt;

	rt = 0;
	rt |= ((((col1 & 0xFF0000) >> 16) + ((col2 & 0xFF0000) >> 16))) << 16;
	rt |= ((((col1 & 0x00FF00) >> 8) + ((col2 & 0x00FF00) >> 8))) << 8;
	rt |= ((col1 & 0x0000FF) + (col2 & 0x0000FF));
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
	double max;

	i = create_vec(0, 0, 0);
	l = light.type == POINT ? sub_vec(light.pos, ipoint) : light.pos;
	max = light.type == POINT ? norm_vec(l) : __DBL_MAX__;
	shadow.o = ipoint;
	shadow.dir = l;
	closest = min_inter(shadow, p, 0.0000001, max);
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

int prod_color_vec(int objcol, t_vec i)
{
	int rt;

	rt = 0;
	rt |= (int)(((objcol & 0xFF0000) >> 16) * (i.x > 1 ? 1 : i.x)) << 16;
	rt |= (int)(((objcol & 0x00FF00) >> 8) * (i.y > 1 ? 1 : i.y)) << 8;
	rt |= (int)((objcol & 0x0000FF) * (i.z > 1 ? 1 : i.z));
	return (rt);
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
		intensity = add_vec(intensity, ((p.lights[i].type != AMBIENT) ? light_intensity(ipoint, normal, p.lights[i], p, min.spec, mult_vec_d(ray.dir, -1)) : mult_vec_d(div_vec(p.lights[i].rgb, create_vec(255, 255, 255)), p.lights[i].intensity)));
	}
	color = prod_color_vec(min.color, intensity);
	if (!depth || min.reflect <= 0)
		return (color);
	ray.dir = retray(mult_vec_d(ray.dir, -1), normal);
	ray.o = ipoint;
	return (add_color_to_color(prod_color_float(color, 1 - min.reflect), prod_color_float(find_pix_color(ray, p, depth - 1), min.reflect)));
}

t_vec	c_to_vp(double i, double j)
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

int abs(int nb)
{
	return (nb >= 0 ? nb : -nb);
}

int		comp_cols(int col1, int col2)
{
	t_vec rgb;

	rgb.x = abs(((col1 & 0xFF0000) >> 16) - ((col2 & 0xFF0000) >> 16));
	rgb.y = abs(((col1 & 0x00FF00) >> 8) - ((col2 & 0x00FF00) >> 8));
	rgb.z = abs(((col1 & 0x0000FF) - (col2 & 0x0000FF)));
	if (norm_vec(rgb) > DELTA)
		return (-1);
	return (0);
}

int		check_diff(int i, int j, int *tab, int len)
{
	int k;
	int m;

	k = -2;
	while (++k < 2)
	{
		m = -2;
		while (++m < 2)
			if (comp_cols(tab[(i - k) * len + (j - m)], tab[i * len + j]) == -1)
				return (-1);
	}
	return (0);
}

int get_clr_int(int r, int g, int b)
{
	int rt;

	rt = 0;
	rt |= r << 16;
	rt |= g << 8;
	return (rt |= b);
}

int mid_color(int *color)
{
	int r;
	int g;
	int b;
	int i;
	int nb_ray;

	nb_ray = ((COEFF_ALIASING * 2) - 1) * ((COEFF_ALIASING * 2) - 1);
	r = 0;
	g = 0;
	b = 0;
	i = -1;
	while (++i < nb_ray)
	{
		r += (color[i] & 0xFF0000) >> 16;
		g += (color[i] & 0x00FF00) >> 8;
		b += color[i] & 0x0000FF;
	}
	return (get_clr_int(r / nb_ray, g / nb_ray, b / nb_ray));
}

int recalc_img(int i, int j, t_p p, int actualpix)
{
	int color[((COEFF_ALIASING * 2) - 1) * ((COEFF_ALIASING * 2) - 1)];
	t_ray ray;
	int k;
	int m;
	int n;

	n = 0;
	ray.o = p.cam.o;
	k = -COEFF_ALIASING;
	while (++k < COEFF_ALIASING)
	{
		m = -COEFF_ALIASING;
		while (++m < COEFF_ALIASING)
		{
			if (k || m)
			{
				ray.dir = c_to_vp((double)(((double)k / (COEFF_ALIASING * 2)) + i), (double)(j + ((double)m / (COEFF_ALIASING * 2))));
				color[n] = find_pix_color(ray, p, RECURS_DEPTH);
			}
			else
				color[n] = actualpix;
			n++;
		}
	}
	return (mid_color(color));
}

void		aliasing(int *img, int len, t_p p)
{
	int i;
	int j;
	i = 0;
	while (++i < RES_Y - 1)
	{
		j = 0;
		while (++j < RES_X - 1)
			if (check_diff(i, j, img, len) == -1)
				img[i * len + j] = recalc_img(i, j, p, img[i * len + j]);
	}
}
void	fill_img(int *img, t_info info, t_p p)
{
	int i;
	int j;
	t_ray ray;
	int len;
	 
	len = info.l / 4;
	i = -1;
	ray.o = p.cam.o;
	while (++i < RES_Y)
	{
		j = -1;
		while (++j < RES_X)
		{
			ray.dir = mult_vec(c_to_vp((double)i, (double)j), cam_rot());
			img[i * len + j] = find_pix_color(ray, p, RECURS_DEPTH);
		}
	}
	aliasing(img, len, p);
}

int quit(t_mlx *mlx)
{
	(void)mlx;
	exit(0);
}

int		main()
{
	t_mlx	mlx;
	t_info	info;
	t_p		p;
	int 	*img;

	mlx.ptr = mlx_init();
	get_p(&p);
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
