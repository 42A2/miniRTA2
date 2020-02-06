/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aliasing_threading_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 05:30:33 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/06 07:47:30 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"
#include <pthread.h>

void	aliasing_bonus(t_data *dt)
{
	int	i;
	int	j;

	if (!dt->p.bonus.coeff_aliasing)
		return ;
	(*(dt->count))++;
	if (*(dt->count) == 8)
		pthread_cond_broadcast(dt->cond);
	else
	{
		pthread_mutex_lock(dt->mut);
		pthread_cond_wait(dt->cond, dt->mut);
		pthread_mutex_unlock(dt->mut);
	}
	return ;
}
