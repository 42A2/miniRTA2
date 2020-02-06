/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_it_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 19:33:33 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/06 08:24:35 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

static void	init_thd(t_data *dt, t_ray *ray, int *i, int *res_y)
{
	(*ray).o = dt->p.cam[dt->i_img].o;
	*res_y = dt->i == 7 ? dt->p.vp.res_y : dt->p.vp.res_y / 8 * (dt->i + 1);
	*i = dt->p.vp.res_y / 8 * dt->i - 1;
}

static void	*fill_img_threading(void *data)
{
	t_data	dt;
	int		i;
	int		j;
	int		res_y;
	t_ray	ray;

	dt = *(t_data*)data;
	init_thd(&dt, &ray, &i, &res_y);
	while (++i < res_y)
	{
		j = -1;
		while (++j < dt.p.vp.res_x)
		{
			ray.dir = cam_rot(c_to_vp((double)i, (double)j, dt.p.vp,
				dt.p.cam[dt.i_img].dist), dt.p.cam[dt.i_img].vec_dir, dt.ang);
			dt.img[i * dt.len + j] = find_pix_color(ray, &(dt.p),
				dt.p.bonus.recurse_reflect);
			if (dt.p.bonus.filter_type)
				filter(dt.p.bonus.filter_type, dt.p.bonus.filter_strength,
					dt.img, i * dt.len + j);
		}
	}
	aliasing_bonus(&dt);
	free(data);
	return (NULL);
}

static void	*create_data(t_p p, t_thread th, int i_img, int *img)
{
	t_data	*data;

	if (!(data = malloc(sizeof(t_data))))
	{
		ft_fprintf(2, "Error in allocation of thread %d\n", th.i);
		return (NULL);
	}
	data->p = p;
	data->ang = th.ang;
	data->len = th.len;
	data->i = th.i;
	data->i_img = i_img;
	data->img = img;
	data->count = &(th.count);
	data->cond = th.cond;
	data->mut = th.mut;
	return (data);
}

static void	init_th(t_thread *th, t_info info, t_p p, int i_img)
{
	th->count = 0;
	th->len = info.l / 4;
	th->i = -1;
	th->ang.x = acos(p.cam[i_img].vec_dir.z / sqrt(p.cam[i_img].vec_dir.y *
		p.cam[i_img].vec_dir.y + p.cam[i_img].vec_dir.z *
		p.cam[i_img].vec_dir.z));
	th->ang.y = acos(p.cam[i_img].vec_dir.z / sqrt(p.cam[i_img].vec_dir.x *
		p.cam[i_img].vec_dir.x + p.cam[i_img].vec_dir.z *
		p.cam[i_img].vec_dir.z));
}

void		fill_img(int *img, t_info info, t_p p, int i_img)
{
	t_thread				th;
	pthread_t				threads[8];
	t_data					*data;
	static pthread_cond_t	cond = PTHREAD_COND_INITIALIZER;
	static pthread_mutex_t	mut = PTHREAD_MUTEX_INITIALIZER;

	th.cond = &cond;
	th.mut = &mut;
	init_th(&th, info, p, i_img);
	while (++th.i < 8)
	{
		data = create_data(p, th, i_img, img);
		if (data)
			th.ret = pthread_create(threads + th.i, NULL,
				&fill_img_threading, data);
		if (th.ret || !data)
		{
			if (data)
				ft_fprintf(2, "Error in creation of thread %d\n", th.i);
			while (th.i-- > 0)
				pthread_join(threads[th.i], NULL);
			return ;
		}
	}
	joining(threads, th);
}
