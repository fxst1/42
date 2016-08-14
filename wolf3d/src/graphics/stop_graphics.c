#include <graphics.h>

void			stop_graphics(t_graphics *g)
{
	mlx_destroy_image(g->mlx, g->img);
	mlx_destroy_window(g->mlx, g->screen);
	free(g->buf);
	free(g);
	exit(0);
}
