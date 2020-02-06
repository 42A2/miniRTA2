/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aliasing_threading_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 05:30:33 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/06 08:30:16 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

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

static void		cond_thread(t_data *dt)
{
	(*(dt->count))++;
	if (*(dt->count) == 8)
		pthread_cond_broadcast(dt->cond);
	else
	{
		pthread_mutex_lock(dt->mut);
		pthread_cond_wait(dt->cond, dt->mut);
		pthread_mutex_unlock(dt->mut);
	}
}

void			aliasing_bonus(t_data *dt)
{
	t_coor	v;
	t_vec	ang;
	int		res_y;

	if (!dt->p.bonus.coeff_aliasing)
		return ;
	cond_thread(dt);
	res_y = dt->i == 7 ? dt->p.vp.res_y - 1 : dt->p.vp.res_y / 8 * (dt->i + 1);
	v.i = dt->p.vp.res_y / 8 * dt->i;
	find_ang(&ang, dt->p, dt->i_img);
	while (++v.i < res_y)
	{
		v.j = 0;
		while (++v.j < dt->p.vp.res_x - 1)
		{
			v.actualpix = dt->img[v.i * dt->len + v.j];
			if (check_diff(v, dt->img, dt->len,\
			dt->p.bonus.delta_aliasing) == -1)
				dt->img[v.i * dt->len + v.j] =\
				recalc_img(v, &(dt->p), dt->i_img, ang);
		}
	}
}
