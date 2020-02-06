/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 04:21:31 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/06 04:44:38 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

static void	intersp_split(t_spvar *var)
{
	if (var->dis > 0)
	{
		var->t1 = (-var->b + sqrt(var->dis)) / (2 * var->a);
		var->t2 = (-var->b - sqrt(var->dis)) / (2 * var->a);
		if (var->t1 < 0)
			var->rt.inter = var->t2;
		else if (var->t2 < 0)
			var->rt.inter = var->t1;
		else
			var->rt.inter = var->t1 < var->t2 ? var->t1 : var->t2;
	}
	else if (var->dis == 0)
		var->rt.inter = -var->b / 2 * var->a;
	else
		var->rt.inter = 0;
}

t_inter		intersp(t_ray ray, void *ptr, double start, double max)
{
	t_spvar	var;
	t_sp	sp;

	sp = *(t_sp*)ptr;
	var.oc = sub_vec(ray.o, sp.o);
	var.a = prod_scal(ray.dir, ray.dir);
	var.b = 2 * prod_scal(var.oc, ray.dir);
	var.c = prod_scal(var.oc, var.oc) - sp.r * sp.r;
	var.dis = var.b * var.b - 4 * var.a * var.c;
	intersp_split(&var);
	var.rt.color = sp.color;
	var.rt.spec = sp.spec;
	var.rt.reflect = sp.reflect;
	if (var.rt.inter < start || var.rt.inter > max)
		var.rt.inter = 0;
	var.rt.ipoint = add_vec(ray.o, mult_vec_d(ray.dir, var.rt.inter));
	var.rt.normal = normalize(sub_vec(var.rt.ipoint, sp.o));
	return (var.rt);
}
