/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:35:55 by mbrunel           #+#    #+#             */
/*   Updated: 2020/02/06 04:17:51 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

t_vec	retray(t_vec r, t_vec n)
{
	return (sub_vec(mult_vec_d(mult_vec_d(n, prod_scal(r, n)), 2), r));
}

t_inter	min_inter(t_ray ray, t_p p, double start, double max)
{
	t_inter	min;
	t_inter	inter;
	int		j;

	j = -1;
	min.color = BG_COLOR;
	min.inter = max;
	while (++j < p.nb_objs)
	{
		inter = (g_get_inter[p.objs[j].type])(ray, p.objs[j].o, start, max);
		if (inter.inter < min.inter && inter.inter > start)
		{
			min = inter;
			min.i_obj = j;
		}
	}
	min.inter = (min.inter == max ? 0 : min.inter);
	return (min);
}

t_vec	light_intensity(t_vec ipoint, t_vec normal, t_light light, t_p p, double spec, t_vec invray)
{
	t_vec	i;
	double	coeff;
	double	p_scal;
	t_vec	l;
	t_inter	closest;
	t_ray	shadow;
	double	max;

	i = create_vec(0, 0, 0);
	l = light.type == POINT ? sub_vec(light.pos, ipoint) : mult_vec_d(light.pos, -1);
	max = light.type == POINT ? 1 : __DBL_MAX__;
	shadow.o = ipoint;
	shadow.dir = l;
	closest = min_inter(shadow, p, MIN_SHADOW, max);
	if (closest.inter)
		return (i);
	p_scal = prod_scal(normal, l);
	if (p_scal > 0)
	{
		coeff = light.intensity * p_scal / (norm_vec(normal) * norm_vec(l));
		i = create_vec(coeff * light.rgb.x / 255, coeff * light.rgb.y / 255, coeff * light.rgb.z / 255);
	}
	if (spec != -1)
	{
		l = sub_vec(mult_vec_d(mult_vec_d(normal, prod_scal(normal, l)), 2), l);
		if ((p_scal = prod_scal(l, invray)) > 0)
		{
			coeff = light.intensity * pow(p_scal / (norm_vec(l) * norm_vec(invray)), spec);
			i = add_vec(i, mult_vec_d(i, coeff));
		}
	}
	return (i);
}

int		find_pix_color(t_ray ray, t_p p, int depth)
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
	while (++i < p.nb_lights)
	{
		intensity = add_vec(intensity, ((p.lights[i].type != AMBIENT) ? light_intensity(min.ipoint, min.normal, p.lights[i], p, min.spec, mult_vec_d(ray.dir, -1)) : mult_vec_d(div_vec(p.lights[i].rgb, create_vec(255, 255, 255)), p.lights[i].intensity)));
	}
	color = prod_color_vec(min.color, intensity);
	if (!depth || min.reflect <= 0)
		return (color);
	ray.dir = retray(mult_vec_d(ray.dir, -1), min.normal);
	ray.o = min.ipoint;
	return (add_color_to_color(prod_color_float(color, 1 - min.reflect), prod_color_float(find_pix_color(ray, p, depth - 1), min.reflect)));
}

t_vec	c_to_vp(double i, double j, t_vp vp, double dist)
{
	t_vec	dir;
	int		mid;

	mid = vp.res_x < vp.res_y ? vp.res_x : vp.res_y;
	dir.x = (j - vp.res_x / 2.0) * (VP_W / mid);
	dir.y = (vp.res_y / 2.0 - i) * (VP_H / mid);
	dir.z = dist;
	return (normalize(dir));
}

t_vec	cam_rot(t_vec dir, t_vec cam, t_vec ang)
{
	t_vec	tmp;
	if (cam.z < 0)
		ang.y += M_PI;
	if (cam.x > 0)
		ang.y = M_PI * 2 - ang.y;
	if (cam.y < 0)
		ang.x = M_PI * 2 - ang.x;
	tmp.x = dir.x;
	tmp.y = sin(ang.x) * dir.z + cos(ang.x) * dir.y;
	tmp.z = cos(ang.x) * dir.z - sin(ang.x) * dir.y;
	dir = tmp;
	tmp.x = cos(ang.y) * dir.x - sin(ang.y) * dir.z;
	tmp.y = dir.y;
	tmp.z = sin(ang.y) * dir.x + cos(ang.y) * dir.z;
	return (normalize(tmp));
}

int		check_diff(int i, int j, int *tab, int len, double delta)
{
	int	k;
	int	m;

	k = -2;
	while (++k < 2)
	{
		m = -2;
		while (++m < 2)
			if (comp_cols(tab[(i - k) * len + (j - m)], tab[i * len + j], delta) == -1)
				return (-1);
	}
	return (0);
}

int		recalc_img(int i, int j, t_p p, int actualpix, int i_img, t_vec ang)
{
	int		nb;
	int		*color;
	t_ray	ray;
	int		k;
	int		m;
	int		n;

	nb = ((p.bonus.coeff_aliasing * 2) - 1) * ((p.bonus.coeff_aliasing * 2) - 1);
	if (!(color = malloc(nb * sizeof(int))))
		exit(error(NULL, "memory error\n"));
	n = 0;
	ray.o = p.cam[i_img].o;
	k = -p.bonus.coeff_aliasing;
	while (++k < p.bonus.coeff_aliasing)
	{
		m = -p.bonus.coeff_aliasing;
		while (++m < p.bonus.coeff_aliasing)
		{
			if (k || m)
			{
				ray.dir = cam_rot(c_to_vp((double)(((double)k / (p.bonus.coeff_aliasing) * 2)) + i, (double)(j + ((double)m / (p.bonus.coeff_aliasing * 2))), p.vp, p.cam[i_img].dist), p.cam[i_img].vec_dir, ang);
				color[n] = find_pix_color(ray, p, p.bonus.recurse_reflect);
				if (p.bonus.filter_type)
					filter(p.bonus.filter_type, p.bonus.filter_strength, color, n);
			}
			else
			{
				color[n] = actualpix;
				if (p.bonus.filter_type)
					filter(p.bonus.filter_type, p.bonus.filter_strength, color, n);
			}
			n++;
		}
	}
	return (mid_color(color, nb));
}

void	aliasing(int *img, int len, t_p p, int i_img, t_vec ang)
{
	int	i;
	int	j;

	i = 0;
	while (++i < p.vp.res_y - 1)
	{
		j = 0;
		while (++j < p.vp.res_x - 1)
			if (check_diff(i, j, img, len, p.bonus.delta_aliasing) == -1)
				img[i * len + j] = recalc_img(i, j, p, img[i * len + j], i_img, ang);
	}
}