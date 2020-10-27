/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:35:55 by mbrunel           #+#    #+#             */
/*   Updated: 2020/10/15 20:53:19 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	retray(t_vec r, t_vec n)
{
	return (sub_vec(mult_vec_d(mult_vec_d(n, prod_scal(r, n)), 2), r));
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
