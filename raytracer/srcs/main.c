/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 05:55:14 by mbrunel           #+#    #+#             */
/*   Updated: 2019/12/11 22:22:20 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"


void get_p(t_p *p)
{
	t_sp *sp1;
	t_sp *sp2;
	t_sp *sp3;
	t_sp *sp4;
	t_pl *pl1;/*
	t_pl *pl2;*/

	sp1 = malloc(sizeof(t_sp));
	sp2 = malloc(sizeof(t_sp));
	sp3 = malloc(sizeof(t_sp));
	sp4 = malloc(sizeof(t_sp));
	pl1 = malloc(sizeof(t_pl));
	/*pl2 = malloc(sizeof(t_pl));*/

	sp1->r = 1.0;
	sp1->o.x = 0.0; //sphere 1
	sp1->o.y = -1.0;
	sp1->o.z = 3.0;
	sp1->color = 0xff0000;

	sp2->r = 1.0;
	sp2->o.x = 2.0; // sphere 2
	sp2->o.y = 0.0;
	sp2->o.z = 4.0;
	sp2->color = 0xff;
	
	sp3->r = 1.0;
	sp3->o.x = -2.0; // sphere 3
	sp3->o.y = 0.0;
	sp3->o.z = 4.0;
	sp3->color = 0x00ff00;

	sp4->r = 5000;
	sp4->o.x = 0.0; // sphere 
	sp4->o.y = -5001.0;
	sp4->o.z = 0.0;
	sp4->color = 0xffff00;

	pl1->a = 0;
	pl1->b = 1;
	pl1->c = 0;
	pl1->d = 0; 	// plan1
	pl1->p.x = 0;
	pl1->p.y = 1;
	pl1->p.z = 0;
	pl1->color = 0xff00ff;/*

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
	/*p->objs[4].o = pl1;
	p->objs[4].type = PLANE;*/
/*
	p->objs[4].o = pl2;
	p->objs[4].type = PLANE;*/

	p->objs[4].o = NULL;

	p->lights[0].intensity = 0.2;
	p->lights[0].type = AMBIENT;

	p->lights[1].intensity = 0.6;
	p->lights[1].type = POINT;
	p->lights[1].pos.x = 2;
	p->lights[1].pos.y = 1;
	p->lights[1].pos.z = 0;

	p->lights[2].intensity = 0.2;
	p->lights[2].type = POINT;
	p->lights[2].pos.x = 1;
	p->lights[2].pos.y = 4;
	p->lights[2].pos.z = 4;
}

t_inter	interpl(t_ray ray, void *ptr)
{
	t_pl pl;
	t_inter rt;

	pl = *(t_pl*)ptr;
	rt.inter = -1 * ((pl.a * pl.p.x + pl.b * pl.p.y + pl.c * pl.p.z) / (pl.a * ray.dir.x + pl.b * ray.dir.y + pl.c * ray.dir.z));
	rt.color = pl.color;
	rt.o = pl.p;
	return (rt);
}

t_inter intersp(t_ray ray, void *ptr)
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
	mult_vec_d(ray.dir, -1);
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
	return (rt);
}

double	light_intensity(t_vec ipoint, t_vec normal, t_light light)
{
	double	i;
	double	p_scal;
	t_vec	l;

	i = 0.0;
	l = sub_vec(light.pos, ipoint);
	p_scal = prod_scal(normal, l);
	if (p_scal > 0)
		i = light.intensity * p_scal / (norm_vec(normal) * norm_vec(l));
	return (i);
}

int		get_color(int objcol, double i)
{
	int rt;
	int r;
	int g;
	int b;

	r = (objcol & 0xFF0000) >> 16;
	g = (objcol & 0x00FF00) >> 8;
	b = (objcol & 0x0000FF);
	rt = 0;
	rt |= (int)(r * i) << 16;
	rt |= (int)(g * i) << 8;
	rt |= (int)(b * i);
	return (rt);
}

void	fill_img(int *img, t_info info, t_p p)
{
	int i;
	int j;
	int k;
	t_ray ray;
	t_inter inter;
	t_inter min;
	double intensity;
	t_vec ipoint;
	t_vec normal;
	int len = info.l / 4;

	i = -1;
	ray.o = p.cam.o;
	ray.dir.z = VP_D / 4;
	while (++i < RES_Y)
	{
		k = -1;
		while (++k < len)
		{
			ray.dir.x = (k - len / 2.0) * (VP_W / MEDIUM);
			ray.dir.y = -1 * (i - RES_Y / 2.0) * (VP_H / MEDIUM);
			j = -1;
			min.color = BACKGROUND_COLOR;
			min.inter = __DBL_MAX__;
			while (p.objs[++j].o)
			{
				inter = (get_inter[p.objs[j].type])(ray, p.objs[j].o);
				if (inter.inter < min.inter && inter.inter >= 1)
					min = inter;
			}
			if (min.inter != __DBL_MAX__)
			{
				ipoint = add_vec(ray.o, mult_vec_d(ray.dir, min.inter));
				normal = normalize(sub_vec(ipoint, min.o));
				j = -1;
				intensity = 0.0;
				while (++j < NB_LIGHT)
					intensity += ((p.lights[j].type == POINT) ? light_intensity(ipoint, normal, p.lights[j]) : p.lights[j].intensity);
				img[i * len + k] = get_color(min.color, intensity > 1 ? 1 : intensity);
			}
			else
				img[i * len + k] = BACKGROUND_COLOR;
		}
	}
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
