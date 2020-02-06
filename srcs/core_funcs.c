/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 05:05:56 by mbrunel           #+#    #+#             */
/*   Updated: 2020/02/06 06:07:13 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

t_inter		min_inter(t_ray ray, t_p *p, double start, double max)
{
	t_inter	min;
	t_inter	inter;
	int		j;

	j = -1;
	min.color = BG_COLOR;
	min.inter = max;
	while (++j < p->nb_objs)
	{
		inter = (g_get_inter[p->objs[j].type])(ray, p->objs[j].o, start, max);
		if (inter.inter < min.inter && inter.inter > start)
		{
			min = inter;
			min.i_obj = j;
		}
	}
	min.inter = (min.inter == max ? 0 : min.inter);
	return (min);
}

static void	light2(t_lightvar *v, t_light *light, t_inter *min, t_p *p)
{
	v->i = create_vec(0, 0, 0);
	v->l = light->type == POINT ? sub_vec(light->pos\
	, min->ipoint) : mult_vec_d(light->pos, -1);
	v->max = light->type == POINT ? 1 : __DBL_MAX__;
	v->shadow.o = min->ipoint;
	v->shadow.dir = v->l;
	v->closest = min_inter(v->shadow, p, MIN_SHADOW, v->max);
}

t_vec		light_intensity(t_inter *min, t_light *light, t_p *p, t_vec invray)
{
	t_lightvar v;

	light2(&v, light, min, p);
	if (v.closest.inter)
		return (v.i);
	v.p_scal = prod_scal(min->normal, v.l);
	if (v.p_scal > 0)
	{
		v.coeff = light->intensity * v.p_scal / (norm_vec(min->normal)\
		* norm_vec(v.l));
		v.i = create_vec(v.coeff * light->rgb.x / 255, v.coeff\
		* light->rgb.y / 255, v.coeff * light->rgb.z / 255);
	}
	if (min->spec != -1)
	{
		v.l = sub_vec(mult_vec_d(mult_vec_d(min->normal\
		, prod_scal(min->normal, v.l)), 2), v.l);
		if ((v.p_scal = prod_scal(v.l, invray)) > 0)
		{
			v.coeff = light->intensity\
			* pow(v.p_scal / (norm_vec(v.l) * norm_vec(invray)), min->spec);
			v.i = add_vec(v.i, mult_vec_d(v.i, v.coeff));
		}
	}
	return (v.i);
}

int			find_pix_color(t_ray ray, t_p *p, int depth)
{
	t_vec	intensity;
	t_inter	min;
	int		i;
	int		color;

	i = -1;
	intensity = create_vec(0.0, 0.0, 0.0);
	min = min_inter(ray, p, MIN_SHADOW, __DBL_MAX__);
	if (!min.inter)
		return (BG_COLOR);
	while (++i < p->nb_lights)
		intensity = add_vec(intensity, ((p->lights[i].type != AMBIENT)\
		? light_intensity(&min, &(p->lights[i]), p, mult_vec_d(ray.dir, -1))\
		: mult_vec_d(div_vec(p->lights[i].rgb, create_vec(255, 255, 255))\
		, p->lights[i].intensity)));
	color = prod_color_vec(min.color, intensity);
	if (!depth || min.reflect <= 0)
		return (color);
	ray.dir = retray(mult_vec_d(ray.dir, -1), min.normal);
	ray.o = min.ipoint;
	return (add_color_to_color(prod_color_float(color, 1 - min.reflect)\
	, prod_color_float(find_pix_color(ray, p, depth - 1), min.reflect)));
}
