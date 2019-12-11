/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_minirt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 12:51:50 by mbrunel           #+#    #+#             */
/*   Updated: 2019/12/11 03:31:01 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_MINIRT_H
# define H_MINIRT_H


#define RES_X 800 
#define RES_Y 800
#define VP_D 1.0
#define VP_H 1.0
#define VP_W 1.0
#define NB_OBJ 5
#define SPHERE 0
#define PLANE 1
#define BACKGROUND_COLOR 0
#define NB_FORM 2

# include <mlx.h>
# include "../libs/libft/libft.h"
# include "../incs/get_next_line.h"
# include <math.h>

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	void			*img;
}					t_mlx;

typedef struct		s_vec
{
	float			x;
	float			y;
	float			z;
}					t_vec;

typedef struct		s_info
{
	int				n;
	int				e;
	int				l;
}					t_info;

typedef struct		s_cam
{
	t_vec			right;
	t_vec			up;
	t_vec			dir;
	t_vec			o;
	t_vec			upleft;
}					t_cam;

typedef struct		s_ray
{
	t_vec			o;
	t_vec			dir;
}					t_ray;

typedef struct		s_sp
{
	t_vec			o;
	double			r;
	int				color;
}					t_sp;

typedef struct		s_pl
{
	double			a;
	double			b;
	double			c;
	double			d;
	t_vec			p;
	int				color;
}					t_pl;

typedef struct		s_objs
{
	void *o;
	int type;
}					t_objs;

typedef struct		s_p
{
	t_sp			sp;
	t_pl			pl;
	t_cam			cam;
	t_objs			objs[NB_OBJ + 1];
}					t_p;

typedef struct		s_inter
{
	int				color;
	double			inter;
}					t_inter;

void 	fill_img(int *img, t_info info, t_p p);
t_vec	add_vec(t_vec vec1, t_vec vec2);
t_vec	add_vec_d(t_vec vec1, double val);
t_vec	sub_vec(t_vec vec1, t_vec vec2);
t_vec	sub_vec_d(t_vec vec1, double val);
t_vec	div_vec(t_vec vec1, t_vec vec2);
t_vec	div_vec_d(t_vec vec1, double val);
t_vec	mult_vec(t_vec vec1, t_vec vec2);
t_vec	mult_vec_d(t_vec vec1, double val);
double	norm_vec(t_vec vec);
t_vec 	normalize(t_vec vec);
t_inter intersp(t_ray ray, void *ptr);
t_inter	interpl(t_ray ray, void *ptr);


static t_inter	(*get_inter[NB_FORM])(t_ray ray, void *ptr) = {
	intersp,
	interpl
};

#endif
