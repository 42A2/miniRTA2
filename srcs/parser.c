/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 05:14:16 by mbrunel           #+#    #+#             */
/*   Updated: 2020/03/02 01:08:07 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

static int	p2(int *type, int *incs, char *buf, t_p *p)
{
	if (*type == SPHERE && buf[1] == 'q')
		*type = SQUARE;
	if (*type == RESOLUTION && (\
	incs[RESOLUTION] || get_vp(buf, &(p->vp)) == -1))
		return (error(buf, "the vp is badly registered\n"));
	else if (*type <= AMBIENT && *type >= POINT && ((incs[AMBIENT] == 1 && *\
	type == AMBIENT) || (get_lights(buf, &(\
	p->lights[incs[AMBIENT] + incs[POINT]]), *type) == -1)))
		return (error(buf, "light parameters are badly registered\n"));
	else if (*type == CAMERA && ft_isspace(buf[1]) && (get_cam(buf\
	, &(p->cam[incs[CAMERA]])) == -1))
		return (error(buf, "camera parameters are badly registered\n"));
	else if (*type == CAMERA && buf[1] == 'y')
		*type = CYLINDRE;
	else if (*type == BONUS && (incs[BONUS\
	] || get_bonus(buf, &(p->bonus)) == -1))
		return (error(buf, "bonus parameters are badly registered\n"));
	if (*type < NB_FORM && (g_get_obj[*type])(buf\
	, &(p->objs[incs[NB_FORM]].o)) == -1)
		return (error(buf, "objs parameters are badly registered\n"));
	return (0);
}

static int	p3(t_p *p, int *incs)
{
	p->nb_cam = incs[CAMERA];
	p->nb_lights = incs[POINT] + incs[AMBIENT];
	p->nb_objs = incs[NB_FORM];
	if (!incs[RESOLUTION])
		return (error(NULL, "no resolution\n"));
	if (!incs[CAMERA])
		return (error(NULL, "no camera\n"));
	if (!incs[AMBIENT])
		return (error(NULL, "no ambiant\n"));
	return (0);
}

static void	p4(t_parse2 n, int *incs, char *buf, t_p *p)
{
	if (n.type < NB_FORM)
		p->objs[incs[NB_FORM]].type = n.type;
	incs[n.type]++;
	if (n.type < NB_FORM)
		incs[NB_FORM]++;
	free(buf);
}

int			get_p(t_p *p, char *path)
{
	t_parse2	n;
	int			incs[20];
	char		*buf;
	char		*shrs;

	shrs = "spyt0#RlAcb";
	if ((n.fd = open(path, O_RDWR)) == -1)
		return (error(NULL, "open_eror\n"));
	ft_memset(incs, 0, sizeof(int) * 20);
	while ((n.status = get_next_line(n.fd, &buf)) > 0 &&
		++incs[LINES_OF_FILE] < MAX_LENGTHG_FILE)
	{
		if ((n.type = (f_chr(shrs, buf[0]))) == -1)
			return (error(buf, "object not found in database\n"));
		else if (shrs[n.type] == '#' || buf[0] == '\0')
		{
			free(buf);
			buf = NULL;
			continue ;
		}
		else if (p2(&(n.type), incs, buf, p) == -1)
			return (-1);
		p4(n, incs, buf, p);
	}
	if (buf)
		free(buf);
	return (p3(p, incs));
}
