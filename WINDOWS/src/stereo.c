/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 02:08:42 by mbrunel           #+#    #+#             */
/*   Updated: 2020/10/15 20:53:19 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	free_2(void *img1, void *img2)
{
	free(img2);
	free(img1);
}

static int	cat_img(t_swap *s, int *img1, int *img2, int prev_len)
{
	int i;
	int j;
	int len;

	if (!(s->mlx.img = mlx_new_image(s->mlx.ptr\
	, s->p.vp.res_x * 2, s->p.vp.res_y)))
		return (-1);
	if (!(s->img = (int*)mlx_get_data_addr(s->mlx.img\
	, &(s->info.n), &(s->info.l), &(s->info.e))))
		return (-1);
	i = -1;
	len = s->info.l / 4;
	while (++i < s->p.vp.res_y)
	{
		j = -1;
		while (++j < s->p.vp.res_x)
		{
			s->img[i * len + j] = img1[i * (prev_len) + j];
			s->img[i * len + j + s->p.vp.res_x] = img2[i * (prev_len) + j];
		}
	}
	free_2(img1, img2);
	s->p.vp.res_x *= 2;
	export_bmp(create_bmp_filename("3D.rt", 2), s);
	return (quit(0, s));
}

int			stereo(t_swap *s)
{
	t_vec	chng;
	t_vec	ang;
	int		*img1;
	int		*img2;
	int		prev_len;

	prev_len = s->info.l / 4;
	if (!(img1 = malloc(sizeof(int) * s->p.vp.res_y * (s->info.l / 4))))
		quit(error(NULL, "memory error\n"), s);
	if (!(img2 = malloc(sizeof(int) * s->p.vp.res_y * (s->info.l / 4))))
		quit(error(img1, "memory error\n"), s);
	memcpy(img1, s->img, sizeof(int) * s->p.vp.res_y * (s->info.l / 4));
	chng = create_vec(DEC, 0, 0);
	ang.x = acos(s->p.cam[s->i].vec_dir.z / sqrt(s->p.cam[s->i].vec_dir.y\
	* s->p.cam[s->i].vec_dir.y + s->p.cam[s->i].vec_dir.z\
	* s->p.cam[s->i].vec_dir.z));
	ang.y = acos(s->p.cam[s->i].vec_dir.z / sqrt(s->p.cam[s->i].vec_dir.x\
	* s->p.cam[s->i].vec_dir.x + s->p.cam[s->i].vec_dir.z\
	* s->p.cam[s->i].vec_dir.z));
	s->p.cam[s->i].o = add_vec(s->p.cam[s->i].o\
	, rot(chng, s->p.cam[s->i].vec_dir, ang));
	fill_img(s->img, s->info, s->p, s->i);
	memcpy(img2, s->img, sizeof(int) * s->p.vp.res_y * (s->info.l / 4));
	return (cat_img(s, img1, img2, prev_len));
}
