/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numconvs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:46:55 by mbrunel           #+#    #+#             */
/*   Updated: 2019/10/31 17:22:51 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

char		*uconv(va_list ap)
{
	char				str[100];
	char				*rt;
	int					nb;
	size_t				new;

	nb = va_arg(ap, unsigned int);
	new = nb >= 0 ? nb : (UINT32_MAX + nb + 1);
	deathcurse(new, 0, str);
	return ((rt = revdup(str)) ? rt : NULL);
}

char		*diconv(va_list ap)
{
	return ((ft_itoa(va_arg(ap, int))));
}
