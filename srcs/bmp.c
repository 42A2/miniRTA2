/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 23:37:51 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/03 05:56:40 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

void	fill_bmp(char **data, t_swap *s)
{
	int		i;
	int		j;
	int		x;
	int		y;
	char	*mlx_data;

	mlx_data = mlx_get_data_addr(s->mlx.img,
		&(s->bpp), &(s->size_line), &(s->endian));
	i = HEADER_SIZE;
	y = s->p.vp.res_y;
	while (y--)
	{
		x = -1;
		while (++x < s->p.vp.res_x)
		{
			j = (x * (s->info.n / 8)) + (y * s->info.l);
			*(*data + i++) = *(mlx_data + j++);
			*(*data + i++) = *(mlx_data + j++);
			*(*data + i++) = *(mlx_data + j);
		}
	}
}

void	header_bmp(char **data, t_swap *s)
{
	unsigned int size;

	size = s->p.vp.res_y * s->p.vp.res_x * 3;
	*(unsigned short *)*data = *(const unsigned int *)(unsigned long)"BM";
	*(unsigned int *)(*data + 2) = (size + HEADER_SIZE);
	*(unsigned int *)(*data + 6) = 0u;
	*(unsigned char *)(*data + 10) = HEADER_SIZE;
	*(unsigned int *)(*data + 14) = HEADER_SIZE - 14;
	*(unsigned int *)(*data + 18) = s->p.vp.res_x;
	*(unsigned int *)(*data + 22) = s->p.vp.res_y;
	*(unsigned short *)(*data + 26) = 1;
	*(unsigned short *)(*data + 28) = 24;
	*(unsigned int *)(*data + 30) = 0;
	*(unsigned int *)(*data + 34) = (unsigned int)size;
	*(unsigned int *)(*data + 38) = 3780;
	*(unsigned int *)(*data + 42) = 3780;
	*(int *)(*data + 46) = 0;
	*(int *)(*data + 50) = 0;
}

void	export_bmp(char *filename, t_swap *s)
{
	int				fd;
	unsigned int	size;
	unsigned int	i;
	char			*data;

	size = s->p.vp.res_y * s->p.vp.res_x * 3;
	if (!(data = malloc((size + HEADER_SIZE))))
		exit(error(NULL, "stack error\n"));
	i = 0;
	while (i < size + HEADER_SIZE)
		data[i++] = 0;
	header_bmp(&data, s);
	printf("%s\n", filename);
	fill_bmp(&data, s);
	if ((fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644)) <= 0)
		exit(error(NULL, "stack error\n"));
	write(fd, data, (size + HEADER_SIZE));
	close(fd);
}

char	*create_bmp_filename(char *file, int i)
{
	char		*filename;
	int			n;

	if (!(filename = malloc(sizeof(char) * (i + 5))))
		exit(error(NULL, "stack error\n"));
	n = -1;
	while (++n <= i)
		*(filename + n) = *(file + n);
	*(unsigned int *)(filename + n) =
	*(const unsigned int *)(unsigned long)"bmp\0";
	return (filename);
}
