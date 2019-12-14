/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 09:13:12 by mbrunel           #+#    #+#             */
/*   Updated: 2019/10/28 16:10:48 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				ft_printf(const char *str, ...)
{
	va_list		ap;
	t_incs		sizes[1];

	va_start(ap, str);
	sizes->i = 0;
	sizes->tot = 0;
	while (str[sizes->i])
	{
		if (str[sizes->i] != '%')
		{
			write(1, str + sizes->i, 1);
			sizes->tot++;
		}
		else
		{
			if ((matrix(str, ap, sizes)) == -1)
				return (-1);
		}
		sizes->i++;
	}
	va_end(ap);
	return (sizes->tot);
}
