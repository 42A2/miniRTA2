/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_it_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 19:33:33 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/06 02:47:48 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

t_vec	retray(t_vec r, t_vec n)
{
	return (sub_vec(mult_vec_d(mult_vec_d(n, prod_scal(r, n)), 2), r));
}

t_inter	intertr(t_ray ray, void *ptr, double start, double max)
{
	t_tr	tr;
	t_inter	rt;
	t_vec	vec1;
	t_vec	vec2;
	t_vec	edge2;
	t_vec	edge3;
	double	d;
	double	m;
	t_vec	l;
	t_vec	vp;
	t_vec	c;
	int		boo;

	tr = *(t_tr*)ptr;
	boo = 0;
	vec1 = sub_vec(tr.ang2, tr.ang1);
	vec2 = sub_vec(tr.ang3, tr.ang1);
	edge2 = sub_vec(tr.ang3, tr.ang2);
	edge3 = sub_vec(tr.ang1, tr.ang3);
	rt.normal = cross_prod(vec1, vec2);
	m = prod_scal(rt.normal, ray.dir);
	if (d_abs(m) < start)
	{
		rt.inter = 0;
		return (rt);
	}
	else
	{
		l = sub_vec(ray.o, tr.ang1);
		d = prod_scal(rt.normal, l);
		rt.inter = -d / m;
	}
	if (rt.inter < start || rt.inter > max)
		rt.inter = 0;
	rt.ipoint = add_vec(ray.o, mult_vec_d(ray.dir, rt.inter));
	vp = sub_vec(rt.ipoint, tr.ang1);
	c = cross_prod(vec1, vp);
	if (prod_scal(rt.normal, c) < 0)
		boo++;
	vp = sub_vec(rt.ipoint, tr.ang2);
	c = cross_prod(edge2, vp);
	if (prod_scal(rt.normal, c) < 0)
		boo++;
	vp = sub_vec(rt.ipoint, tr.ang3);
	c = cross_prod(edge3, vp);
	if (prod_scal(rt.normal, c) < 0)
		boo++;
	if (boo != 0)
		rt.inter = 0;
	rt.normal = prod_scal(sub_vec(tr.ang1, ray.o), rt.normal)
		< 0 ? rt.normal : mult_vec_d(rt.normal, -1);
	rt.color = tr.color;
	rt.reflect = tr.reflect;
	rt.spec = tr.spec;
	return (rt);
}

t_inter	intercy(t_ray ray, void *ptr, double start, double max)
{
	t_vec	L;
	t_cy	cy;
	t_vec	w;
	double	sqr_omega;
	t_vec	wn;
	double	R;
	t_vec	E;
	double	t;
	t_inter	rt;
	t_vec	F;
	t_vec	Fn;
	double	s;
	t_vec	cp;
	double	cq;
	t_vec	qp;
	int		boo;

	cy = *(t_cy*)ptr;
	boo = 0;
	L = sub_vec(ray.o, cy.p);
	w = cross_prod(ray.dir, cy.dir);
	sqr_omega = prod_scal(w, w);
	if (!sqr_omega)
		rt.inter = 0;
	else
	{
		wn = div_vec_d(w, sqrt(sqr_omega));
		R = d_abs(prod_scal(L, wn));
		if (R > cy.r)
			rt.inter = 0;
		else
		{
			E = cross_prod(L, cy.dir);
			t = prod_scal(mult_vec_d(E, -1), wn) / sqrt(sqr_omega);
			F = cross_prod(wn, cy.dir);
			Fn = div_vec_d(F, norm_vec(F));
			s = sqrt(cy.r * cy.r - R * R) / d_abs(prod_scal(ray.dir, Fn));
			rt.inter = t - s;
			if (norm_vec(add_vec(cy.dir, ray.dir)) < norm_vec(add_vec(mult_vec_d(cy.dir, -1), ray.dir)))
				mult_vec_d(cy.dir, -1);
			if (norm_vec(sub_vec(add_vec(ray.o, mult_vec_d(ray.dir, rt.inter)), cy.p)) > sqrt(cy.h / 2 * cy.h / 2 + cy.r * cy.r))
			{
				rt.inter = t + s;
				boo = 1;
				if (norm_vec(sub_vec(add_vec(ray.o, mult_vec_d(ray.dir, rt.inter)), cy.p)) > sqrt(cy.h / 2 * cy.h / 2 + cy.r * cy.r))
					rt.inter = 0;
			}
			else if (rt.inter < 0)
			{
				rt.inter = t + s;
				boo = 1;
			}
		}
	}
	if (rt.inter < start || rt.inter > max)
		rt.inter = 0;
	rt.ipoint = add_vec(ray.o, mult_vec_d(ray.dir, rt.inter));
	rt.color = cy.color;
	rt.reflect = cy.reflect;
	rt.spec = cy.spec;
	cp = sub_vec(rt.ipoint, cy.p);
	cq = prod_scal(cp, cy.dir);
	qp = sub_vec(cp, mult_vec_d(cy.dir, cq));
	rt.normal = boo ? cy.dir : div_vec_d(qp, cy.r);
	return (rt);
}

t_inter	interpl(t_ray ray, void *ptr, double start, double max)
{
	t_pl	pl;
	t_inter	rt;
	t_vec	l;
	double	d;
	double	m;

	pl = *(t_pl*)ptr;
	m = prod_scal(pl.dir, ray.dir);
	if (d_abs(m) < start)
	{
		rt.inter = 0;
		return (rt);
	}
	else
	{
		l = sub_vec(ray.o, pl.p);
		d = prod_scal(pl.dir, l);
		rt.inter = -d / m;
	}
	if (rt.inter > start && rt.inter < max)
		rt.ipoint = add_vec(ray.o, mult_vec_d(ray.dir, rt.inter));
	else
	{
		rt.inter = 0;
		return (rt);
	}
	rt.reflect = pl.reflect;
	rt.spec = pl.spec;
	rt.color = pl.color;
	rt.normal = prod_scal(sub_vec(pl.p, ray.o), pl.dir) < 0 ? pl.dir : mult_vec_d(pl.dir, -1);
	return (rt);
}

t_inter	intersp(t_ray ray, void *ptr, double start, double max)
{
	double	t1;
	double	t2;
	double	a;
	double	b;
	double	c;
	double	dis;
	t_inter	rt;
	t_sp	sp;
	t_vec	oc;

	sp = *(t_sp*)ptr;
	oc = sub_vec(ray.o, sp.o);
	a = prod_scal(ray.dir, ray.dir);
	b = 2 * prod_scal(oc, ray.dir);
	c = prod_scal(oc, oc) - sp.r * sp.r;
	dis = b * b - 4 * a * c;
	if (dis > 0)
	{
		t1 = (-b + sqrt(dis)) / (2 * a);
		t2 = (-b - sqrt(dis)) / (2 * a);
		if (t1 < 0)
			rt.inter = t2;
		else if (t2 < 0)
			rt.inter = t1;
		else
			rt.inter = t1 < t2 ? t1 : t2;
	}
	else if (dis == 0)
		rt.inter = -b / 2 * a;
	else
		rt.inter = 0;
	rt.color = sp.color;
	rt.spec = sp.spec;
	rt.reflect = sp.reflect;
	if (rt.inter < start || rt.inter > max)
		rt.inter = 0;
	rt.ipoint = add_vec(ray.o, mult_vec_d(ray.dir, rt.inter));
	rt.normal = normalize(sub_vec(rt.ipoint, sp.o));
	return (rt);
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

static void	*fill_img_threading(void *data)
{
	t_data	dt;
	int		i;
	int		j;
	int		res_y;
	t_ray	ray;

	dt = *(t_data*)data;
	ray.o = dt.p.cam[dt.i_img].o;
	res_y = dt.i == 7 ? dt.p.vp.res_y : dt.p.vp.res_y / 8 * (dt.i + 1);
	i = dt.p.vp.res_y / 8 * dt.i - 1;
	while (++i < res_y)
	{
		j = -1;
		while (++j < dt.p.vp.res_x)
		{
			ray.dir = cam_rot(c_to_vp((double)i, (double)j, dt.p.vp, dt.p.cam[dt.i_img].dist), dt.p.cam[dt.i_img].vec_dir, dt.ang);
			dt.img[i * dt.len + j] = find_pix_color(ray, dt.p, dt.p.bonus.recurse_reflect);
			if (dt.p.bonus.filter_type)
				filter(dt.p.bonus.filter_type, dt.p.bonus.filter_strength, dt.img, i * dt.len + j);
		}
	}
	free(data);
	return (NULL);
}

static void	*create_data(t_p p, t_vec ang, int len, int i, int i_img, int *img)
{
	t_data	*data;
	if (!(data = malloc(sizeof(t_data))))
	{
		ft_fprintf(2, "Error in allocation of thread %d\n", i);
		return (NULL);
	}
	data->p = p;
	data->ang = ang;
	data->len = len;
	data->i = i;
	data->i_img = i_img;
	data->img = img;
	return (data);
}

void		fill_img(int *img, t_info info, t_p p, int i_img)
{
	int			i;
	int			len;
	t_vec		ang;
	pthread_t	threads[8];
	int			ret;
	t_data		*data;

	len = info.l / 4;
	i = -1;
	ang.x = acos(p.cam[i_img].vec_dir.z / sqrt(p.cam[i_img].vec_dir.y * p.cam[i_img].vec_dir.y + p.cam[i_img].vec_dir.z * p.cam[i_img].vec_dir.z));
	ang.y = acos(p.cam[i_img].vec_dir.z / sqrt(p.cam[i_img].vec_dir.x * p.cam[i_img].vec_dir.x + p.cam[i_img].vec_dir.z * p.cam[i_img].vec_dir.z));
	while (++i < 8)
	{
		data = create_data(p, ang, len, i, i_img, img);
		if (data)
			ret = pthread_create(threads + i, NULL, &fill_img_threading, data);
		if (ret || !data)
		{
			if (data)
				ft_fprintf(2, "Error in creation of thread %d\n", i);
			while (i-- > 0)
			{
				pthread_join(threads[i], NULL);
				return ;
			}
		}
	}
	i = -1;
	while (++i < 8)
	{
		pthread_join(threads[i], NULL);
	}
}
