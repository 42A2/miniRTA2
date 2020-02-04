/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_gets3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 04:27:37 by mbrunel           #+#    #+#             */
/*   Updated: 2020/02/04 04:34:49 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

static int	cylindre2(char *line, t_cy *cy, int i)
{
	t_parse v;

	if (wk(v.d1 = recupdbl(line, &i, 'f', ','), -1, 1) == -1 ||\
		wk(v.d2 = recupdbl(line, &i, 'f', ','), -1, 1) == -1 ||\
		wk(v.d3 = recupdbl(line, &i, 'f', ' '), -1, 1) == -1)
		return (-1);
	v.d1 = !v.d1 ? __DBL_MIN__ : v.d1;
	v.d2 = !v.d2 ? __DBL_MIN__ : v.d2;
	v.d3 = !v.d3 ? __DBL_MIN__ : v.d3;
	cy->dir = normalize(create_vec(v.d1, v.d2, v.d3));
	if (wk(cy->r = (recupdbl(line, &i, 'f', ' ') / 2), 0.0, MAX_D) == -1)
		return (-1);
	if (wk(cy->h = recupdbl(line, &i, 'f', ' '), 0.0, MAX_D) == -1)
		return (-1);
	if (wk(v.i1 = (int)recupdbl(line, &i, 'i', ','), 0, 255) == -1 ||\
		wk(v.i2 = (int)recupdbl(line, &i, 'i', ','), 0, 255) == -1 ||\
		wk(v.i3 = (int)recupdbl(line, &i, 'i', ' '), 0, 255) == -1)
		return (-1);
	cy->rgb = create_vec(v.i1, v.i2, v.i3);
	cy->color = get_color_integer(v.i1, v.i2, v.i3);
	if (wk(cy->spec = recupdbl(line, &i, 'f', ' '), 0.0, MAX_D) == -1)
		return (-1);
	if (wk(cy->reflect = recupdbl(line, &i, 'f', '\0'), 0.0, 1.0) == -1)
		return (-1);
	return (0);
}

int			get_cylindre(char *line, void **ptr)
{
	t_parse	v;
	int		i;
	t_cy	*cy;

	if (!(cy = malloc(sizeof(t_cy))))
		return (-1);
	i = 2;
	if (wk(v.d1 = recupdbl(line, &i, 'f', ','), -MAX_D, MAX_D) == -1 ||\
		wk(v.d2 = recupdbl(line, &i, 'f', ','), -MAX_D, MAX_D) == -1 ||\
		wk(v.d3 = recupdbl(line, &i, 'f', ' '), -MAX_D, MAX_D) == -1)
		return (-1);
	cy->p = create_vec(v.d1, v.d2, v.d3);
	if (cylindre2(line, cy, i) == -1)
		return (-1);
	*ptr = cy;
	return (0);
}

static int	square2(char *line, t_sq *sq, int i)
{
	t_parse v;

	if (wk(v.d1 = recupdbl(line, &i, 'f', ','), -1, 1) == -1 ||\
		wk(v.d2 = recupdbl(line, &i, 'f', ','), -1, 1) == -1 ||\
		wk(v.d3 = recupdbl(line, &i, 'f', ' '), -1, 1) == -1)
		return (-1);
	if (wk(sq->h = recupdbl(line, &i, 'f', ' '), 0.0, MAX_D) == -1)
		return (-1);
	sq->dir = create_vec(v.d1, v.d2, v.d3);
	if (wk(v.i1 = (int)recupdbl(line, &i, 'i', ','), 0, 255) == -1 ||\
		wk(v.i2 = (int)recupdbl(line, &i, 'i', ','), 0, 255) == -1 ||\
		wk(v.i3 = (int)recupdbl(line, &i, 'i', ' '), 0, 255) == -1)
		return (-1);
	sq->color = get_color_integer(v.i1, v.i2, v.i3);
	sq->d = -1 * prod_scal(sq->dir, sq->p);
	if (wk(sq->spec = recupdbl(line, &i, 'f', ' '), 0.0, MAX_D) == -1)
		return (-1);
	if (wk(sq->reflect = recupdbl(line, &i, 'f', '\0'), 0.0, 1.0) == -1)
		return (-1);
	return (0);
}

int			get_square(char *line, void **ptr)
{
	t_parse	v;
	int		i;
	t_sq	*sq;

	if (!(sq = malloc(sizeof(t_sq))))
		return (-1);
	i = 2;
	if (wk(v.d1 = recupdbl(line, &i, 'f', ','), -MAX_D, MAX_D) == -1 ||\
		wk(v.d2 = recupdbl(line, &i, 'f', ','), -MAX_D, MAX_D) == -1 ||\
		wk(v.d3 = recupdbl(line, &i, 'f', ' '), -MAX_D, MAX_D) == -1)
		return (-1);
	sq->p = create_vec(v.d1, v.d2, v.d3);
	if (square2(line, sq, i) == -1)
		return (-1);
	*ptr = sq;
	return (0);
}
