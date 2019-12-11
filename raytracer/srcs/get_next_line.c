/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:50:13 by mbrunel           #+#    #+#             */
/*   Updated: 2019/11/07 07:04:57 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char				*setbuff(void)
{
	char *new;

	if (!(new = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (NULL);
	*new = '\0';
	return (new);
}

int					clean(char **buf, int rt)
{
	if (*buf)
		free(*buf);
	*buf = NULL;
	return (rt);
}

int					check(const char *buf)
{
	int i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int					get_next_line(int fd, char **line)
{
	static char		*buf;
	int				st;

	if (!line)
		return (-1);
	*line = malloc(sizeof(char));
	**line = '\0';
	if (!(buf))
		if (!(buf = setbuff()))
			return (-1);
	while ((st = check(buf)) == -1)
	{
		if (!(*line = ft_strjoi(*line, buf)))
			return (clean(&buf, -1));
		if ((st = read(fd, buf, BUFFER_SIZE)) < 1)
			return (clean(&buf, st));
		buf[st] = '\0';
	}
	buf[st] = '\0';
	if (!(*line = ft_strjoi(*line, buf)))
		return (clean(&buf, -1));
	st = ft_strlen(buf);
	ft_memmov(buf, buf + st + 1, ft_strlen(buf + st + 1) + 1);
	return (1);
}
