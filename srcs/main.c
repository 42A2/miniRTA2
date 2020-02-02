/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 01:16:49 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/03 00:46:01 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

int quit(void *swap)
{
	t_swap *s;

	s = (t_swap*)swap;
	printf("kjlkj %d\n", s->save);
	if (s->save)
		export_bmp(create_bmp_filename("yvanat", 6), s);
	exit(0);
}

int	swap_cam(int i, void *swap)
{
	t_swap s;
	s = *(t_swap*)swap;
	if (i >= 18 && i <= 21)
		s.i = i - 18;
	else if (i == 23)
		s.i = 4;
	else if (i == 22)
		s.i = 5;
	else if (i == 26)
		s.i = 6;
	else if (i == 28)
		s.i = 7;
	else if (i == 25)
		s.i = 8;
	else if (i >= 83 && i <= 92)
		s.i = i - 83;
	else if (i == 53)
		quit(swap);
	else if (i == 48)
		s.i = (s.i + 1) % s.p.nb_cam;
	else
		return (0);
	if (s.p.nb_cam <= s.i)
	{
		ft_fprintf(1, "no such camera\n");
		return (0);
	}
	mlx_destroy_image(s.mlx.ptr, s.img);
	return (img_to_win(s));
}

int img_to_win(t_swap s)
{
	if (!(s.mlx.img = mlx_new_image(s.mlx.ptr, s.p.vp.res_x, s.p.vp.res_y)))
			return (-1);
	if (!(s.img = (int*)mlx_get_data_addr(s.mlx.img, &(s.info.n), &(s.info.l) , &(s.info.e))))
		return (-1);
	fill_img(s.img, s.info, s.p, s.i);
	mlx_put_image_to_window(s.mlx.ptr, s.mlx.win, s.mlx.img, 0, 0);
	mlx_key_hook(s.mlx.win, &swap_cam, &s);
	mlx_hook(s.mlx.win, 17, 1, &quit, &s);
	mlx_loop(s.mlx.ptr);
	return (0);
}

int		main(int argc, char *argv[])
{
	t_mlx	mlx;
	t_swap swap;

	swap.i = 0;
	mlx.ptr = mlx_init();
	swap.save = 0;
	if (argc == 3 && !ft_strncmp(argv[2], "-save", 5))
		swap.save = 1;
	if (!argv[1] || (argc > 2 && !swap.save))
		exit (error(NULL, "manque ou surplus d'args ou \"-save\" mal ecrit\n"));
	if (get_p(&(swap.p), argv[1]) == -1)
		return (-1);
	if ((mlx.win = mlx_new_window(mlx.ptr, swap.p.vp.res_x, swap.p.vp.res_y, "RT")))
	{
		swap.mlx = mlx;
		if (img_to_win(swap) == -1)
			return (-1);
	}
	return (0);
}