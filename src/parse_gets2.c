/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_gets2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 04:12:08 by mbrunel           #+#    #+#             */
/*   Updated: 2020/10/15 20:53:19 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			get_sphere(char *line, void **ptr)
{
	t_parse	v;
	int		i;
	t_sp	*sphere;

	if (!(sphere = malloc(sizeof(t_sp))))
		return (-1);
	i = 2;
	if (wk(v.d1 = recupdbl(line, &i, 'f', ','), -MAX_D, MAX_D) == -1 ||\
		wk(v.d2 = recupdbl(line, &i, 'f', ','), -MAX_D, MAX_D) == -1 ||\
		wk(v.d3 = recupdbl(line, &i, 'f', ' '), -MAX_D, MAX_D) == -1)
		return (-1);
	sphere->o = create_vec(v.d1, v.d2, v.d3);
	if (wk(sphere->r = recupdbl(line, &i, 'f', ' '), 0.0, MAX_D) == -1)
		return (-1);
	if (wk(v.i1 = (int)recupdbl(line, &i, 'i', ','), 0, 255) == -1 ||\
		wk(v.i2 = (int)recupdbl(line, &i, 'i', ','), 0, 255) == -1 ||\
		wk(v.i3 = (int)recupdbl(line, &i, 'i', ' '), 0, 255) == -1)
		return (-1);
	sphere->color = get_color_integer(v.i1, v.i2, v.i3);
	if (wk(sphere->spec = recupdbl(line, &i, 'f', ' '), 0.0, MAX_D) == -1)
		return (-1);
	if (wk(sphere->reflect = recupdbl(line, &i, 'f', '\0'), 0.0, 1.0) == -1)
		return (-1);
	*ptr = sphere;
	return (0);
}

static int	plane2(char *line, t_pl *pl, int i)
{
	t_parse v;

	if (wk(v.d1 = recupdbl(line, &i, 'f', ','), -1, 1) == -1 ||\
		wk(v.d2 = recupdbl(line, &i, 'f', ','), -1, 1) == -1 ||\
		wk(v.d3 = recupdbl(line, &i, 'f', ' '), -1, 1) == -1)
		return (-1);
	pl->dir = create_vec(v.d1, v.d2, v.d3);
	if (wk(v.i1 = (int)recupdbl(line, &i, 'i', ','), 0, 255) == -1 ||\
		wk(v.i2 = (int)recupdbl(line, &i, 'i', ','), 0, 255) == -1 ||\
		wk(v.i3 = (int)recupdbl(line, &i, 'i', ' '), 0, 255) == -1)
		return (-1);
	pl->color = get_color_integer(v.i1, v.i2, v.i3);
	pl->d = -1 * prod_scal(pl->dir, pl->p);
	if (wk(pl->spec = recupdbl(line, &i, 'f', ' '), 0.0, MAX_D) == -1)
		return (-1);
	if (wk(pl->reflect = recupdbl(line, &i, 'f', '\0'), 0.0, 1.0) == -1)
		return (-1);
	return (0);
}

int			get_plane(char *line, void **ptr)
{
	t_parse	v;
	int		i;
	t_pl	*pl;

	if (!(pl = malloc(sizeof(t_pl))))
		return (-1);
	i = 2;
	if (wk(v.d1 = recupdbl(line, &i, 'f', ','), -MAX_D, MAX_D) == -1 ||\
		wk(v.d2 = recupdbl(line, &i, 'f', ','), -MAX_D, MAX_D) == -1 ||\
		wk(v.d3 = recupdbl(line, &i, 'f', ' '), -MAX_D, MAX_D) == -1)
		return (-1);
	pl->p = create_vec(v.d1, v.d2, v.d3);
	if (plane2(line, pl, i) == -1)
		return (-1);
	*ptr = pl;
	return (0);
}

static int	triangle2(char *line, t_tr *tr, int i)
{
	t_parse v;

	tr->ang2 = create_vec(v.d1, v.d2, v.d3);
	if (wk(v.d1 = recupdbl(line, &i, 'f', ','), -MAX_D, MAX_D) == -1 ||\
		wk(v.d2 = recupdbl(line, &i, 'f', ','), -MAX_D, MAX_D) == -1 ||\
		wk(v.d3 = recupdbl(line, &i, 'f', ' '), -MAX_D, MAX_D) == -1)
		return (-1);
	tr->ang3 = create_vec(v.d1, v.d2, v.d3);
	if (wk(v.i1 = (int)recupdbl(line, &i, 'd', ','), 0, 255) == -1 ||\
		wk(v.i2 = (int)recupdbl(line, &i, 'd', ','), 0, 255) == -1 ||\
		wk(v.i3 = (int)recupdbl(line, &i, 'd', ' '), 0, 255) == -1)
		return (-1);
	tr->color = get_color_integer(v.i1, v.i2, v.i3);
	if (wk(tr->spec = recupdbl(line, &i, 'f', ' '), 0.0, MAX_D) == -1)
		return (-1);
	if (wk(tr->reflect = recupdbl(line, &i, 'f', '\0'), 0.0, 1.0) == -1)
		return (-1);
	return (0);
}

int			get_triangle(char *line, void **ptr)
{
	t_parse	v;
	int		i;
	t_tr	*tr;

	if (!(tr = malloc(sizeof(t_tr))))
		return (-1);
	i = 2;
	if (wk(v.d1 = recupdbl(line, &i, 'f', ','), -MAX_D, MAX_D) == -1 ||\
		wk(v.d2 = recupdbl(line, &i, 'f', ','), -MAX_D, MAX_D) == -1 ||\
		wk(v.d3 = recupdbl(line, &i, 'f', ' '), -MAX_D, MAX_D) == -1)
		return (-1);
	tr->ang1 = create_vec(v.d1, v.d2, v.d3);
	if (wk(v.d1 = recupdbl(line, &i, 'f', ','), -MAX_D, MAX_D) == -1 ||\
		wk(v.d2 = recupdbl(line, &i, 'f', ','), -MAX_D, MAX_D) == -1 ||\
		wk(v.d3 = recupdbl(line, &i, 'f', ' '), -MAX_D, MAX_D) == -1)
		return (-1);
	if (triangle2(line, tr, i) == -1)
		return (-1);
	*ptr = tr;
	return (0);
}
