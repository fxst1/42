#include <wall.h>
#include <fcntl.h>
#include <unistd.h>
#include <libft/libft.h>
#include <libft/get_next_line.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <graphics.h>
extern int errno;

int		main(int argc, char **argv)
{
	int		ret;

	t_graphics *g = NULL;
	ret = 0;
	if (argc > 1)
	{
		argv++;
		while (*argv && !ret)
		{
			if (!(g = start_graphics(*argv, 1000, 1000)))
				ret = 1;
			else
			{
				load_textures(g, &g->textures, 64, 64);
				raycasting(g);
				mlx_loop(g->mlx);
			}
			argv++;
		}
	}
	else
	{
		ret = 1;
		write(2, "./wolf3d [File] [File] ...\n", 27);
	}
	return (ret);
}
