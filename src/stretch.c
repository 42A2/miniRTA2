/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stretch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 03:35:20 by mbrunel           #+#    #+#             */
/*   Updated: 2020/10/15 20:53:19 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	stretch_sp(void *ptr, t_ray new)
{
	t_sp	*sp;
	t_vec	translation;

	sp = (t_sp*)ptr;
	translation = add_vec(new.o\
	, mult_vec_d(new.dir, (norm_vec(sub_vec(sp->o, new.o)))));
	sp->r = norm_vec(sub_vec(sp->o, translation));
}

void	stretch_cy(void *ptr, t_ray new)
{
	t_cy	*cy;
	t_vec	translation;

	cy = (t_cy*)ptr;
	translation = add_vec(new.o, mult_vec_d(new.dir\
	, (norm_vec(sub_vec(cy->p, new.o)))));
	cy->r = norm_vec(sub_vec(cy->p, translation));
	cy->h = norm_vec(sub_vec(cy->p, translation));
}

void	stretch_pl(void *ptr, t_ray new)
{
	(void)ptr;
	(void)new;
}

void	stretch_sq(void *ptr, t_ray new)
{
	t_sq	*sq;
	t_vec	translation;

	sq = (t_sq*)ptr;
	translation = add_vec(new.o, mult_vec_d(new.dir\
	, (norm_vec(sub_vec(sq->p, new.o)))));
	sq->h = norm_vec(sub_vec(sq->p, translation)) * 2;
}

void	stretch_tr(void *ptr, t_ray new)
{
	t_tr	*tr;
	t_vec	new_pos;
	double	dist1;
	double	dist2;
	double	dist3;

	tr = (t_tr*)ptr;
	new_pos = add_vec(new.o, mult_vec_d(new.dir\
	, (norm_vec(sub_vec(tr->ang1, new.o)))));
	dist1 = norm_vec(sub_vec(tr->ang1, tr->click));
	dist2 = norm_vec(sub_vec(tr->ang2, tr->click));
	dist3 = norm_vec(sub_vec(tr->ang3, tr->click));
	if (dist1 <= dist2 && dist1 <= dist3)
		tr->ang1 = new_pos;
	else if (dist2 <= dist3)
		tr->ang2 = new_pos;
	else
		tr->ang3 = new_pos;
}
