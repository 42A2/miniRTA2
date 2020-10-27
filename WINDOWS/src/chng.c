/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chng.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 20:42:22 by mbrunel           #+#    #+#             */
/*   Updated: 2020/10/15 20:53:19 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	chng_sp(void *ptr, t_ray new)
{
	t_sp	*sp;

	sp = (t_sp*)ptr;
	sp->o = add_vec(new.o,\
	mult_vec_d(new.dir, (norm_vec(sub_vec(sp->o, new.o)))));
}

void	chng_pl(void *ptr, t_ray new)
{
	t_pl	*pl;

	pl = (t_pl*)ptr;
	pl->p = add_vec(new.o,\
	mult_vec_d(new.dir, (norm_vec(sub_vec(pl->p, new.o)))));
}

void	chng_cy(void *ptr, t_ray new)
{
	t_cy	*cy;

	cy = (t_cy*)ptr;
	cy->p = add_vec(new.o,\
	mult_vec_d(new.dir, (norm_vec(sub_vec(cy->p, new.o)))));
}

void	chng_tr(void *ptr, t_ray new)
{
	t_tr	*tr;
	t_tr	trans;
	t_vec	old_g;
	t_vec	new_g;

	tr = (t_tr*)ptr;
	old_g.x = (tr->ang1.x + tr->ang2.x + tr->ang3.x) / 3;
	old_g.y = (tr->ang1.y + tr->ang2.y + tr->ang3.y) / 3;
	old_g.z = (tr->ang1.z + tr->ang2.z + tr->ang3.z) / 3;
	new_g = add_vec(new.o,\
	mult_vec_d(new.dir, (norm_vec(sub_vec(tr->ang1, new.o)))));
	trans.ang1 = add_vec(new_g, sub_vec(tr->ang1, old_g));
	trans.ang2 = add_vec(new_g, sub_vec(tr->ang2, old_g));
	trans.ang3 = add_vec(new_g, sub_vec(tr->ang3, old_g));
	*tr = trans;
}

void	chng_sq(void *ptr, t_ray new)
{
	t_sq	*sq;

	sq = (t_sq*)ptr;
	sq->p = add_vec(new.o,\
	mult_vec_d(new.dir, (norm_vec(sub_vec(sq->p, new.o)))));
}
