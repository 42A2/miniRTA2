/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_gets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 01:06:04 by mbrunel           #+#    #+#             */
/*   Updated: 2019/12/13 02:15:01 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

int		get_vp(char *line, t_vp *vp)
{
	int i;
	
	i = 0;
	if (wk(vp->res_x = (int)recupfloat(line, &i, 'd', ' '), 4, RES_X_MAX) == -1)
		return (-1);
	if (wk(vp->res_y = (int)recupfloat(line, &i, 'd', '\0'), 4, RES_Y_MAX) == -1)
		return (-1);
	return (0);
}

int		get_lights(char *line, t_light *light, int type)
{
	light->type = type;
	light->rgb = create_vec()
	return (0);
}

int		get_cam(char *line, t_cam *cam)
{
	return (0);
}

int		get_sphere(char *line, void **ptr)
{
	return (0);
}

int		get_plane(char *line, void **ptr)
{
	return (0);
}
