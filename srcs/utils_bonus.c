/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 08:19:28 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/06 08:31:32 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

void		joining(pthread_t *threads, t_thread th)
{
	th.i = -1;
	while (++th.i < 8)
		pthread_join(threads[th.i], NULL);
}

void		find_ang(t_vec *ang, t_p p, int i_img)
{
	ang->x = acos(p.cam[i_img].vec_dir.z / sqrt(p.cam[i_img].vec_dir.y\
	* p.cam[i_img].vec_dir.y + p.cam[i_img].vec_dir.z\
	* p.cam[i_img].vec_dir.z));
	ang->y = acos(p.cam[i_img].vec_dir.z / sqrt(p.cam[i_img].vec_dir.x\
	* p.cam[i_img].vec_dir.x + p.cam[i_img].vec_dir.z\
	* p.cam[i_img].vec_dir.z));
}

int			check_diff(t_coor v, int *tab, int len, double delta)
{
	int	k;
	int	m;

	k = -2;
	while (++k < 2)
	{
		m = -2;
		while (++m < 2)
			if (comp_cols(tab[(v.i - k) * len\
			+ (v.j - m)], tab[v.i * len + v.j], delta) == -1)
				return (-1);
	}
	return (0);
}
