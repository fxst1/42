#ifndef ENGINE_H
# define ENGINE_H
# include <fcntl.h>
# include <camera.h>
# include <graphics.h>

/*
**	Init world
*/
t_world			load_wolf_3d(char *filename);
int				read_file(t_world *w, char *filename, int fd);
int				load_walls(t_world *w, int **walls, int fd);


#endif

