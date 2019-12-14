/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 05:14:16 by mbrunel           #+#    #+#             */
/*   Updated: 2019/12/14 15:06:50 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

int get_p(t_p *p, char *path)
{
	int fd;
	int status;
	int type;
	int incs[10];
	char *buf;
	char *shrs;
	
	shrs = "spRlAc#\n";
	if (!(fd = open(path, O_RDWR)))
		return error(NULL, "open_eror\n");
	ft_memset(incs, 0, sizeof(int) * 10);
	while ((status = get_next_line(fd, &buf)) > 0 && ++incs[LINES_OF_FILE] < MAX_LENGTHG_FILE)
	{
		printf("a\n");
		if ((type = (chr(shrs, buf[0]))) == -1)
			return (error(buf, "object not found in database\n"));
		else if (shrs[type] == '#' || shrs[type] == '\n')
			continue ;
		else if (type == RESOLUTION && (incs[RESOLUTION] || get_vp(buf, &(p->vp)) == -1))
			return (error(buf, "the vp is badly registered\n"));
		else if (type <= AMBIENT && type >= POINT && ((incs[AMBIENT] == 1 && type == AMBIENT) || (get_lights(buf, &(p->lights[incs[AMBIENT] + incs[POINT]]), type) == -1)))
			return (error(buf, "light parameters are badly registered\n"));
		else if (type == CAMERA && (get_cam(buf, &(p->cam[incs[CAMERA]])) == -1))
			return (error(buf, "camera parameters are badly registered\n"));
		else if (type < NB_FORM && (get_obj[type])(buf, &(p->objs[incs[type]].o)) == -1)
			return (error(buf, "objs parameters are badly registered\n"));
		if (type < NB_FORM)
			p->objs[incs[type]].type = type;
		incs[type]++;
		free(buf);
	}
	p->nb_cam = incs[CAMERA];
	p->nb_lights = incs[POINT] + incs[AMBIENT];
	p->nb_objs = incs[SPHERE] + incs[PLANE];
	return (0);
}
/*
int	main()
{
	t_p p;
	int i = -1;
	get_p(&p, "../file.rt");
	printf("res : %d %d\n", p.vp.res_x, p.vp.res_y);
	while (++i < p.nb_lights)
		printf("light %d : %f %f %f		%f		%f %f %f	%d	%x\n", i, p.lights[i].pos.x, p.lights[i].pos.y, p.lights[i].pos.z, p.lights[i].intensity, p.lights[i].rgb.x, p.lights[i].rgb.y, p.lights[i].rgb.z, p.lights[i].type,p.lights[i].color);
	i = -1; 
	while (++i < p.nb_cam)
		printf("cam %d : %f %f %f		%f 		%f %f %f\n", i, p.cam[i].o.x, p.cam[i].o.y, p.cam[i].o.z, p.cam[i].fov, p.cam[i].vec_dir.x, p.cam[i].vec_dir.y, p.cam[i].vec_dir.z);
	i = -1;
	while (++i < p.nb_objs)
		printf("obj %d : %f %f %f %d	%x\n", i, ((t_sp*)(p.objs[i].o))->o.x, ((t_sp*)(p.objs[i].o))->o.y, ((t_sp*)(p.objs[i].o))->o.z, ((t_sp*)(p.objs[i].o))->color);
	return (0);
}*/