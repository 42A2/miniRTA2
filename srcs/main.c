/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 01:16:49 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/13 15:21:40 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

int		img_to_win(t_swap *s)
{
	if (s->img)
		mlx_destroy_image(s->mlx.ptr, s->mlx.img);
	if (!(s->mlx.img = mlx_new_image(s->mlx.ptr, s->p.vp.res_x, s->p.vp.res_y)))
		return (-1);
	if (!(s->img = (int*)mlx_get_data_addr(s->mlx.img\
	, &(s->info.n), &(s->info.l), &(s->info.e))))
		return (-1);
	fill_img(s->img, s->info, s->p, s->i);
	if (s->s_s)
	{
		export_bmp(create_bmp_filename(s->name, s->save), s);
		quit(0, s);
	}
	if (mlx_put_image_to_window(s->mlx.ptr, s->mlx.win, s->mlx.img, 0, 0) == -1)
		return (-1);
	return (0);
}

int		check_n(char *buf)
{
	int i;

	i = -1;
	while (buf[++i] && buf[i] != '.')
		;
	if (buf[i + 1] == 'r' && buf[i + 2] == 't' && !buf[i + 3])
		return (i);
	return (-1);
}

int		main(int argc, char *argv[])
{
	t_mlx	mlx;
	t_swap	s;
	int		i;

	s.i = 0;
	mlx.ptr = mlx_init();
	s.s_s = 0;
	if (argc == 3 && !ft_strncmp(argv[2], "-save", 5))
		s.s_s = 1;
	s.name = argv[1];
	if ((argc > 2 && !s.save) || argc < 2)
		exit(error(NULL, "manque ou surplus d'args ou \"-save\" mal ecrit\n"));
	if ((s.save = check_n(argv[1])) == -1)
		exit(error(NULL, "file bad named\n"));
	if (get_p(&(s.p), argv[1]) == -1)
		quit(-1, &s);
	if (!s.s_s && !(mlx.win = mlx_new_window(mlx.ptr\
	, s.p.vp.res_x, s.p.vp.res_y, "RT")))
		quit(error(NULL, "mlx error\n"), &s);
	s.mlx = mlx;
	s.img = NULL;
	if (img_to_win(&s) == -1)
		quit(error(NULL, "mlx error\n"), &s);
	mlx_hook(s.mlx.win, 2, 1L << 0, &swap_cam, &s);
	mlx_hook(s.mlx.win, 3, 1L << 1, &chng_ocam, &s);
	mlx_hook(s.mlx.win, 4, 1L << 2, &get_pos, &s);
	mlx_hook(s.mlx.win, 5, 1L << 3, &stretch, &s);
	mlx_hook(s.mlx.win, 17, 1L << 17, &quit, &s);
	mlx_loop_hook(s.mlx.ptr, &img_to_win, &s);
	nmlx_smart_hook_on(s.mlx.ptr);
	mlx_loop(s.mlx.ptr);
	i = -1;
	while (++i < s.p.nb_objs)
		free(s.p.objs[i].o);
	mlx_destroy_image(s.mlx.ptr, s.mlx.img);
	mlx_destroy_window(s.mlx.ptr, s.mlx.win);
	nmlx_quit(s.mlx.ptr);
	return (0);
}
