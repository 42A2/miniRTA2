/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 06:12:33 by mbrunel           #+#    #+#             */
/*   Updated: 2020/02/06 08:36:50 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

static int		check_di(t_coor v, int *tab, int len, double delta)
{
	int	k;
	int	m;

	k = -2;
	while (++k < 2)
	{
		m = -2;
		while (++m < 2)
			if (comp_cols(tab[(v.i - k) * len\
			+ (v.j - m)], tab[v.i * len + v.j], delta) == -1)
				return (-1);
	}
	return (0);
}

static void		r3(t_as *v, t_coor inc, t_p *p)
{
	v->color[v->n] = inc.actualpix;
	if (p->bonus.filter_type)
		filter(p->bonus.filter_type, p->bonus.filter_strength, v->color, v->n);
}

static void		r2(t_as *v, t_coor inc, t_vec ang, t_p *p)
{
	v->ray.dir = cam_rot(c_to_vp((double)(((double)v->k\
	/ (p->bonus.coeff_aliasing) * 2)) + inc.i, (double)(inc.j\
	+ ((double)v->m / (p->bonus.coeff_aliasing * 2)))\
	, p->vp, p->cam[v->i_img].dist), p->cam[v->i_img].vec_dir, ang);
	v->color[v->n] = find_pix_color(v->ray, p, p->bonus.recurse_reflect);
	if (p->bonus.filter_type)
		filter(p->bonus.filter_type\
		, p->bonus.filter_strength, v->color, v->n);
}

static int		recalc_img(t_coor inc, t_p *p, int i_img, t_vec ang)
{
	t_as	v;

	v.i_img = i_img;
	v.nb = ((p->bonus.coeff_aliasing * 2)\
	- 1) * ((p->bonus.coeff_aliasing * 2) - 1);
	if (!(v.color = malloc(v.nb * sizeof(int))))
		exit(error(NULL, "memory error\n"));
	v.n = 0;
	v.ray.o = p->cam[i_img].o;
	v.k = -p->bonus.coeff_aliasing;
	while (++v.k < p->bonus.coeff_aliasing)
	{
		v.m = -p->bonus.coeff_aliasing;
		while (++v.m < p->bonus.coeff_aliasing)
		{
			if (v.k || v.m)
				r2(&v, inc, ang, p);
			else
				r3(&v, inc, p);
			v.n++;
		}
	}
	return (mid_color(v.color, v.nb));
}

void			aliasing(int *img, int len, t_p p, int i_img)
{
	t_coor	v;
	t_vec	ang;

	v.i = 0;
	find_ang(&ang, p, i_img);
	while (++v.i < p.vp.res_y - 1)
	{
		v.j = 0;
		while (++v.j < p.vp.res_x - 1)
		{
			v.actualpix = img[v.i * len + v.j];
			if (check_di(v, img, len, p.bonus.delta_aliasing) == -1)
				img[v.i * len + v.j] = recalc_img(v, &p, i_img, ang);
		}
	}
}
