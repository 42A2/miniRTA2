/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intercy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 04:26:20 by mbrunel           #+#    #+#             */
/*   Updated: 2020/10/15 20:53:19 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		cy2(t_cyvar *v, t_cy cy, t_inter *rt, t_var2 v2)
{
	v->ex = cross_prod(v->lx, cy.dir);
	v->t = prod_scal(mult_vec_d(v->ex, -1), v->wn) / sqrt(v->sqr_omega);
	v->fx = cross_prod(v->wn, cy.dir);
	v->fxn = div_vec_d(v->fx, norm_vec(v->fx));
	v->s = sqrt(cy.r\
	* cy.r - v->rx * v->rx) / d_absol(prod_scal(v2.ray.dir, v->fxn));
	rt->inter = v->t - v->s;
	if (norm_vec(add_vec(cy.dir\
	, v2.ray.dir)) < norm_vec(add_vec(mult_vec_d(cy.dir, -1), v2.ray.dir)))
		mult_vec_d(cy.dir, -1);
	if (norm_vec(sub_vec(add_vec(v2.ray.o, mult_vec_d(v2.ray.dir\
	, rt->inter)), cy.p)) > sqrt(cy.h / 2 * cy.h / 2 + cy.r * cy.r))
	{
		rt->inter = v->t + v->s;
		v->boo = 1;
		if (norm_vec(sub_vec(add_vec(v2.ray.o, mult_vec_d(v2.ray.dir\
		, rt->inter)), cy.p)) > sqrt(cy.h / 2 * cy.h / 2 + cy.r * cy.r))
			rt->inter = 0;
	}
	else if (rt->inter < 0)
	{
		rt->inter = v->t + v->s;
		v->boo = 1;
	}
}

t_inter		cy3(t_cyvar *v, t_cy cy, t_inter *rt, t_var2 v2)
{
	rt->ipoint = add_vec(v2.ray.o, mult_vec_d(v2.ray.dir, rt->inter));
	rt->color = cy.color;
	rt->reflect = cy.reflect;
	rt->spec = cy.spec;
	v->cp = sub_vec(rt->ipoint, cy.p);
	v->cq = prod_scal(v->cp, cy.dir);
	v->qp = sub_vec(v->cp, mult_vec_d(cy.dir, v->cq));
	rt->normal = v->boo ? cy.dir : div_vec_d(v->qp, cy.r);
	return (*rt);
}

t_inter		intercy(t_ray ray, void *ptr, double start, double max)
{
	t_cy	cy;
	t_inter	rt;
	t_cyvar	v;
	t_var2	v2;

	cy = *(t_cy*)ptr;
	v2 = create_v2(start, max, ray);
	v.boo = 0;
	v.lx = sub_vec(ray.o, cy.p);
	v.w = cross_prod(ray.dir, cy.dir);
	v.sqr_omega = prod_scal(v.w, v.w);
	if (!v.sqr_omega)
		rt.inter = 0;
	else
	{
		v.wn = div_vec_d(v.w, sqrt(v.sqr_omega));
		v.rx = d_absol(prod_scal(v.lx, v.wn));
		if (v.rx > cy.r)
			rt.inter = 0;
		else
			cy2(&v, cy, &rt, v2);
	}
	if (rt.inter < start || rt.inter > max)
		rt.inter = 0;
	return (cy3(&v, cy, &rt, v2));
}
