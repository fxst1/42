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
# include <SDL.h>
# include <SDL_audio.h>
//# include "X11/Xlib.h"
# include "keys.h" 
# define BSHIP 3
# define MANDELBROT 1
# define JULIA 2
# define NB_THREAD 25
# define TH_SCL 100
# define INPUT_MODE 64
# define ANIM_MODE 16
# define PTR_MOTION_MASK (1L<<6)
# define MOTION_NOTIFY 6
# define KEY_PRESS_MASK (1L<<0)
# define KEY_PRESS 2

# define WEIGTH			1000
# define LENGTH			1000
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

typedef struct			s_arg
{
	double				s;
	double				v;
	int					y;
	int					x;
}						t_arg;

typedef struct			s_env
{
	pthread_t			th[1024];
	t_arg				arguments[1024];
	int					w;
	int					l;
	int					mask;

	t_buffer			*buffer;
	void				*mlx;
	void				*img;
	t_scn				*screen;

	t_scn				*info;

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
	int					machin;

//	Mix_Music			*music;
	char				*filename;
}						t_env;
/*
typedef	struct			s_music
{
	Mix_Music			*data;
	int					freq_alpha;
	int					freq_beta;
}						t_music;
*/
void		random_animation(t_env *e);
void		init_threads(t_env *e, t_arg *arguments);
t_env		*new_env(t_env *e, int h, int l, char *name);
void		free_env(t_env *e);
void		init_arg(t_arg *a, t_env *e, double s, double v);
void		clear(t_env *e, int c);
void		reset_color(t_env *e, int c);
void		put_pixel(t_buffer *buf, int x, int y, int c);
int    		 wtf(double h, double s, double v);
void		*burning_ship(t_arg *a);
void		*mandelbrot(t_env *e);
void		*julia(t_env *a);
char		*mlx_key_str(int keycode, int *end);
//Mix_Music	*start_music(char *filename);
//void		*stop_music(Mix_Music *music);
#endif
