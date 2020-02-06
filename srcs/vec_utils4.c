/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 05:59:18 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/06 04:36:19 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

double	d_abs(double nb)
{
	return (nb >= 0 ? nb : -nb);
}

int		abs(int nb)
{
	return (nb >= 0 ? nb : -nb);
}

t_vec	i_prod_scal(t_vec vec)
{
	t_vec rt;

	rt.x = 0;
	(void)vec;
	return (rt);
}

t_vec	inv_prod_scal(t_vec vec1)
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

t_var2	create_v2(double start, double max, t_ray ray)
{
	t_var2 v2;

	v2.start = start;
	v2.max = max;
	v2.ray = ray;
	return (v2);
}
