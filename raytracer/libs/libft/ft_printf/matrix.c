/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 03:59:42 by mbrunel           #+#    #+#             */
/*   Updated: 2019/12/09 15:44:14 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int						matrix(const char *str, va_list ap, t_incs *sizes)
{
	char		*(*f[9])(va_list ap);
	char		*set;
	char		*new;
	int			convt;
	t_param		*p;

	set = "cs%pdiuxX";
	setf(f);
	sizes->j = 0;
	while (str[++(sizes->j) + sizes->i])
		if ((convt = chr(set, str[sizes->i + sizes->j])) != -1)
			break ;
	if (!(str[sizes->i + sizes->j]))
		return (-1);
	if (!(p = srch_flags(str + sizes->i, sizes->j - 1, ap)))
		return (-1);
	if (!(new = (*f[convt])(ap)))
		return (-1);
	sizes->i += sizes->j;
	if (convt != 2 && convt != 0)
		sizes->tot += convt <= 3 ? print_str(new, p, 0) :\
		print_dig(new, p, 0);
	else
		sizes->tot += printpercent(new, p, 0);
	return (sizes->tot);
}
