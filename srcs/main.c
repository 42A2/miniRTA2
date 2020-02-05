/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrunel <mbrunel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 01:16:49 by yvanat            #+#    #+#             */
/*   Updated: 2020/02/05 10:51:05 by mbrunel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/h_minirt.h"

t_vec	rot(t_vec dir, t_vec cam, t_vec ang)
{
	t_vec	tmp;
	if (cam.z < 0)
		ang.y += M_PI;
	if (cam.x > 0)
		ang.y = M_PI * 2 - ang.y;
	if (cam.y < 0)
		ang.x = M_PI * 2 - ang.x;
	tmp.x = dir.x;
	tmp.y = sin(ang.x) * dir.z + cos(ang.x) * dir.y;
	tmp.z = cos(ang.x) * dir.z - sin(ang.x) * dir.y;
	dir = tmp;
	tmp.x = cos(ang.y) * dir.x - sin(ang.y) * dir.z;
	tmp.y = dir.y;
	tmp.z = sin(ang.y) * dir.x + cos(ang.y) * dir.z;
	return ((tmp));
}

int	chng_ocam(int i, void *swap)
{
	t_vec chng;
	t_vec ang;
	t_swap *s;

	s = (t_swap*)swap;
	if (i == 123)
		chng = create_vec(-STEP * s->p.cam[s->i].time, 0, 0);
	else if (i == 124)
		chng = create_vec(STEP * s->p.cam[s->i].time,0,0);
	else if (i == 125)
		chng = create_vec(0,0,-STEP * s->p.cam[s->i].time);
	else if (i == 126)
		chng = create_vec(0,0,STEP * s->p.cam[s->i].time);
	else if (i == 116)
		chng = create_vec(0,STEP * s->p.cam[s->i].time,0);
	else if (i == 121)
		chng = create_vec(0,-STEP * s->p.cam[s->i].time,0);
	else
		return (0);
	ang.x = acos(s->p.cam[s->i].vec_dir.z / sqrt(s->p.cam[s->i].vec_dir.y * s->p.cam[s->i].vec_dir.y + s->p.cam[s->i].vec_dir.z * s->p.cam[s->i].vec_dir.z));
	ang.y = acos(s->p.cam[s->i].vec_dir.z / sqrt(s->p.cam[s->i].vec_dir.x * s->p.cam[s->i].vec_dir.x + s->p.cam[s->i].vec_dir.z * s->p.cam[s->i].vec_dir.z));
	s->p.cam[s->i].o = add_vec(s->p.cam[s->i].o, rot(chng, s->p.cam[s->i].vec_dir, ang));
	s->p.cam[s->i].time = 0;
	mlx_destroy_image(s->mlx.ptr, s->mlx.img);
	return (img_to_win(s));
}

int stretch(int i, int x, int y, void *swap)
{
	t_swap s;
	t_vec ang;
	t_ray ray;
	int type;


	s = *(t_swap*)swap;
	if (s.c1.inter)
		type = s.p.objs[s.c1.i_obj].type;
	else if (i == 1)
		return (0);
	else
		type = -1;
	ang.x = acos(s.p.cam[s.i].vec_dir.z / sqrt(s.p.cam[s.i].vec_dir.y * s.p.cam[s.i].vec_dir.y + s.p.cam[s.i].vec_dir.z * s.p.cam[s.i].vec_dir.z));
	ang.y = acos(s.p.cam[s.i].vec_dir.z / sqrt(s.p.cam[s.i].vec_dir.x * s.p.cam[s.i].vec_dir.x + s.p.cam[s.i].vec_dir.z * s.p.cam[s.i].vec_dir.z));
	ray.o = s.p.cam[s.i].o;
	ray.dir = cam_rot(c_to_vp((double)y, (double)x, s.p.vp, s.p.cam[s.i].dist), s.p.cam[s.i].vec_dir, ang);
	if (s.c1.inter == 0 || (type == PLANE && i == 2))
		s.p.cam->vec_dir = ray.dir;
	else if (i == 1 || type == TRIANGLE)
	{
		if (type == TRIANGLE)
			((t_tr*)(s.p.objs[s.c1.i_obj].o))->click = s.c1.ipoint;
		g_chng_origin[type](s.p.objs[s.c1.i_obj].o, ray);
	}
	else if (i == 2)
		g_chng_stretch[type](s.p.objs[s.c1.i_obj].o, ray);
	else
		return (0);
	mlx_destroy_image(s.mlx.ptr, s.mlx.img);
	return (img_to_win(&s));
}

int get_pos(int i, int x, int y, void *swap)
{
	t_swap s;
	t_vec ang;
	t_ray ray;

	(void)i;
	s = *(t_swap*)swap;
	ang.x = acos(s.p.cam[s.i].vec_dir.z / sqrt(s.p.cam[s.i].vec_dir.y * s.p.cam[s.i].vec_dir.y + s.p.cam[s.i].vec_dir.z * s.p.cam[s.i].vec_dir.z));
	ang.y = acos(s.p.cam[s.i].vec_dir.z / sqrt(s.p.cam[s.i].vec_dir.x * s.p.cam[s.i].vec_dir.x + s.p.cam[s.i].vec_dir.z * s.p.cam[s.i].vec_dir.z));
	ray.o = s.p.cam[s.i].o;
	ray.dir = cam_rot(c_to_vp((double)y, (double)x, s.p.vp, s.p.cam[s.i].dist), s.p.cam[s.i].vec_dir, ang);
	((t_swap*)swap)->c1 = min_inter(ray, s.p, MIN_D, __DBL_MAX__);
	return (0);
}

static int quit(int rt, void *swap)
{
	t_swap *s;
	int		i;

	i = -1;
	s = (t_swap*)swap;
	while (++i < s->p.nb_objs)
		free(s->p.objs[i].o);
	if (s->mlx.img)
		mlx_destroy_image(s->mlx.ptr, s->mlx.img);
	exit(rt != -1 ? 0 : -1);
}

int stereo(t_swap *s)
{
	t_vec chng;
	t_vec ang;
	int *img1;
	int *img2;
	int i;
	int j;
	int prev_len;
	int len;

	i = -1;
	prev_len = s->info.l / 4;
	if (!(img1 = malloc(sizeof(int) * s->p.vp.res_y * (s->info.l / 4))))
		quit(error(NULL, "memory error\n"), s);
	if (!(img2 = malloc(sizeof(int) * s->p.vp.res_y * (s->info.l / 4))))
		quit(error(img1, "memory error\n"), s);
	ft_memcpy(img1, s->img, sizeof(int) * s->p.vp.res_y * (s->info.l / 4));
	chng = create_vec(DEC,0,0);
	ang.x = acos(s->p.cam[s->i].vec_dir.z / sqrt(s->p.cam[s->i].vec_dir.y * s->p.cam[s->i].vec_dir.y + s->p.cam[s->i].vec_dir.z * s->p.cam[s->i].vec_dir.z));
	ang.y = acos(s->p.cam[s->i].vec_dir.z / sqrt(s->p.cam[s->i].vec_dir.x * s->p.cam[s->i].vec_dir.x + s->p.cam[s->i].vec_dir.z * s->p.cam[s->i].vec_dir.z));
	s->p.cam[s->i].o = add_vec(s->p.cam[s->i].o, rot(chng, s->p.cam[s->i].vec_dir, ang));
	fill_img(s->img, s->info, s->p, s->i);
	ft_memcpy(img2, s->img, sizeof(int) * s->p.vp.res_y * (s->info.l / 4));
	if (!(s->mlx.img = mlx_new_image(s->mlx.ptr, s->p.vp.res_x * 2, s->p.vp.res_y)))
		return (-1);
	if (!(s->img = (int*)mlx_get_data_addr(s->mlx.img, &(s->info.n), &(s->info.l) , &(s->info.e))))
		return (-1);
	len = s->info.l / 4;
	while (++i < s->p.vp.res_y)
	{
		j = -1;
		while (++j < s->p.vp.res_x)
		{
			s->img[i * len + j] = img1[i * (prev_len) +j];
			s->img[i * len + j + s->p.vp.res_x] = img2[i * (prev_len) + j];
		}
	}
	s->p.vp.res_x *= 2;
	free(img2);
	free(img1);
	export_bmp(create_bmp_filename("3D.rt", 2), s);
	return (quit(0, s));
}

int	swap_cam(int i, void *swap)
{
	t_swap *s;
	s = (t_swap*)swap;
	if (i >= 18 && i <= 21)
		s->i = i - 18;
	else if (i == 23)
		s->i = 4;
	else if (i == 22)
		s->i = 5;
	else if (i == 26)
		s->i = 6;
	else if (i == 28)
		s->i = 7;
	else if (i == 25)
		s->i = 8;
	else if (i >= 83 && i <= 92)
		s->i = i - 83;
	else if (i == 53)
		quit(0, swap);
	else if (i == 48)
		s->i = (s->i + 1) % s->p.nb_cam;
	else if (i == 1)
	{
		s->p.vp = s->p.bonus.save_res;
		s->p.bonus.coeff_aliasing = s->p.bonus.save_coef_as;
		s->p.bonus.delta_aliasing = s->p.bonus.save_delta_as;
		s->s_s = 1;
		mlx_destroy_image(s->mlx.ptr, s->mlx.img);
		img_to_win(s);
	}
	else if(i == 2)
		return (stereo(s));
	else
	{
		if ((i >= 123 && i <= 126) || i == 116 || i == 121)
			((t_swap*)(swap))->p.cam[s->i].time += 1;
		else if (s->p.nb_cam <= s->i)
			ft_fprintf(1, "no such camera\n");
		return (0);
	}
	mlx_destroy_image(s->mlx.ptr, s->mlx.img);
	return (img_to_win(s));
}

int img_to_win(t_swap *s)
{
	if (!(s->mlx.img = mlx_new_image(s->mlx.ptr, s->p.vp.res_x, s->p.vp.res_y)))
			return (-1);
	if (!(s->img = (int*)mlx_get_data_addr(s->mlx.img, &(s->info.n), &(s->info.l) , &(s->info.e))))
		return (-1);
	fill_img(s->img, s->info, s->p, s->i);
	if (s->s_s)
	{
		export_bmp(create_bmp_filename(s->name, s->save), s);
		quit(0, s);
	}
	if (mlx_put_image_to_window(s->mlx.ptr, s->mlx.win, s->mlx.img, 0, 0) == -1)
		return (-1);
	mlx_hook(s->mlx.win, 2, 1L<<0, &swap_cam, s);
	mlx_hook(s->mlx.win, 3, 1L<<1, &chng_ocam, s);
	mlx_hook(s->mlx.win, 4, 1L<<2, &get_pos, s);
	mlx_hook(s->mlx.win, 5, 1L<<3, &stretch, s);
	mlx_hook(s->mlx.win, 17, 1L<<17, &quit, s);
	mlx_loop(s->mlx.ptr);
	return (0);
}

int check_n(char *buf)
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
	t_swap s;

	s.i = 0;
	mlx.ptr = mlx_init();
	s.s_s = 0;
	if (argc == 3 && !ft_strncmp(argv[2], "-save", 5))
		s.s_s = 1;
	s.name = argv[1];
	if ((argc > 2 && !s.save) || argc < 2)
		exit (error(NULL, "manque ou surplus d'args ou \"-save\" mal ecrit\n"));
	if ((s.save = check_n(argv[1])) == -1)
		exit (error(NULL, "file bad named\n"));
	if (get_p(&(s.p), argv[1]) == -1)
		quit(-1, &s);
	if (!s.s_s && !(mlx.win = mlx_new_window(mlx.ptr, s.p.vp.res_x, s.p.vp.res_y, "RT")))
		quit(error(NULL, "mlx error\n"), &s);
	s.mlx = mlx;
	if (img_to_win(&s) == -1)
		quit(error(NULL, "mlx error\n"), &s);
	return (0);
}
