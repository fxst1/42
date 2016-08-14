#ifndef WORLD_H
# define WORLD_H
# define WALL_TYPE_TEXTURE 1
# define WALL_TYPE_COLOR 2
# include <get_next_line.h>

typedef struct		s_world
{
	char			*name;
	void			**textures;
	int				x_max;
	int				y_max;
	int				**walls;
}					t_world;

#endif

