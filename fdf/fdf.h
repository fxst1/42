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
# include "../get_next_line/get_next_line.h"
# include "../libft/implemt.h"
# undef BUFF_SIZE
# define BUFF_SIZE 1000
# define RANDOM	1
# define DEEP	2
# define GRADUATE 3
# define DRAW_AXIS 1
# define LINE_GRADIENT 0xff
# define LINE_DEPTH	0xff00ff
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
}						t_buffer;

typedef struct			s_env
{
	int					h;
	int					l;

	int					p;
	char				*save;
	int					colorfdf;
	int					mask;

	t_buffer			*buf;

	void				*mlx;
	void				*img;
	t_scn				*screen;

	t_point				***fdf;

	t_coord				dx;
	t_coord				dy;
	t_coord				z_dx;
	t_coord				z_dy;
	t_coord				x;
	t_coord				y;
}						t_env;

typedef struct			s_line
{
	t_point				alpha;
	t_point				beta;
	t_point				delt;
	t_coord				err;
	int					color;
}						t_line;

typedef	struct			s_color_grad
{
	t_color				*colors;
	int					nb_values;
}						t_color_grad;

void					print_fdf(t_point ***p);
void					draw_axis(t_env *e);
int						key_hook(int keycode, t_env *e);
int						expose_hook(t_env *e);
void					do_fdf(t_point ***vct, t_point *(*fct)(), t_point *arg);
void					save_fdf(t_point ***p, char *fname);
void					set_scales(t_env *e, t_point ***pt);
t_point					***init_fdf_points(char *fname);
t_point					***init_fdf(t_env *e, int const fd, t_point ***p);
void					free_fdf(t_point ***p);
void					draw_rect(t_env *e, t_point *center, int len, int h,
							int coul);
void					free_env(t_env *e);
void					draw_line(t_env *e, t_point p1, t_point p2, int color);
t_env					*new_env(int h, int l);
t_point					*new_point(int x, int y, int z, int coul);
void					set_point(t_point *pt, int x, int y, int z);
void					draw_hline(t_env *e, int x, int len, int coul);
void					draw_vline(t_env *e, int y, int len, int coul);
void					draw_fdf(t_env *e, t_point ***p);
void					reset_color(t_point ***vct);
t_point					*homothesie(t_point	*p, t_point *del);
t_point					*translate(t_point	*p, t_point *vect);
t_line					init_line(t_point a, t_point b, t_color color);
t_point					init_point(t_coord x, t_coord y, t_coord z, t_color c);
void					put_pixel(t_env *e, int x, int y, int c);
void					clear_image(t_env *e);

#endif
