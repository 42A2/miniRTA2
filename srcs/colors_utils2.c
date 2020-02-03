/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 05:49:22 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/03 05:50:00 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

int		mid_color(int *color, int nb)
{
	int r;
	int g;
	int b;
	int i;

	r = 0;
	g = 0;
	b = 0;
	i = -1;
	while (++i < nb)
	{
		r += (color[i] & 0xFF0000) >> 16;
		g += (color[i] & 0x00FF00) >> 8;
		b += color[i] & 0x0000FF;
	}
	free(color);
	return (get_color_integer(r / nb, g / nb, b / nb));
}

int		red_filter(int color, double strength)
{
	int	r;
	int	g;
	int	b;

	r = (int)((double)((color & 0xFF0000) >> 16) * strength);
	if (r > 255)
		r = 255;
	g = (int)((double)((color & 0x00FF00) >> 8) / strength);
	b = (int)((double)(color & 0x0000FF) / strength);
	return (get_color_integer(r, g, b));
}

int		green_filter(int color, double strength)
{
	int	r;
	int	g;
	int	b;

	r = (int)((double)((color & 0xFF0000) >> 16) / strength);
	g = (int)((double)((color & 0x00FF00) >> 8) * strength);
	if (g > 255)
		g = 255;
	b = (int)((double)(color & 0x0000FF) / strength);
	return (get_color_integer(r, g, b));
}

int		blue_filter(int color, double strength)
{
	int	r;
	int	g;
	int	b;

	r = (int)((double)((color & 0xFF0000) >> 16) / strength);
	g = (int)((double)((color & 0x00FF00) >> 8) / strength);
	b = (int)((double)(color & 0x0000FF) * strength);
	if (b > 255)
		b = 255;
	return (get_color_integer(r, g, b));
}

void	filter(int type, double strength, int *img, int i)
{
	int	color;

	color = img[i];
	if (type == 1)
	{
		img[i] = red_filter(color, strength);
	}
	else if (type == 2)
	{
		img[i] = green_filter(color, strength);
	}
	else if (type == 3)
	{
		img[i] = blue_filter(color, strength);
	}
}
