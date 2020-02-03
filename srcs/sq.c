/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:22:50 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/02 22:38:12 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

static t_vec	inv_prod_scal(t_vec vec1)
{
	t_vec vec2;

	vec2.x = 1;
	vec2.y = 2;
	vec2.z = 3;
	if (vec1.x == 0 && vec1.y == 0)
		vec2.z = 0;
	else if (vec1.x == 0 && vec1.z == 0)
		vec2.y = 0;
	else if (vec1.y == 0 && vec1.z == 0)
		vec2.x = 0;
	else if (vec1.x == 0)
		vec2.y = -1 * (vec1.x * vec2.x + vec1.z * vec2.z) / vec1.y;
	else
	{
		vec2.x = -1 * (vec1.y * vec2.y + vec1.z * vec2.z) / vec1.x;
	}
	return (normalize(vec2));
}

t_inter			intersq(t_ray ray, void *ptr, double start, double max)
{
	t_sq sq;
	t_inter rt;
	t_vec l;
	t_vec random_normal;
	t_vec normal_random_normal;
	t_vec p1;
	t_vec p2;
	t_vec p3;
	t_vec p4;
	t_vec vec1;
	t_vec vec2;
	t_vec vec22;
	t_vec edge2;
	t_vec edge3;
	t_vec edge22;
	t_vec edge33;
	t_vec vp;
	t_vec c;
	double d;
	double m;
	double boo;

	sq = *(t_sq*)ptr;
	random_normal = inv_prod_scal(sq.dir);
	normal_random_normal = cross_prod(random_normal, sq.dir);
	p1 = add_vec(sq.p, mult_vec_d(random_normal, sqrt(sq.h * sq.h / 2)));
	p2 = sub_vec(sq.p, mult_vec_d(random_normal, sqrt(sq.h * sq.h / 2)));
	p3 = add_vec(sq.p, mult_vec_d(normal_random_normal, sqrt(sq.h * sq.h / 2)));
	p4 = sub_vec(sq.p, mult_vec_d(normal_random_normal, sqrt(sq.h * sq.h / 2)));
	boo = 0;
	vec1 = sub_vec(p2, p1);
	vec2 = sub_vec(p3, p1);
	vec22 = sub_vec(p4, p1);
	edge2 = sub_vec(p3, p2);
	edge3 = sub_vec(p1, p3);
	edge22 = sub_vec(p4, p2);
	edge33 = sub_vec(p1, p4);
	rt.normal = cross_prod(vec1, vec2);
	m = prod_scal(rt.normal,ray.dir);
	if (d_abs(m) < start)
	{
		rt.inter = 0;
		return (rt);
	}
	else
	{
		l = sub_vec(ray.o, p1);
		d = prod_scal(rt.normal, l);
		rt.inter = -d / m;
	}
	if (rt.inter < start || rt.inter > max)
		rt.inter = 0;
	rt.ipoint = add_vec(ray.o, mult_vec_d(ray.dir, rt.inter));
	vp = sub_vec(rt.ipoint, p1);
	c = cross_prod(vec1, vp);
	if (prod_scal(rt.normal, c) < 0)
		boo++;
	vp = sub_vec(rt.ipoint, p2);
	c = cross_prod(edge2, vp);
	if (prod_scal(rt.normal, c) < 0)
		boo++;
	vp = sub_vec(rt.ipoint, p3);
	c = cross_prod(edge3, vp);
	if (prod_scal(rt.normal, c) < 0)
		boo++;
	if (boo != 0)
	{
		boo = 0;
		rt.normal = cross_prod(vec1, vec22);
		m = prod_scal(rt.normal,ray.dir);
		if (d_abs(m) < start)
		{
			rt.inter = 0;
			return (rt);
		}
		else
		{
			l = sub_vec(ray.o, p1);
			d = prod_scal(rt.normal, l);
			rt.inter = -d / m;
		}
		if (rt.inter < start || rt.inter > max)
			rt.inter = 0;
		rt.ipoint = add_vec(ray.o, mult_vec_d(ray.dir, rt.inter));
		vp = sub_vec(rt.ipoint, p1);
		c = cross_prod(vec1, vp);
		if (prod_scal(rt.normal, c) < 0)
			boo++;
		vp = sub_vec(rt.ipoint, p2);
		c = cross_prod(edge22, vp);
		if (prod_scal(rt.normal, c) < 0)
			boo++;
		vp = sub_vec(rt.ipoint, p4);
		c = cross_prod(edge33, vp);
		if (prod_scal(rt.normal, c) < 0)
			boo++;
		if (boo != 0)
			rt.inter = 0;
	}
	rt.normal = prod_scal(sub_vec(p1, ray.o), rt.normal) < 0 ? rt.normal : mult_vec_d(rt.normal, -1);
	rt.reflect = sq.reflect;
	rt.spec = sq.spec;
	rt.color = sq.color;
	return (rt);
}