/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tr.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:44:02 by mbrunel           #+#    #+#             */
/*   Updated: 2020/02/06 04:09:26 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

static t_trvar2	create_v2(double start, double max, t_ray ray)
{
	t_trvar2 v2;

	v2.start = start;
	v2.max = max;
	v2.ray = ray;
	return (v2);
}

static void		tr1(t_trvar *v, t_inter *rt, t_tr tr, t_trvar2 v2)
{
	v->boo = 0;
	v->vec1 = sub_vec(tr.ang2, tr.ang1);
	v->vec2 = sub_vec(tr.ang3, tr.ang1);
	v->edge2 = sub_vec(tr.ang3, tr.ang2);
	v->edge3 = sub_vec(tr.ang1, tr.ang3);
	rt->normal = cross_prod(v->vec1, v->vec2);
	v->m = prod_scal(rt->normal, v2.ray.dir);
	if (d_abs(v->m) < v2.start)
	{
		rt->inter = 0;
		return ;
	}
	v->l = sub_vec(v2.ray.o, tr.ang1);
	v->d = prod_scal(rt->normal, v->l);
	rt->inter = -v->d / v->m;
	if (rt->inter < v2.start || rt->inter > v2.max)
		rt->inter = 0;
	rt->ipoint = add_vec(v2.ray.o, mult_vec_d(v2.ray.dir, rt->inter));
	v->vp = sub_vec(rt->ipoint, tr.ang1);
	v->c = cross_prod(v->vec1, v->vp);
	if (prod_scal(rt->normal, v->c) < 0)
		v->boo++;
}

t_inter			intertr(t_ray ray, void *ptr, double start, double max)
{
	t_trvar		v;
	t_inter		rt;
	t_tr		tr;

	tr = *(t_tr*)ptr;
	tr1(&v, &rt, tr, create_v2(start, max, ray));
	if (!rt.inter)
		return (rt);
	v.vp = sub_vec(rt.ipoint, tr.ang2);
	v.c = cross_prod(v.edge2, v.vp);
	if (prod_scal(rt.normal, v.c) < 0)
		v.boo++;
	v.vp = sub_vec(rt.ipoint, tr.ang3);
	v.c = cross_prod(v.edge3, v.vp);
	if (prod_scal(rt.normal, v.c) < 0)
		v.boo++;
	if (v.boo != 0)
		rt.inter = 0;
	rt.normal = prod_scal(sub_vec(tr.ang1, ray.o), rt.normal)
		< 0 ? rt.normal : mult_vec_d(rt.normal, -1);
	rt.color = tr.color;
	rt.reflect = tr.reflect;
	rt.spec = tr.spec;
	return (rt);
}
