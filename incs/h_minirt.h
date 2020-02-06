/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_minirt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yvanat <yvanat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 12:51:50 by mbrunel           #+#    #+#             */
/*   Updated: 2020/02/06 07:49:59 by yvanat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_MINIRT_H
# define H_MINIRT_H

/*
**restrictions
*/
# define RES_X_MAX 2560
# define RES_Y_MAX 1440
# define MAX_LENGTHG_FILE 300
# define VP_H 1.0
# define VP_W 1.0
# define STEP 5
# define BG_COLOR 0
# define DEC 0.8

/*
**formes
*/
# define SPHERE 0
# define PLANE 1
# define CYLINDRE 2
# define TRIANGLE 3
# define SQUARE 4

/*
**tt augmenter de 1 lorsqu on rajoute un forme
*/
# define NB_FORM 5
# define RESOLUTION 6
# define POINT 7
# define AMBIENT 8
# define CAMERA 9
# define BONUS 10
# define PARALLEL 11
# define LINES_OF_FILE 12

/*
**necessaires pour le code
*/
# define CODE_ERROR -18.8358795487531548454548874
# define MIN_D 1e-100
# define MAX_D 1e100
# define I_MAX __INT32_MAX__
# define MIN_SHADOW 1e-5
# define HEADER_SIZE 122

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <pthread.h>

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

typedef struct		s_mouse
{
	int				x;
	int				y;
	int				button;
}					t_mouse;

typedef struct		s_parse
{
	double			d1;
	double			d2;
	double			d3;
	int				i1;
	int				i2;
	int				i3;
}					t_parse;

typedef struct		s_pars2
{
	int				fd;
	int				status;
	int				type;
}					t_parse2;

typedef struct		s_vp
{
	int				res_x;
	int				res_y;
}					t_vp;

typedef struct		s_bonus
{
	double			delta_aliasing;
	int				coeff_aliasing;
	int				recurse_reflect;
	int				filter_type;
	double			filter_strength;
	t_vp			save_res;
	double			save_delta_as;
	double			save_coef_as;
}					t_bonus;

typedef struct		s_cam
{
	double			dist;
	t_vec			o;
	t_vec			vec_dir;
	double			fov;
	double			time;
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

typedef struct		s_sq
{
	double			d;
	t_vec			dir;
	t_vec			p;
	double			h;
	int				color;
	double			spec;
	double			reflect;
}					t_sq;

typedef struct		s_tr
{
	t_vec			ang1;
	t_vec			ang2;
	t_vec			ang3;
	t_vec			rgb;
	int				color;
	double			spec;
	double			reflect;
	t_vec			click;
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
	void			*o;
	int				type;
}					t_objs;

typedef struct		s_p
{
	t_vp			vp;
	t_cam			cam[MAX_LENGTHG_FILE];
	t_objs			objs[MAX_LENGTHG_FILE];
	t_light			lights[MAX_LENGTHG_FILE];
	t_bonus			bonus;
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
	int				i_obj;
}					t_inter;

typedef struct		s_coor
{
	int				i;
	int				j;
	int				actualpix;
}					t_coor;

typedef struct		s_swap
{
	t_mlx			mlx;
	int				*img;
	t_p				p;
	int				i;
	t_info			info;
	t_inter			c1;
	int				save;
	char			*name;
	int				bpp;
	int				endian;
	int				size_line;
	int				s_s;
}					t_swap;

typedef struct		s_data
{
	t_p				p;
	t_vec			ang;
	int				len;
	int				i;
	int				i_img;
	int				*img;
	int				*count;
	pthread_mutex_t	*mut;
	pthread_cond_t	*cond;
}					t_data;

typedef struct		s_sqvar
{
	t_inter			rt;
	t_vec			l;
	t_vec			random_normal;
	t_vec			normal_random_normal;
	t_vec			p1;
	t_vec			p2;
	t_vec			p3;
	t_vec			p4;
	t_vec			vec1;
	t_vec			vec2;
	t_vec			vec22;
	t_vec			edge2;
	t_vec			edge3;
	t_vec			edge22;
	t_vec			edge33;
	t_vec			vp;
	t_vec			c;
	double			d;
	double			m;
	double			boo;
	double			sqr;
}					t_sqvar;

typedef struct		s_spvar
{
	double			t1;
	double			t2;
	double			a;
	double			b;
	double			c;
	double			dis;
	t_inter			rt;
	t_vec			oc;
}					t_spvar;

typedef struct		s_trvar
{
	t_vec			vec1;
	t_vec			vec2;
	t_vec			edge2;
	t_vec			edge3;
	double			d;
	double			m;
	t_vec			l;
	t_vec			vp;
	t_vec			c;
	int				boo;
}					t_trvar;

typedef struct		s_thread
{
	int				i;
	int				len;
	int				ret;
	int				count;
	t_vec			ang;
	pthread_mutex_t	*mut;
	pthread_cond_t	*cond;
}					t_thread;

typedef struct		s_cyvar
{
	t_vec			L;
	t_cy			cy;
	t_vec			w;
	double			sqr_omega;
	t_vec			wn;
	double			R;
	t_vec			E;
	double			t;
	t_inter			rt;
	t_vec			F;
	t_vec			Fn;
	double			s;
	t_vec			cp;
	double			cq;
	t_vec			qp;
	int				boo;
}					t_cyvar;

typedef struct		s_as
{
	int		nb;
	int		k;
	int		m;
	int		n;
	int		i_img;
	int		*color;
	t_ray	ray;
}					t_as;

typedef struct		s_lightvar
{
	t_vec			i;
	double			coeff;
	double			p_scal;
	t_vec			l;
	t_inter			closest;
	t_ray			shadow;
	double			max;
}					t_lightvar;

typedef struct		s_var2
{
	double			start;
	double			max;
	t_ray			ray;
}					t_var2;


int					get_p(t_p *p, char *path);
double				recupdbl(char *line, int *i, char type, char format);
int					f_chr(const char *str, char c);
int					check_chr(int param, char c);
int					error(void *line, char *msg);
int					wk(double arg, double min, double max);
int					get_vp(char *line, t_vp *vp);
int					get_lights(char *line, t_light *light, int type);
int					get_cam(char *line, t_cam *cam);
int					get_sphere(char *line, void **ptr);
int					get_plane(char *line, void **ptr);
int					get_bonus(char *line, t_bonus *bonus);
int					get_cylindre(char *line, void **ptr);
int					get_triangle(char *line, void **ptr);
int					get_square(char *line, void **ptr);

int					abs(int nb);
double				d_abs(double nb);
t_vec				add_vec(t_vec vec1, t_vec vec2);
t_vec				add_vec_d(t_vec vec1, double val);
t_vec				sub_vec(t_vec vec1, t_vec vec2);
t_vec				sub_vec_d(t_vec vec1, double val);
t_vec				div_vec(t_vec vec1, t_vec vec2);
t_vec				div_vec_d(t_vec vec1, double val);
t_vec				mult_vec(t_vec vec1, t_vec vec2);
t_vec				mult_vec_d(t_vec vec1, double val);
t_vec				create_vec(double x, double y, double z);
double				norm_vec(t_vec vec);
double				prod_scal(t_vec vec1, t_vec vec2);
t_vec				normalize(t_vec vec);
t_vec				cross_prod(t_vec vec1, t_vec vec2);
t_vec				i_prod_scal(t_vec vec);
t_vec				inv_prod_scal(t_vec vec1);

int					prod_color_float(int objcol, double i);
int					add_color_to_color(int col1, int col2);
int					prod_color_vec(int objcol, t_vec i);
int					get_color_integer(int r, int g, int b);
int					comp_cols(int col1, int col2, double delta);
int					mid_color(int *color, int nb);
int					red_filter(int color, double strength);
int					green_filter(int color, double strength);
int					blue_filter(int color, double strength);
void				filter(int type, double strength, int *img, int i);

void				fill_img(int *img, t_info info, t_p p, int i_img);
int					img_to_win(t_swap *s);

t_var2				create_v2(double start, double max, t_ray ray);
t_vec				cam_rot(t_vec dir, t_vec cam, t_vec ang);
t_vec				rot(t_vec dir, t_vec cam, t_vec ang);
t_inter				intersp(t_ray ray, void *ptr, double start, double max);
t_inter				interpl(t_ray ray, void *ptr, double start, double max);
t_inter				intercy(t_ray ray, void *ptr, double start, double max);
t_inter				intertr(t_ray ray, void *ptr, double start, double max);
t_inter				intersq(t_ray ray, void *ptr, double start, double max);
t_vec				c_to_vp(double i, double j, t_vp vp, double dist);
t_inter				min_inter(t_ray ray, t_p *p, double start, double max);
int					find_pix_color(t_ray ray, t_p *p, int depth);
t_vec				retray(t_vec r, t_vec n);
void				aliasing(int *img, int len, t_p p, int i_img);
void				find_ang(t_vec *ang, t_p p, int i_img);
void				aliasing_bonus(t_data *dt);

void				chng_sp(void *ptr, t_ray new);
void				chng_pl(void *ptr, t_ray new);
void				chng_cy(void *ptr, t_ray new);
void				chng_tr(void *ptr, t_ray new);
void				chng_sq(void *ptr, t_ray new);

void				stretch_sp(void *ptr, t_ray new);
void				stretch_pl(void *ptr, t_ray new);
void				stretch_cy(void *ptr, t_ray new);
void				stretch_tr(void *ptr, t_ray new);
void				stretch_sq(void *ptr, t_ray new);

int					chng_ocam(int i, void *swap);
int					get_pos(int i, int x, int y, void *swap);
int					quit(int rt, void *swap);
int					stereo(t_swap *s);
int					stretch(int i, int x, int y, void *swap);
int					swap_cam(int i, void *swap);

void				fill_bmp(char **data, t_swap *s);
void				header_bmp(char **data, t_swap *s);
void				export_bmp(char *filename, t_swap *s);
char				*create_bmp_filename(char *file, int i);

static int			(*g_get_obj[NB_FORM + 1])(char *line, void **ptr) = {
	get_sphere,
	get_plane,
	get_cylindre,
	get_triangle,
	get_square,
};

static t_inter		(*g_get_inter[NB_FORM])
	(t_ray ray, void *ptr, double start, double max) = {
	intersp,
	interpl,
	intercy,
	intertr,
	intersq,
};

static void			(*g_chng_stretch[NB_FORM])(void *ptr, t_ray new) = {
	stretch_sp,
	stretch_pl,
	stretch_cy,
	stretch_tr,
	stretch_sq,
};

static void			(*g_chng_origin[NB_FORM])(void *ptr, t_ray new) = {
	chng_sp,
	chng_pl,
	chng_cy,
	stretch_tr,
	chng_sq,
};

#endif
