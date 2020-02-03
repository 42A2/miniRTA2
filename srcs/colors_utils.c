/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 02:01:43 by mbrunel           #+#    #+#             */
/*   Updated: 2020/02/03 04:21:29 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

int		prod_color_float(int objcol, double i)
{
	int rt;

	rt = 0;
	rt |= (int)(((objcol & 0xFF0000) >> 16) * i) << 16;
	rt |= (int)(((objcol & 0x00FF00) >> 8) * i) << 8;
	rt |= (int)((objcol & 0x0000FF) * i);
	return (rt);
}

int		add_color_to_color(int col1, int col2)
{
	int rt;

	rt = 0;
	rt |= ((((col1 & 0xFF0000) >> 16) + ((col2 & 0xFF0000) >> 16))) << 16;
	rt |= ((((col1 & 0x00FF00) >> 8) + ((col2 & 0x00FF00) >> 8))) << 8;
	rt |= ((col1 & 0x0000FF) + (col2 & 0x0000FF));
	return (rt);
}

int prod_color_vec(int objcol, t_vec i)
{
	int rt;

	rt = 0;
	rt |= (int)(((objcol & 0xFF0000) >> 16) * (i.x > 1 ? 1 : i.x)) << 16;
	rt |= (int)(((objcol & 0x00FF00) >> 8) * (i.y > 1 ? 1 : i.y)) << 8;
	rt |= (int)((objcol & 0x0000FF) * (i.z > 1 ? 1 : i.z));
	return (rt);
}

int get_color_integer(int r, int g, int b)
{
	int rt;

	rt = 0;
	rt |= r << 16;
	rt |= g << 8;
	rt |= b;
	return (rt);
}

int		comp_cols(int col1, int col2, double delta)
{
	t_vec rgb;

	rgb.x = abs(((col1 & 0xFF0000) >> 16) - ((col2 & 0xFF0000) >> 16));
	rgb.y = abs(((col1 & 0x00FF00) >> 8) - ((col2 & 0x00FF00) >> 8));
	rgb.z = abs(((col1 & 0x0000FF) - (col2 & 0x0000FF)));
	if (norm_vec(rgb) > delta)
		return (-1);
	return (0);
}

int mid_color(int *color, int nb)
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

int	red_filter(int color, double strength)
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

int	green_filter(int color, double strength)
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

int	blue_filter(int color, double strength)
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
