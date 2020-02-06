/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 19:33:33 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/06 07:07:31 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

void		find_ang(t_vec *ang, t_p p, int i_img)
{
	ang->x = acos(p.cam[i_img].vec_dir.z / sqrt(p.cam[i_img].vec_dir.y\
	* p.cam[i_img].vec_dir.y + p.cam[i_img].vec_dir.z\
	* p.cam[i_img].vec_dir.z));
	ang->y = acos(p.cam[i_img].vec_dir.z / sqrt(p.cam[i_img].vec_dir.x\
	* p.cam[i_img].vec_dir.x + p.cam[i_img].vec_dir.z\
	* p.cam[i_img].vec_dir.z));
}

void		fill_img(int *img, t_info info, t_p p, int i_img)
{
	int		i;
	int		j;
	t_ray	ray;
	int		len;
	t_vec	ang;

	len = info.l / 4;
	i = -1;
	ray.o = p.cam[i_img].o;
	find_ang(&ang, p, i_img);
	while (++i < p.vp.res_y)
	{
		j = -1;
		while (++j < p.vp.res_x)
		{
			ray.dir = cam_rot(c_to_vp((double)i, (double)j\
			, p.vp, p.cam[i_img].dist), p.cam[i_img].vec_dir, ang);
			img[i * len + j] = find_pix_color(ray, &p, p.bonus.recurse_reflect);
			if (p.bonus.filter_type)
				filter(p.bonus.filter_type\
				, p.bonus.filter_strength, img, i * len + j);
		}
	}
	if (p.bonus.coeff_aliasing)
		aliasing(img, len, p, i_img);
}
