/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 03:28:23 by mbrunel           #+#    #+#             */
/*   Updated: 2019/12/13 01:52:41 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

double	recupdbl(char *line, int *i, char type, char format)
{
	double	nbr;
	double	part2;
	int		j;

	j = 0;
	while (ft_isspace(line[*i]))
		(*i)++;
	nbr = ft_atoi(line + *i);
	if (line[*i] == '-')
		(*i)++;
	while (ft_isdigit(line[*i]))
		(*i)++;
	if (line[*i] == '.' && type == 'f')
	{
		part2 = ft_atoi(line + ++(*i));
		while (ft_isdigit(line[*i + j]))
			j++;
		*i += j;
		nbr += part2 / (pow(10, j));
	}
	if (!format)
		while (ft_isspace(line[*i]))
			(*i)++;
	return (((format == ' ' && ft_isspace(line[*i])) ||
	(line[(*i)++] == format)) ? nbr : -2);
}

int		chr(const char *str, char c)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

int		wk(double arg, double min, double max)
{
	if (min == max)
		return (0);
	if (min <= arg && arg <= max)
		return (0);
	return (-1);
}

int error(void *line, char *msg)
{
	if (line)
		free(line);
	write(2, msg, ft_strlen(msg));
	return (-1);
}
