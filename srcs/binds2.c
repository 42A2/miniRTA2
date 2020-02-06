/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binds2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 02:23:59 by mbrunel           #+#    #+#             */
/*   Updated: 2020/02/06 09:59:01 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

static void	calc_ray(t_ray *ray, t_swap *s, int x, int y)
{
	t_vec ang;

	ang.x = acos(s->p.cam[s->i].vec_dir.z / sqrt(s->p.cam[s->i].vec_dir.y\
	* s->p.cam[s->i].vec_dir.y + s->p.cam[s->i].vec_dir.z\
	* s->p.cam[s->i].vec_dir.z));
	ang.y = acos(s->p.cam[s->i].vec_dir.z / sqrt(s->p.cam[s->i].vec_dir.x\
	* s->p.cam[s->i].vec_dir.x + s->p.cam[s->i].vec_dir.z
	* s->p.cam[s->i].vec_dir.z));
	ray->o = s->p.cam[s->i].o;
	ray->dir = cam_rot(c_to_vp((double)y, (double)x, s->p.vp
	, s->p.cam[s->i].dist), s->p.cam[s->i].vec_dir, ang);
}

int			stretch(int i, int x, int y, void *swap)
{
	t_swap	*s;
	t_ray	ray;
	int		type;

	s = (t_swap*)swap;
	if (s->c1.inter)
		type = s->p.objs[s->c1.i_obj].type;
	else
		type = -1;
	calc_ray(&ray, s, x, y);
	if ((!s->c1.inter || type == PLANE) && i == 2)
		s->p.cam->vec_dir = ray.dir;
	else if (s->c1.inter && (i == 1 || type == TRIANGLE))
	{
		if (type == TRIANGLE)
			((t_tr*)(s->p.objs[s->c1.i_obj].o))->click = s->c1.ipoint;
		g_chng_origin[type](s->p.objs[s->c1.i_obj].o, ray);
	}
	else if (i == 2)
		g_chng_stretch[type](s->p.objs[s->c1.i_obj].o, ray);
	else
		return (0);
	return (img_to_win(s));
}

static int	forest(t_swap *s, int i)
{
	if (i >= 18 && i <= 21)
		s->i = i - 18;
	else if (i == 23)
		s->i = 4;
	else if (i == 22)
		s->i = 5;
	else if (i == 26)
		s->i = 6;
	else if (i == 28)
		s->i = 7;
	else if (i == 25)
		s->i = 8;
	else if (i >= 83 && i <= 92)
		s->i = i - 83;
	else if (i == 53)
		quit(0, s);
	else if (i == 48)
		s->i = (s->i + 1) % s->p.nb_cam;
	else
		return (-1);
	return (0);
}

int			swap_cam(int i, void *swap)
{
	t_swap *s;

	s = (t_swap*)swap;
	if (!forest(s, i))
		(void)i;
	else if (i == 1)
	{
		s->p.vp = s->p.bonus.save_res;
		s->p.bonus.coeff_aliasing = s->p.bonus.save_coef_as;
		s->p.bonus.delta_aliasing = s->p.bonus.save_delta_as;
		s->s_s = 1;
	}
	else if (i == 2)
		return (stereo(s));
	else
	{
		if ((i >= 123 && i <= 126) || i == 116 || i == 121)
			((t_swap*)(swap))->p.cam[s->i].time += 1;
		else if (s->p.nb_cam <= s->i)
			ft_fprintf(1, "no such camera\n");
		return (0);
	}
	return (img_to_win(s));
}
