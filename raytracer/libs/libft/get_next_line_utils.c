/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:25:29 by mbrunel           #+#    #+#             */
/*   Updated: 2019/11/07 07:05:06 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strjoi(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
	{
		free(s1);
		return (NULL);
	}
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	free(s1);
	return (new);
}

void	ft_memmov(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	unsigned char		*s;

	s = (unsigned char*)src;
	d = (unsigned char*)dest;
	i = 0;
	if (dest == src)
		return ;
	if (dest < src)
		while (n-- > 0)
		{
			d[i] = s[i];
			i++;
		}
	else
		while (n-- > 0)
			d[n] = s[n];
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*j;

	i = 0;
	j = (char*)s;
	while (n > 0)
	{
		j[i] = '\0';
		i++;
		n--;
	}
}
