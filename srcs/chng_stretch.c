/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chng_stretch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 20:42:22 by mbrunel           #+#    #+#             */
/*   Updated: 2020/02/03 04:33:18 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

void	chng_sp(void *ptr, t_ray new)
{
    t_sp *sp;

    sp = (t_sp*)ptr;
    sp->o = add_vec(new.o, mult_vec_d(new.dir, (norm_vec(sub_vec(sp->o, new.o)))));
}
void	chng_pl(void *ptr, t_ray new)
{
    t_pl *pl;

    pl = (t_pl*)ptr;
    pl->p = add_vec(new.o, mult_vec_d(new.dir, (norm_vec(sub_vec(pl->p, new.o)))));
    
}
void	chng_cy(void *ptr, t_ray new)
{
    t_cy *cy;

    cy = (t_cy*)ptr;
    cy->p = add_vec(new.o, mult_vec_d(new.dir, (norm_vec(sub_vec(cy->p, new.o)))));
}
void	chng_tr(void *ptr, t_ray new)
{
    t_tr *tr;
    t_tr trans;
    t_vec old_g;
    t_vec new_g;

    tr = (t_tr*)ptr;
    old_g.x = (tr->ang1.x + tr->ang2.x + tr->ang3.x) / 3;
    old_g.y = (tr->ang1.y + tr->ang2.y + tr->ang3.y) / 3;
    old_g.z = (tr->ang1.z + tr->ang2.z + tr->ang3.z) / 3;
    new_g = add_vec(new.o, mult_vec_d(new.dir, (norm_vec(sub_vec(tr->ang1, new.o)))));
    trans.ang1 = add_vec(new_g, sub_vec(tr->ang1, old_g));
    trans.ang2 = add_vec(new_g, sub_vec(tr->ang2, old_g));
    trans.ang3 = add_vec(new_g, sub_vec(tr->ang3, old_g));
    *tr = trans;
}
void	chng_sq(void *ptr, t_ray new)
{
    t_sq *sq;

    sq = (t_sq*)ptr;
    sq->p = add_vec(new.o, mult_vec_d(new.dir, (norm_vec(sub_vec(sq->p, new.o)))));
}

void    stretch_sp(void *ptr, t_ray new)
{
    t_sp *sp;
    t_vec translation;

    sp = (t_sp*)ptr;
    translation = add_vec(new.o, mult_vec_d(new.dir, (norm_vec(sub_vec(sp->o, new.o)))));
    sp->r = norm_vec(sub_vec(sp->o, translation));
}

void    stretch_cy(void *ptr, t_ray new)
{
    t_cy *cy;
    t_vec translation;

    cy = (t_cy*)ptr;
    translation = add_vec(new.o, mult_vec_d(new.dir, (norm_vec(sub_vec(cy->p, new.o)))));
    cy->r = norm_vec(sub_vec(cy->p, translation));
    cy->h = norm_vec(sub_vec(cy->p, translation));
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
    translation = add_vec(new.o, mult_vec_d(new.dir, (norm_vec(sub_vec(sq->p, new.o)))));
    sq->h = norm_vec(sub_vec(sq->p, translation)) * 2;
}

void    stretch_tr(void *ptr, t_ray new)
{
    t_tr *tr;
    t_vec new_pos;
    double dist1;
    double dist2;
    double dist3;

    tr = (t_tr*)ptr;
    new_pos = add_vec(new.o, mult_vec_d(new.dir, (norm_vec(sub_vec(tr->ang1, new.o)))));
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