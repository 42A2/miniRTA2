/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 01:42:37 by mbrunel           #+#    #+#             */
/*   Updated: 2019/12/10 02:27:37 by mbrunel          ###   ########.fr       */
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