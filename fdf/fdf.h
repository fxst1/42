/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:32:07 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 04:32:09 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../libft/implemt.h"
# include "keys.h"
# include <limits.h>
# undef BUFF_SIZE
# define BUFF_SIZE 1000
# define RANDOM	1
# define NORMAL	4
# define IN_SAVE 32
# define IN_INPUT 64
# define INFO 16
# define SET_COLOR 8
# define SET_Z	128

# define GRADUATE 2
# define LINE_GRADIENT 0xff
# define LINE_DEPTH	0xff00ff

# define EDITOR_STR "-----------------  EDITOR  -----------------"
# define INFO_STR "-----------------  INFOS  -----------------"
# define SAVE_STR "-----------------  SAVE  -----------------"
# define RANDOM_STR "useless random"
# define GRAD_STR "graduate"
# define NORMAL_STR "default"
# define USAGE "Usage: ./fdf [file] [--color=[graduate, random, depth]]\n"
# include <string.h>
# include <errno.h>

typedef void			*t_scn;

typedef double			t_coord;

typedef unsigned int	t_color;

typedef struct			s_rgb
{
	int					r;
	int					g;
	int					b;
}						t_rgb;

typedef struct			s_point
{
	t_coord				x;
	t_coord				y;
	t_coord				z;
	t_color				coul;
}						t_point;

typedef struct			s_buffer
{
	int					size_line;
	int					endian;
	int					bpp;
	char				*data;
	int					h;
	int					l;
}						t_buffer;

typedef struct			s_editor
{
	int					h;
	int					l;

	t_scn				screen;
}						t_editor;

typedef struct			s_env
{
	int					h;
	int					l;
	char				*save;
	int					mask;

	t_buffer			*buf;
	void				*mlx;
	void				*img;
	t_scn				*screen;

	t_buffer			*buf_e;
	void				*img_e;
	void				*screen_e;
	t_point				***fdf;

	t_coord				dx;
	t_coord				dy;
	t_coord				z_dx;
	t_coord				z_dy;
	t_coord				x;
	t_coord				y;
	t_point				*select;
}						t_env;

typedef struct			s_line
{
	t_point				abs;
	t_point				p;
	t_point				sd;
	int					*coul;
}						t_line;

typedef	struct			s_color_grad
{
	t_color				*colors;
	int					nb_values;
}						t_color_grad;

int						mouse_pick_color(int btn, int x, int y, t_env *e);
int						pseudo_useless_key_event(int keycode, t_env *e);
void					color_editor(t_env *e, int w, int h);
char					*key_str(int keycode, int *end);
void					clear(t_env *e);
int						mlx_key_number(int keycode, int *end);
char					*mlx_key_str(int keycode, int *end);
void					draw_pt(t_env *e, t_point *p);
t_point					*get_point_at(t_env *e, int x, int y);
void					print_info(t_env *e, t_point *p);
int						key_number(int keycode, int *end);
int						mouse_hook(int btn, int x, int y, t_env *e);
void					print_fdf(t_point ***p);
void					draw_axis(t_env *e);
int						key_hook(int keycode, t_env *e);
int						expose_hook(t_env *e);
void					do_fdf(t_point ***vct, t_point *(*fct)(), t_point *arg);
void					save_fdf(t_point ***p, char *fname);
void					set_scales(t_env *e, t_point ***pt);
t_point					***init_fdf_points(int fd);
t_point					***init_fdf(int mask, int const fd, t_point ***p);
void					free_fdf(t_point ***p);
void					free_env(t_env *e);
void					draw_line(t_env *e, t_point p1, t_point p2, int color);
t_env					*new_env(t_env *e, int h, int l, char *fname);
t_point					*new_point(int x, int y, int z, int coul);
void					set_point(t_point *pt, int x, int y, int z);
void					draw_fdf(t_env *e, t_point ***p);
void					reset_color(t_point ***vct);
t_point					*homothesie(t_point	*p, t_point *del);
t_point					*translate(t_point	*p, t_point *vect);
t_line					init_line(t_point p1, t_point p2);
t_point					init_point(t_coord x, t_coord y, t_coord z, t_color c);
void					init_color(int mask, t_point *p);
void					put_pixel(t_buffer *buf, int x, int y, int c);
void					clear_image(t_env *e);
void					build_3d_pt(t_env *e, t_point *p, t_point *dst);
t_point					init_point(t_coord x, t_coord y, t_coord z, t_color c);
t_rgb					init_rgb(t_color coul);
void					open_close_color(t_env *e, int mask);

#endif
