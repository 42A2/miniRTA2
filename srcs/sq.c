/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:22:50 by yvanat            #+#    #+#             */
/*   Updated: 2020/01/23 21:29:38 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

t_inter	intersq(t_ray ray, void *ptr, double start, double max)
{
	t_sq sq;
	t_inter rt;
	(void)start;(void)max;(void)ray;
	sq = *(t_sq*)ptr;
	rt.inter = 0;
	return (rt);
}