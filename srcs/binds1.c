/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binds1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 01:43:48 by mbrunel           #+#    #+#             */
/*   Updated: 2020/02/06 02:08:15 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

t_vec			rot(t_vec dir, t_vec cam, t_vec ang)
{
	t_vec	tmp;

	if (cam.z < 0)
		ang.y += M_PI;
	if (cam.x > 0)
		ang.y = M_PI * 2 - ang.y;
	if (cam.y < 0)
		ang.x = M_PI * 2 - ang.x;
	tmp.x = dir.x;
	tmp.y = sin(ang.x) * dir.z + cos(ang.x) * dir.y;
	tmp.z = cos(ang.x) * dir.z - sin(ang.x) * dir.y;
	dir = tmp;
	tmp.x = cos(ang.y) * dir.x - sin(ang.y) * dir.z;
	tmp.y = dir.y;
	tmp.z = sin(ang.y) * dir.x + cos(ang.y) * dir.z;
	return ((tmp));
}

static int		find_chng(int i, t_swap *s, t_vec *chng)
{
	if (i == 123)
		*chng = create_vec(-STEP * s->p.cam[s->i].time, 0, 0);
	else if (i == 124)
		*chng = create_vec(STEP * s->p.cam[s->i].time, 0, 0);
	else if (i == 125)
		*chng = create_vec(0, 0, -STEP * s->p.cam[s->i].time);
	else if (i == 126)
		*chng = create_vec(0, 0, STEP * s->p.cam[s->i].time);
	else if (i == 116)
		*chng = create_vec(0, STEP * s->p.cam[s->i].time, 0);
	else if (i == 121)
		*chng = create_vec(0, -STEP * s->p.cam[s->i].time, 0);
	else
		return (-1);
	return (0);
}

int				chng_ocam(int i, void *swap)
{
	t_vec	chng;
	t_vec	ang;
	t_swap	*s;

	s = (t_swap*)swap;
	if (find_chng(i, s, &chng) == -1)
		return (0);
	ang.x = acos(s->p.cam[s->i].vec_dir.z / sqrt(s->p.cam[s->i].vec_dir.y\
	* s->p.cam[s->i].vec_dir.y + s->p.cam[s->i].vec_dir.z \
	* s->p.cam[s->i].vec_dir.z));
	ang.y = acos(s->p.cam[s->i].vec_dir.z / sqrt(s->p.cam[s->i].vec_dir.x \
	* s->p.cam[s->i].vec_dir.x + s->p.cam[s->i].vec_dir.z \
	* s->p.cam[s->i].vec_dir.z));
	s->p.cam[s->i].o = add_vec(s->p.cam[s->i].o\
	, rot(chng, s->p.cam[s->i].vec_dir, ang));
	s->p.cam[s->i].time = 0;
	mlx_destroy_image(s->mlx.ptr, s->mlx.img);
	return (img_to_win(s));
}

int				get_pos(int i, int x, int y, void *swap)
{
	t_swap		s;
	t_vec		ang;
	t_ray		ray;

	(void)i;
	s = *(t_swap*)swap;
	ang.x = acos(s.p.cam[s.i].vec_dir.z / sqrt(s.p.cam[s.i].vec_dir.y\
	* s.p.cam[s.i].vec_dir.y + s.p.cam[s.i].vec_dir.z\
	* s.p.cam[s.i].vec_dir.z));
	ang.y = acos(s.p.cam[s.i].vec_dir.z / sqrt(s.p.cam[s.i].vec_dir.x\
	* s.p.cam[s.i].vec_dir.x + s.p.cam[s.i].vec_dir.z\
	* s.p.cam[s.i].vec_dir.z));
	ray.o = s.p.cam[s.i].o;
	ray.dir = cam_rot(c_to_vp((double)y, (double)x\
	, s.p.vp, s.p.cam[s.i].dist), s.p.cam[s.i].vec_dir, ang);
	((t_swap*)swap)->c1 = min_inter(ray, s.p, MIN_D, __DBL_MAX__);
	return (0);
}

int				quit(int rt, void *swap)
{
	t_swap	*s;
	int		i;

	i = -1;
	s = (t_swap*)swap;
	while (++i < s->p.nb_objs)
		free(s->p.objs[i].o);
	exit(rt != -1 ? 0 : -1);
}
