/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_it_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 19:33:33 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/06 03:38:10 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"
# include <pthread.h>

static void	*fill_img_threading(void *data)
{
	t_data	dt;
	int		i;
	int		j;
	int		res_y;
	t_ray	ray;

	dt = *(t_data*)data;
	ray.o = dt.p.cam[dt.i_img].o;
	res_y = dt.i == 7 ? dt.p.vp.res_y : dt.p.vp.res_y / 8 * (dt.i + 1);
	i = dt.p.vp.res_y / 8 * dt.i - 1;
	while (++i < res_y)
	{
		j = -1;
		while (++j < dt.p.vp.res_x)
		{
			ray.dir = cam_rot(c_to_vp((double)i, (double)j, dt.p.vp, dt.p.cam[dt.i_img].dist), dt.p.cam[dt.i_img].vec_dir, dt.ang);
			dt.img[i * dt.len + j] = find_pix_color(ray, dt.p, dt.p.bonus.recurse_reflect);
			if (dt.p.bonus.filter_type)
				filter(dt.p.bonus.filter_type, dt.p.bonus.filter_strength, dt.img, i * dt.len + j);
		}
	}
	free(data);
	return (NULL);
}

static void	*create_data(t_p p, t_vec ang, int len, int i, int i_img, int *img)
{
	t_data	*data;
	if (!(data = malloc(sizeof(t_data))))
	{
		ft_fprintf(2, "Error in allocation of thread %d\n", i);
		return (NULL);
	}
	data->p = p;
	data->ang = ang;
	data->len = len;
	data->i = i;
	data->i_img = i_img;
	data->img = img;
	return (data);
}

void		fill_img(int *img, t_info info, t_p p, int i_img)
{
	int			i;
	int			len;
	t_vec		ang;
	pthread_t	threads[8];
	int			ret;
	t_data		*data;

	len = info.l / 4;
	i = -1;
	ang.x = acos(p.cam[i_img].vec_dir.z / sqrt(p.cam[i_img].vec_dir.y * p.cam[i_img].vec_dir.y + p.cam[i_img].vec_dir.z * p.cam[i_img].vec_dir.z));
	ang.y = acos(p.cam[i_img].vec_dir.z / sqrt(p.cam[i_img].vec_dir.x * p.cam[i_img].vec_dir.x + p.cam[i_img].vec_dir.z * p.cam[i_img].vec_dir.z));
	while (++i < 8)
	{
		data = create_data(p, ang, len, i, i_img, img);
		if (data)
			ret = pthread_create(threads + i, NULL, &fill_img_threading, data);
		if (ret || !data)
		{
			if (data)
				ft_fprintf(2, "Error in creation of thread %d\n", i);
			while (i-- > 0)
			{
				pthread_join(threads[i], NULL);
				return ;
			}
		}
	}
	i = -1;
	while (++i < 8)
	{
		pthread_join(threads[i], NULL);
	}
}
