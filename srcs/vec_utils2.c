/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 01:42:37 by mbrunel           #+#    #+#             */
/*   Updated: 2020/02/03 05:57:26 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

t_vec	add_vec_d(t_vec vec1, double val)
{
	vec1.x += val;
	vec1.y += val;
	vec1.z += val;
	return (vec1);
}

t_vec	sub_vec_d(t_vec vec1, double val)
{
	vec1.x -= val;
	vec1.y -= val;
	vec1.z -= val;
	return (vec1);
}

t_vec	mult_vec_d(t_vec vec1, double val)
{
	vec1.x *= val;
	vec1.y *= val;
	vec1.z *= val;
	return (vec1);
}

t_vec	div_vec_d(t_vec vec1, double val)
{
	vec1.x /= val;
	vec1.y /= val;
	vec1.z /= val;
	return (vec1);
}

t_vec	cross_prod(t_vec vec1, t_vec vec2)
{
	t_vec	rt;

	rt.x = vec1.y * vec2.z - vec1.z * vec2.y;
	rt.y = vec1.z * vec2.x - vec1.x * vec2.z;
	rt.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (rt);
}
