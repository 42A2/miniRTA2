/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 05:55:14 by mbrunel           #+#    #+#             */
/*   Updated: 2019/12/11 03:36:02 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"


void get_p(t_p *p)
{
	t_sp *sp1;
	t_sp *sp2;
	t_sp *sp3;
	t_pl *pl1;
	t_pl *pl2;

	sp1 = malloc(sizeof(t_sp));
	sp2 = malloc(sizeof(t_sp));
	sp3 = malloc(sizeof(t_sp));
	pl1 = malloc(sizeof(t_pl));
	pl2 = malloc(sizeof(t_pl));

	sp1->r = 5;
	sp1->o.x = 0; //sphere 1
	sp1->o.y = 0;
	sp1->o.z = 45;
	sp1->color = 0xff0000;

	sp2->r = 5;
	sp2->o.x = 0; // sphere 2
	sp2->o.y = 10;
	sp2->o.z = 45;
	sp2->color = 0x0000ff;
	
	sp3->r = 5;
	sp3->o.x = 10; // sphere 3
	sp3->o.y = 0;
	sp3->o.z = 45;
	sp3->color = 0x00ff00;

	pl1->a = 0;
	pl1->b = 1;
	pl1->c = 0;
	pl1->d = 0; 	// plan1
	pl1->p.x = 0;
	pl1->p.y = 100;
	pl1->p.z = 0;
	pl1->color = 0xff00ff;

	pl2->a = 0;
	pl2->b = 1;
	pl2->c = 0;
	pl2->d = 0; 	// plan2
	pl2->p.x = 0;
	pl2->p.y = -100;
	pl2->p.z = 0;
	pl2->color = 0xffff;

	p->cam.o.x = 0;
	p->cam.o.y = 0;  //cam1
	p->cam.o.z = 0;

	p->objs[0].o = sp1;
	p->objs[0].type = SPHERE;

	p->objs[1].o = sp2;
	p->objs[1].type = SPHERE;

	p->objs[2].o = sp3;
	p->objs[2].type = SPHERE;

	p->objs[3].o = pl1;
	p->objs[3].type = PLANE;

	p->objs[4].o = pl2;
	p->objs[4].type = PLANE;

	p->objs[5].o = NULL;
}

t_inter	interpl(t_ray ray, void *ptr)
{
	t_pl pl;
	t_inter rt;

	pl = *(t_pl*)ptr;
	rt.inter = -1 * ((pl.a * pl.p.x + pl.b * pl.p.y + pl.c * pl.p.z) / (pl.a * ray.dir.x + pl.b * ray.dir.y + pl.c * ray.dir.z));
	rt.color = pl.color;
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
	
	sp = *(t_sp*)ptr;
	a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y + ray.dir.z * ray.dir.z;
	b = 2 * (ray.dir.x * (ray.o.x - sp.o.x) + ray.dir.y * (ray.o.y - sp.o.y) + ray.dir.z * (ray.o.z - sp.o.z));
	c = (ray.o.x - sp.o.x) * (ray.o.x - sp.o.x) + (ray.o.y - sp.o.y) * (ray.o.y - sp.o.y) + (ray.o.z - sp.o.z) * (ray.o.z - sp.o.z) - sp.r * sp.r;
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
	return (rt);
}

void gen_ray(t_ray *ray, int x, int y)
{
	ray->dir.x = (x - RES_X / 2.0) * (VP_W / RES_X);
	ray->dir.y = (y - RES_Y / 2.0) * (VP_H / RES_Y);
}

void	fill_img(int *img, t_info info, t_p p)
{
	int i;
	int j;
	t_ray ray;
	t_inter inter;
	t_inter min;
	
	i = -1;
	ray.o = p.cam.o;
	ray.dir.z = VP_D;
	while (++i < RES_Y * info.l / 4)
	{
		gen_ray(&ray, i % (info.l / 4), i / (info.l / 4));
		j = -1;
		min.color = BACKGROUND_COLOR;
		min.inter = __DBL_MAX__;
		while (p.objs[++j].o)
		{
			inter = (get_inter[p.objs[j].type])(ray, p.objs[j].o);
			if (inter.inter < min.inter && inter.inter > 1)
				min = inter;
		}
		img[i] = min.color;
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
