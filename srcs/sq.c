/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:22:50 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/06 04:00:21 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

static void		init_sqvar(t_sq sq, t_ray ray, t_sqvar *var)
{
	var->sqr = sqrt(sq.h * sq.h / 2);
	var->random_normal = inv_prod_scal(sq.dir);
	var->normal_random_normal = cross_prod(var->random_normal, sq.dir);
	var->p1 = add_vec(sq.p, mult_vec_d(var->random_normal, var->sqr));
	var->p2 = sub_vec(sq.p, mult_vec_d(var->random_normal, var->sqr));
	var->p3 = add_vec(sq.p, mult_vec_d(var->normal_random_normal, var->sqr));
	var->p4 = sub_vec(sq.p, mult_vec_d(var->normal_random_normal, var->sqr));
	var->boo = 0;
	var->vec1 = sub_vec(var->p2, var->p1);
	var->vec2 = sub_vec(var->p3, var->p1);
	var->vec22 = sub_vec(var->p4, var->p1);
	var->edge2 = sub_vec(var->p3, var->p2);
	var->edge3 = sub_vec(var->p1, var->p3);
	var->edge22 = sub_vec(var->p4, var->p2);
	var->edge33 = sub_vec(var->p1, var->p4);
	var->rt.normal = cross_prod(var->vec1, var->vec2);
	var->m = prod_scal(var->rt.normal, ray.dir);
}

static void		intersq_split(t_sqvar *var, t_ray ray, double start, double max)
{
	var->l = sub_vec(ray.o, var->p1);
	var->d = prod_scal(var->rt.normal, var->l);
	var->rt.inter = -var->d / var->m;
	if (var->rt.inter < start || var->rt.inter > max)
		var->rt.inter = 0;
	var->rt.ipoint = add_vec(ray.o, mult_vec_d(ray.dir, var->rt.inter));
	var->vp = sub_vec(var->rt.ipoint, var->p1);
	var->c = cross_prod(var->vec1, var->vp);
	if (prod_scal(var->rt.normal, var->c) < 0)
		var->boo++;
	var->vp = sub_vec(var->rt.ipoint, var->p2);
	var->c = cross_prod(var->edge2, var->vp);
	if (prod_scal(var->rt.normal, var->c) < 0)
		var->boo++;
	var->vp = sub_vec(var->rt.ipoint, var->p3);
	var->c = cross_prod(var->edge3, var->vp);
	if (prod_scal(var->rt.normal, var->c) < 0)
		var->boo++;
}

static void		intersq_splitnd(t_sqvar *var, t_ray ray, double s, double max)
{
	var->l = sub_vec(ray.o, var->p1);
	var->d = prod_scal(var->rt.normal, var->l);
	var->rt.inter = -var->d / var->m;
	if (var->rt.inter < s || var->rt.inter > max)
		var->rt.inter = 0;
	var->rt.ipoint = add_vec(ray.o, mult_vec_d(ray.dir, var->rt.inter));
	var->vp = sub_vec(var->rt.ipoint, var->p1);
	var->c = cross_prod(var->vec1, var->vp);
	if (prod_scal(var->rt.normal, var->c) < 0)
		var->boo++;
	var->vp = sub_vec(var->rt.ipoint, var->p2);
	var->c = cross_prod(var->edge22, var->vp);
	if (prod_scal(var->rt.normal, var->c) < 0)
		var->boo++;
	var->vp = sub_vec(var->rt.ipoint, var->p4);
	var->c = cross_prod(var->edge33, var->vp);
	if (prod_scal(var->rt.normal, var->c) < 0)
		var->boo++;
	if (var->boo != 0)
		var->rt.inter = 0;
}

static t_inter	ret_rt(t_sqvar *var)
{
	var->rt.inter = 0;
	return (var->rt);
}

t_inter			intersq(t_ray ray, void *ptr, double start, double max)
{
	t_sq	sq;
	t_sqvar	var;

	sq = *(t_sq*)ptr;
	init_sqvar(sq, ray, &var);
	if (d_abs(var.m) < start)
		return (ret_rt(&var));
	intersq_split(&var, ray, start, max);
	if (var.boo != 0)
	{
		var.boo = 0;
		var.rt.normal = cross_prod(var.vec1, var.vec22);
		var.m = prod_scal(var.rt.normal, ray.dir);
		if (d_abs(var.m) < start)
			return (ret_rt(&var));
		intersq_splitnd(&var, ray, start, max);
	}
	var.rt.normal = prod_scal(sub_vec(var.p1, ray.o), var.rt.normal) < 0 ?
		var.rt.normal : mult_vec_d(var.rt.normal, -1);
	var.rt.reflect = sq.reflect;
	var.rt.spec = sq.spec;
	var.rt.color = sq.color;
	return (var.rt);
}
