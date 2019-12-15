/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_gets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 01:06:04 by mbrunel           #+#    #+#             */
/*   Updated: 2019/12/15 22:20:03 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

int		get_vp(char *line, t_vp *vp)
{
	int i;
	
	i = 1;
	if (wk(vp->res_x = (int)recupdbl(line, &i, 'f', ' '), 4, RES_X_MAX) == -1)
		return (-1);
	if (wk(vp->res_y = (int)recupdbl(line, &i, 'f', '\0'), 4, RES_Y_MAX) == -1)
		return (-1);
	return (0);
}

int		get_lights(char *line, t_light *light, int type)
{
	t_parse v;
	int i;

	i = 1;
	if (line[1] == 'p')
		i++;
	if ((light->type = type) != AMBIENT)
		if (wk(v.d1 = recupdbl(line, &i, 'f', ','), -__DBL_MAX__, __DBL_MAX__) == -1 ||\
			wk(v.d2 = recupdbl(line, &i, 'f', ','), -__DBL_MAX__, __DBL_MAX__) == -1 ||\
			wk(v.d3 = recupdbl(line, &i, 'f', ' '), -__DBL_MAX__, __DBL_MAX__) == -1)
			return (-1);
	if ((light->type = type) != AMBIENT)
		light->pos = create_vec(v.d1, v.d2, v.d3);
	if (wk(light->intensity = recupdbl(line, &i, 'f', ' '), 0.0, 1.0) == -1)
		return (-1);
	if (wk(v.i1 = (int)recupdbl(line, &i, 'i', ','), 0, 255) == -1 ||\
		wk(v.i2 = (int)recupdbl(line, &i, 'i', ','), 0, 255) == -1 ||\
		wk(v.i3 = (int)recupdbl(line, &i, 'i', '\0'), 0, 255) == -1)
			return (-1);
	light->rgb = create_vec(v.i1, v.i2, v.i3);
	light->color = get_color_integer(v.i1, v.i2, v.i3);
	if (line[1] == 'p')
		light->type = PARALLEL;
	return (0);
}

int		get_cam(char *line, t_cam *cam)
{
	t_parse v;
	int i;

	i = 1;
	if (wk(v.d1 = recupdbl(line, &i, 'f', ','), -__DBL_MAX__, __DBL_MAX__) == -1 ||\
		wk(v.d2 = recupdbl(line, &i, 'f', ','), -__DBL_MAX__, __DBL_MAX__) == -1 ||\
		wk(v.d3 = recupdbl(line, &i, 'f', ' '), -__DBL_MAX__, __DBL_MAX__) == -1)
		return (-1);
	cam->o = create_vec(v.d1, v.d2, v.d3);
	if (wk(v.d1 = recupdbl(line, &i, 'f', ','), -1 + MIN_D, 1) == -1 ||\
		wk(v.d2 = recupdbl(line, &i, 'f', ','), -1 + MIN_D, 1) == -1 ||\
		wk(v.d3 = recupdbl(line, &i, 'f', ' '), -1 + MIN_D, 1) == -1)
		return (-1);
	cam->vec_dir = create_vec(v.d1, v.d2, v.d3);
	if (wk(cam->fov = recupdbl(line, &i, 'f', '\0'), 0.0, 180.0) == -1)
		return (-1);
	return (0);
}

int		get_sphere(char *line, void **ptr)
{
	t_parse v;
	int i;
	t_sp *sphere;

	if (!(sphere = malloc(sizeof(t_sp))))
		return (-1);
	i = 2;
	if (wk(v.d1 = recupdbl(line, &i, 'f', ','), -__DBL_MAX__, __DBL_MAX__) == -1 ||\
		wk(v.d2 = recupdbl(line, &i, 'f', ','), -__DBL_MAX__, __DBL_MAX__) == -1 ||\
		wk(v.d3 = recupdbl(line, &i, 'f', ' '), -__DBL_MAX__, __DBL_MAX__) == -1)
		return (-1);
	sphere->o = create_vec(v.d1, v.d2, v.d3);
	if (wk(sphere->r = recupdbl(line, &i, 'f', ' '), 0.0, __DBL_MAX__) == -1)
		return (-1);
	if (wk(v.i1 = (int)recupdbl(line, &i, 'i', ','), 0, 255) == -1 ||\
		wk(v.i2 = (int)recupdbl(line, &i, 'i', ','), 0, 255) == -1 ||\
		wk(v.i3 = (int)recupdbl(line, &i, 'i', ' '), 0, 255) == -1)
		return (-1);
	sphere->color = get_color_integer(v.i1, v.i2, v.i3);
	if (wk(sphere->spec = recupdbl(line, &i, 'f', ' '), 0.0, __DBL_MAX__) == -1)
		return (-1);
	if (wk(sphere->reflect = recupdbl(line, &i, 'f', '\0'), 0.0, 1.0) == -1)
		return (-1);
	*ptr = sphere;
	return (0);
}

int		get_plane(char *line, void **ptr)
{
	t_parse v;
	int i;
	t_pl *pl;

	if (!(pl = malloc(sizeof(t_pl))))
		return (-1);
	i = 2;
	if (wk(v.d1 = recupdbl(line, &i, 'f', ','), -__DBL_MAX__, __DBL_MAX__) == -1 ||\
		wk(v.d2 = recupdbl(line, &i, 'f', ','), -__DBL_MAX__, __DBL_MAX__) == -1 ||\
		wk(v.d3 = recupdbl(line, &i, 'f', ' '), -__DBL_MAX__, __DBL_MAX__) == -1)
		return (-1);
	pl->p = create_vec(v.d1, v.d2, v.d3);
	if (wk(v.d1 = recupdbl(line, &i, 'f', ','), -__DBL_MAX__, __DBL_MAX__) == -1 ||\
		wk(v.d2 = recupdbl(line, &i, 'f', ','), -__DBL_MAX__, __DBL_MAX__) == -1 ||\
		wk(v.d3 = recupdbl(line, &i, 'f', ' '), -__DBL_MAX__, __DBL_MAX__) == -1)
		return (-1);
	pl->dir = create_vec(v.d1, v.d2, v.d3);
	if (wk(v.i1 = (int)recupdbl(line, &i, 'i', ','), 0, 255) == -1 ||\
		wk(v.i2 = (int)recupdbl(line, &i, 'i', ','), 0, 255) == -1 ||\
		wk(v.i3 = (int)recupdbl(line, &i, 'i', '\0'), 0, 255) == -1)
		return (-1);
	pl->color = get_color_integer(v.i1, v.i2, v.i3);
	*ptr = pl;
	return (0);
}
