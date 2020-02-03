/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 05:59:18 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/03 05:59:30 by yvanat           ###   ########.fr       */
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
