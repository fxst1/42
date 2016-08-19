#ifndef GRAPHICS_H
# define GRAPHICS_H
# include <libft/libft.h>
# include <libft/implemt.h>
# include <mlx.h>
# include <mlx_keys.h>
# include <math.h>
# include <wall.h>
# include <camera.h>
# include <engine.h>
# include <stdio.h>
# define MAX_TEXTURES 9
# define PTR_MOTION_MASK (1L<<6)
# define MOTION_NOTIFY 6
# define KEY_PRESS_MASK (1L<<0)
# define KEY_PRESS 2

typedef struct			s_buffer
{
	int					size_line;
	int					endian;
	int					bpp;
	char				*data;
	int					h;
	int					l;
}						t_buffer;

typedef struct			s_graphics
{
	void				*mlx;
	void				*screen;
	void				*img;
	t_buffer			*buf;
	t_world				w;
	t_camera			c;
	int					**textures;
	int					textures_w;
	int					textures_h;
}						t_graphics;

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

typedef struct			s_ray
{
	double				cam_x;
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	int					map_x;
	int					map_y;
	int					side;
	double				side_dist_x;
	double				side_dist_y;
	double				delta_dist_x;
	double				delta_dist_y;
	double				wall_dist;
}						t_ray;

/*
**	Common
*/
t_graphics				*start_graphics(char *name, int x, int y);
void					draw_vline(t_graphics *g, int x, int start, int end, int c);
void					stop_graphics(t_graphics *g);
void					raycasting(t_graphics *g);

/*
**	Events
*/
int						event(int keycode, t_graphics *g);

/*
**	Color
*/
void					reset_color(t_point ***vct);
void					init_color(int mask, t_point *p);

/*
**	Draw
*/
void					put_pixel(t_buffer *buf, int x, int y, int c);
int						*init_gradient(int n, t_point p1, t_point p2);
void					draw_line(t_graphics *e, t_point p1, t_point p2, int color);

/*
**	Point / color
*/
t_point					*new_point(int x, int y, int z, int c);
t_point					init_point(t_coord x, t_coord y, t_coord z, t_color c);
void					set_point(t_point *pt, int x, int y, int z);
t_rgb					init_rgb(t_color coul);
t_line					init_line(t_point p1, t_point p2);

int						expose_hook(t_graphics *e);

int						**load_textures(t_graphics *g, int ***texture, int w, int h);


#endif
