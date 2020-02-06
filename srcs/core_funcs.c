/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 05:05:56 by mbrunel           #+#    #+#             */
/*   Updated: 2020/02/06 05:15:07 by mbrunel          ###   ########.fr       */
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

t_vec		light_intensity(t_inter *min, t_light light, t_p *p, t_vec invray)
{
	t_vec	i;
	double	coeff;
	double	p_scal;
	t_vec	l;
	t_inter	closest;
	t_ray	shadow;
	double	max;

	i = create_vec(0, 0, 0);
	l = light.type == POINT ? sub_vec(light.pos, min->ipoint) : mult_vec_d(light.pos, -1);
	max = light.type == POINT ? 1 : __DBL_MAX__;
	shadow.o = min->ipoint;
	shadow.dir = l;
	closest = min_inter(shadow, p, MIN_SHADOW, max);
	if (closest.inter)
		return (i);
	p_scal = prod_scal(min->normal, l);
	if (p_scal > 0)
	{
		coeff = light.intensity * p_scal / (norm_vec(min->normal) * norm_vec(l));
		i = create_vec(coeff * light.rgb.x / 255, coeff * light.rgb.y / 255, coeff * light.rgb.z / 255);
	}
	if (min->spec != -1)
	{
		l = sub_vec(mult_vec_d(mult_vec_d(min->normal, prod_scal(min->normal, l)), 2), l);
		if ((p_scal = prod_scal(l, invray)) > 0)
		{
			coeff = light.intensity * pow(p_scal / (norm_vec(l) * norm_vec(invray)), min->spec);
			i = add_vec(i, mult_vec_d(i, coeff));
		}
	}
	return (i);
}

int			find_pix_color(t_ray ray, t_p *p, int depth)
{
	t_vec	intensity;
	t_inter	min;
	int	i;
	int	color;

	i = -1;
	intensity = create_vec(0.0, 0.0, 0.0);
	min = min_inter(ray, p, MIN_SHADOW, __DBL_MAX__);
	if (!min.inter)
		return (BG_COLOR);
	while (++i < p->nb_lights)
	{
		intensity = add_vec(intensity, ((p->lights[i].type != AMBIENT) ? light_intensity(&min, p->lights[i], &p, mult_vec_d(ray.dir, -1)) : mult_vec_d(div_vec(p->lights[i].rgb, create_vec(255, 255, 255)), p->lights[i].intensity)));
	}
	color = prod_color_vec(min.color, intensity);
	if (!depth || min.reflect <= 0)
		return (color);
	ray.dir = retray(mult_vec_d(ray.dir, -1), min.normal);
	ray.o = min.ipoint;
	return (add_color_to_color(prod_color_float(color, 1 - min.reflect), prod_color_float(find_pix_color(ray, p, depth - 1), min.reflect)));
}
