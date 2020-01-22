/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 05:14:16 by mbrunel           #+#    #+#             */
/*   Updated: 2020/01/22 15:59:21 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

int get_p(t_p *p, char *path)
{
	int fd;
	int status;
	int type;
	int incs[20];
	char *buf;
	char *shrs;
	
	shrs = "spyt#RlAcb";
	if ((fd = open(path, O_RDWR)) == -1)
		return error(NULL, "open_eror\n");
	ft_memset(incs, 0, sizeof(int) * 20);
	while ((status = get_next_line(fd, &buf)) > 0 && ++incs[LINES_OF_FILE] < MAX_LENGTHG_FILE)
	{
		if ((type = (chr(shrs, buf[0]))) == -1)
			return (error(buf, "object not found in database\n"));
		else if (shrs[type] == '#' || buf[0] == '\0')
			continue ;
		else if (type == RESOLUTION && (incs[RESOLUTION] || get_vp(buf, &(p->vp)) == -1))
			return (error(buf, "the vp is badly registered\n"));
		else if (type <= AMBIENT && type >= POINT && ((incs[AMBIENT] == 1 && type == AMBIENT) || (get_lights(buf, &(p->lights[incs[AMBIENT] + incs[POINT]]), type, &(p->bg_color)) == -1)))
			return (error(buf, "light parameters are badly registered\n"));
		else if (type == CAMERA && ft_isspace(buf[1]) && (get_cam(buf, &(p->cam[incs[CAMERA]])) == -1))
			return (error(buf, "camera parameters are badly registered\n"));
		else if (type == CAMERA && buf[1] == 'y')
			type = CYLINDRE;
		else if (type == BONUS && (incs[BONUS] || get_bonus(buf, &(p->bonus)) == -1))
			return (error(buf, "bonus parameters are badly registered\n"));
		if (type < NB_FORM && (get_obj[type])(buf, &(p->objs[incs[NB_FORM]].o)) == -1)
			return (error(buf, "objs parameters are badly registered\n"));
		if (type < NB_FORM)
			p->objs[incs[NB_FORM]].type = type;
		incs[type]++;
		if (type < NB_FORM)
			incs[NB_FORM]++;
		free(buf);
	}
	p->nb_cam = incs[CAMERA];
	p->nb_lights = incs[POINT] + incs[AMBIENT];
	p->nb_objs = incs[NB_FORM];
	return (0);
}
