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
# undef BUFF_SIZE
# define BUFF_SIZE 1000
# define RANDOM	1
# define NORMAL	0
# define GRADUATE 2
# define DRAW_AXIS 1
# define EDITOR 2
# define LINE_GRADIENT 0xff
# define LINE_DEPTH	0xff00ff
# include <libft/os.h>
# if (OS_FT != MAC)
#  define ECH 65307
#  define UP 65362
#  define DOWN 65364
#  define LEFT 65363
#  define RIGHT 65361
#  define DIVIDE 65455
#  define MULT 65450
#  define PLUS 65451
#  define LESS 65453
#  define KEY_EDIT 101
#  define ONE 65436
#  define TWO 65433
#  define THREE 65435
#  define FOUR 65430
#  define FIVE 65437
#  define SIX 65432
#  define SEVEN 65429
#  define EIGHT 65431
#  define NINE 65434
#  define ZERO 65438
# else
#  define ECH 55
#  define UP 126
#  define DOWN 125
#  define LEFT 124
#  define RIGHT 123
#  define DIVIDE 75
#  define MULT 67
#  define PLUS 69
#  define LESS 78
#  define KEY_EDIT 14
#  define ONE 65436
#  define TWO 65433
#  define THREE 65435
#  define FOUR 65430
#  define FIVE 65437
#  define SIX 65432
#  define SEVEN 65429
#  define EIGHT 65431
#  define NINE 65434
#  define ZERO 65438
# endif
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
	int					colorfdf;
	int					mask;

	t_buffer			*buf;
	t_buffer			*edit;

	void				*mlx;
	void				*img;
	void				*img_e;
	t_scn				*screen;
	t_scn				*editor;
	t_point				***fdf;

	t_coord				dx;
	t_coord				dy;
	t_coord				z_dx;
	t_coord				z_dy;
	t_coord				x;
	t_coord				y;
	t_point				*select;
	int					set_z;
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

int						mlx_key_number(int keycode);
int						mouse_hook(int btn, int x, int y, t_env *e);
void					put_pixel_edit(t_env *e, int x, int y, int c);
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
void					free_env(t_env *e);
void					draw_line(t_env *e, t_point p1, t_point p2, int color);
t_env					*new_env(int h, int l);
t_point					*new_point(int x, int y, int z, int coul);
void					set_point(t_point *pt, int x, int y, int z);
void					draw_fdf(t_env *e, t_point ***p);
void					reset_color(t_point ***vct);
t_point					*homothesie(t_point	*p, t_point *del);
t_point					*translate(t_point	*p, t_point *vect);
t_line					init_line(t_point p1, t_point p2);
t_point					init_point(t_coord x, t_coord y, t_coord z, t_color c);
void					init_color(t_env *e, t_point *p);
void					put_pixel(t_env *e, int x, int y, int c);
void					clear_image(t_env *e);
void					build_3d_pt(t_env *e, t_point *p, t_point *dst);
t_point					init_point(t_coord x, t_coord y, t_coord z, t_color c);
t_rgb					init_rgb(t_color coul);
void					active_editor(t_env *e);

#endif
