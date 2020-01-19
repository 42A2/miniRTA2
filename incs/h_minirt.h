/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_minirt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 12:51:50 by mbrunel           #+#    #+#             */
/*   Updated: 2020/01/19 19:32:24 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_MINIRT_H
# define H_MINIRT_H

// restrictions
#define RES_X_MAX 2300
#define RES_Y_MAX 1900
#define MAX_LENGTHG_FILE 300
#define VP_H 1.0
#define VP_W 1.0

// formes
#define SPHERE 0
#define PLANE 1
#define CYLINDRE 2

// tt augmenter de 1 lorsqu on rajoute un forme
#define NB_FORM 3
#define RESOLUTION 4
#define POINT 5
#define AMBIENT 6
#define CAMERA 7
#define BONUS 8
#define PARALLEL 9
#define LINES_OF_FILE 10

//necessaires pour le code
#define CODE_ERROR -8.1358795487531548454548874
#define MIN_D 0.00000000001
#define MIN_SHADOW 0.00001

# include "mlx.h"
# include "libft.h"
# include <math.h>

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	void			*img;
}					t_mlx;

typedef struct		s_vec
{
	double			x;
	double			y;
	double			z;
}					t_vec;

typedef struct		s_info
{
	int				n;
	int				e;
	int				l;
}					t_info;

typedef struct		s_parse
{

	double			d1;
	double			d2;
	double			d3;
	int				i1;
	int				i2;
	int				i3;
}					t_parse;

typedef struct		s_bonus
{
	double			delta_aliasing;
	int				coeff_aliasing;
	int				recurse_reflect;
}					t_bonus;

typedef struct		s_vp
{
	int				res_x;
	int				res_y;
}					t_vp;

typedef struct		s_cam
{
	double			dist;
	t_vec			o;
	t_vec			vec_dir;
	double			fov;
}					t_cam;

typedef struct		s_ray
{
	t_vec			o;
	t_vec			dir;
}					t_ray;

typedef struct		s_light
{
	int				type;
	double			intensity;
	t_vec			pos;
	int				color;
	t_vec			rgb;
}					t_light;

typedef struct		s_tr
{
	t_vec			ang1;
	t_vec			ang2;
	t_vec			ang3;
	t_vec			rgb;
	int				color;
}					t_tr;

typedef struct		s_cy
{
	t_vec			p;
	t_vec			dir;
	double			r;
	double			h;
	t_vec			rgb;
	int				color;
	double			spec;
	double			reflect;
}					t_cy;	

typedef struct		s_sp
{
	t_vec			o;
	double			r;
	int				color;
	double			spec;
	double			reflect;
}					t_sp;

typedef struct		s_pl
{
	double			d;
	t_vec			dir;
	t_vec			p;
	int				color;
	double			spec;
	double			reflect;
}					t_pl;

typedef struct		s_objs
{
	void *o;
	int type;
}					t_objs;

typedef struct		s_p
{
	t_vp			vp;
	t_cam			cam[MAX_LENGTHG_FILE];
	t_objs			objs[MAX_LENGTHG_FILE];
	t_light			lights[MAX_LENGTHG_FILE];
	t_bonus			bonus;
	int				bg_color;
	int				nb_lights;
	int				nb_objs;
	int				nb_cam;
}					t_p;

typedef struct		s_inter
{
	int				color;
	double			inter;
	double			spec;
	double			reflect;
	t_vec			normal;
	t_vec			ipoint;
}					t_inter;

int 	get_p(t_p *p, char *path);
double	recupdbl(char *line, int *i, char type, char format);
int		chr(const char *str, char c);
int		check_chr(int param, char c);
int		error(void *line, char *msg);
int		wk(double arg, double min, double max);
int		get_vp(char *line, t_vp *vp);
int		get_lights(char *line, t_light *light, int type, int *bg_color);
int		get_cam(char *line, t_cam *cam);
int		get_sphere(char *line, void **ptr);
int		get_plane(char *line, void **ptr);
int		get_bonus(char *line, t_bonus *bonus);
int 	get_cylindre(char *line, void **ptr);
int		get_triangle(char *line, void **ptr);

int		abs(int nb);
double	d_abs(double nb);
t_vec	add_vec(t_vec vec1, t_vec vec2);
t_vec	add_vec_d(t_vec vec1, double val);
t_vec	sub_vec(t_vec vec1, t_vec vec2);
t_vec	sub_vec_d(t_vec vec1, double val);
t_vec	div_vec(t_vec vec1, t_vec vec2);
t_vec	div_vec_d(t_vec vec1, double val);
t_vec	mult_vec(t_vec vec1, t_vec vec2);
t_vec	mult_vec_d(t_vec vec1, double val);
t_vec 	create_vec(double x, double y, double z);
double	norm_vec(t_vec vec);
double	prod_scal(t_vec vec1, t_vec vec2);
t_vec 	normalize(t_vec vec);
t_vec	cross_prod(t_vec vec1, t_vec vec2);

int		prod_color_float(int objcol, double i);
int		add_color_to_color(int col1, int col2);
int		prod_color_vec(int objcol, t_vec i);
int		get_color_integer(int r, int g, int b);
int		comp_cols(int col1, int col2, double delta);
int		mid_color(int *color, int nb);

void 	fill_img(int *img, t_info info, t_p p, int i_img);
t_inter intersp(t_ray ray, void *ptr, double start, double max);
t_inter	interpl(t_ray ray, void *ptr, double start, double max);
t_inter	intercy(t_ray ray, void *ptr, double start, double max);
t_inter	intertr(t_ray ray, void *ptr, double start, double max);

static int		(*get_obj[NB_FORM])(char *line, void **ptr) = {
	get_sphere,
	get_plane,
	get_cylindre,
};

static t_inter	(*get_inter[NB_FORM])(t_ray ray, void *ptr, double start, double max) = {
	intersp,
	interpl,
	intercy,
};

#endif
