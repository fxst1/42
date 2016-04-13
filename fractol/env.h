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
# include "../libft/implemt.h"
# include <limits.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <pthread.h>
# include "keys.h" 
# define BSHIP 3
# define MANDELBROT 1
# define JULIA 2
# define NB_THREAD 1024
# define TH_SCL 50

typedef void			*t_scn;

typedef double			t_coord;

typedef unsigned int	t_color;

typedef struct			s_rgb
{
	int					r;
	int					g;
	int					b;
}						t_rgb;

typedef struct	s_point
{
	t_coord		x;
	t_coord		y;
	t_color		c;
}				t_point;

typedef struct			s_buffer
{
	int					size_line;
	int					endian;
	int					bpp;
	char				*data;
	int					h;
	int					l;
}						t_buffer;

typedef struct			s_env
{
	pthread_t			th[NB_THREAD];

	int					w;
	int					l;
	int					mask;

	t_buffer			*buffer;
	void				*mlx;
	void				*img;
	t_scn				*screen;

	void				*(*fractal)();
	int					nb_iter;
	double				zoom;
	double				x;
	double				y;
	double				re;
	double				im;
	double				h;
	double				s;
	double				v;	
	long int			dc;
}						t_env;

typedef struct			s_arg
{
	t_env				*e;
	double				s;
	double				v;
	int					y;
}						t_arg;

void	init_threads(t_env *e, t_arg *arguments);
t_env	*new_env(t_env *e, int h, int l, char *name);
void	free_env(t_env *e);
void	init_arg(t_arg *a, t_env *e, double s, double v);
void	clear(t_env *e, int c);
void	reset_color(t_env *e, int c);
void	put_pixel(t_buffer *buf, int x, int y, int c);
int     wtf(double h, double s, double v);
void	*burning_ship(t_arg *a);
void	*mandelbrot(t_arg *a);
void	*julia(t_arg *a);
#endif
