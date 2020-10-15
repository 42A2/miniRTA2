/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 03:28:23 by mbrunel           #+#    #+#             */
/*   Updated: 2020/10/15 20:53:19 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	recup2(int *negative, int *j, int *i, char *line)
{
	*negative = 1;
	*j = 0;
	while (ft_isspace(line[*i]))
		(*i)++;
	if (line[*i] == '-' && (*i)++)
		*negative = -1;
}

double		recupdbl(char *line, int *i, char type, char format)
{
	double	nbr;
	double	part2;
	int		j;
	int		negative;

	recup2(&negative, &j, i, line);
	nbr = ft_atoi(line + *i);
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
	while (ft_isspace(line[*i]))
		(*i)++;
	if (ft_isspace(line[*i - 1]) && format == ' ')
		return (nbr * negative);
	return (line[(*i)++] == format || line[(*i - 1)\
	] == '#' ? nbr * negative : CODE_ERROR);
}

int			f_chr(const char *str, char c)
{
	int i;

	i = -1;
	if (c == '\0')
		return (0);
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

int			wk(double arg, double min, double max)
{
	if (arg == CODE_ERROR)
		return (-1);
	if (min == max)
		return (0);
	if (min <= arg && arg <= max)
		return (0);
	return (-1);
}

int			error(void *line, char *msg)
{
	if (line)
		free(line);
	write(2, msg, ft_strlen(msg));
	return (-1);
}
