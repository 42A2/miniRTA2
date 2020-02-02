/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chng_stretch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 20:42:22 by mbrunel           #+#    #+#             */
/*   Updated: 2020/02/02 03:46:51 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

void	chng_sp(void *ptr, t_ray new)
{
    t_sp *sp;

    sp = (t_sp*)ptr;
    sp->o = mult_vec_d(new.dir, (norm_vec(sub_vec(sp->o, new.o))));
}
void	chng_pl(void *ptr, t_ray new)
{
    t_pl *pl;

    pl = (t_pl*)ptr;
    pl->p = mult_vec_d(new.dir, (norm_vec(sub_vec(pl->p, new.o))));
    
}
void	chng_cy(void *ptr, t_ray new)
{
    t_cy *cy;

    cy = (t_cy*)ptr;
    cy->p = mult_vec_d(new.dir, (norm_vec(sub_vec(cy->p, new.o))));
}
void	chng_tr(void *ptr, t_ray new)
{
    (void)ptr;
    (void)new;
}
void	chng_sq(void *ptr, t_ray new)
{
    t_sq *sq;

    sq = (t_sq*)ptr;
    sq->p = mult_vec_d(new.dir, (norm_vec(sub_vec(sq->p, new.o))));
}

void    stretch_sp(void *ptr, t_ray new)
{
    t_sp *sp;
    t_vec translation;

    sp = (t_sp*)ptr;
    translation = mult_vec_d(new.dir, (norm_vec(sub_vec(sp->o, new.o))));
    sp->r = norm_vec(sub_vec(sp->o, translation));
}

void    stretch_cy(void *ptr, t_ray new)
{
    t_cy *cy;
    t_vec translation;

    cy = (t_cy*)ptr;
    translation = mult_vec_d(new.dir, (norm_vec(sub_vec(cy->p, new.o))));
    cy->r = norm_vec(sub_vec(cy->p, translation));
}

void    stretch_pl(void *ptr, t_ray new)
{
    (void)ptr;
    (void)new;
}

void    stretch_sq(void *ptr, t_ray new)
{
    t_sq *sq;
    t_vec translation;

    sq = (t_sq*)ptr;
    translation = mult_vec_d(new.dir, (norm_vec(sub_vec(sq->p, new.o))));
    sq->h = norm_vec(sub_vec(sq->p, translation));
}

void    stretch_tr(void *ptr, t_ray new)
{
    (void)ptr;
    (void)new;
}