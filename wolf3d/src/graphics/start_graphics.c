#include <graphics.h>

t_graphics		*start_graphics(char *name, int x, int y)
{
	t_graphics	*g;

	if (!(g = malloc(sizeof(t_graphics))))
	{
		write(2, "Out of memory\n", 14);
		return (NULL);
	}
	ft_bzero(g, sizeof(t_graphics));
	g->c = new_camera();
	g->w = load_wolf_3d(name);
	if (!(g->mlx = mlx_init()))
	{
		write(2, "Cannot initialize mlx\n", 22);
		return (NULL);
	}
	if (!(g->screen = mlx_new_window(g->mlx, x, y, name)))
	{
		write(2, "Cannot create main window\n", 26);
		return (NULL);
	}
	if (!(g->img = mlx_new_image(g->mlx, x, y)))
	{
		write(2, "Cannot create image\n", 20);
		return (NULL);
	}
	g->buf = malloc(sizeof(t_buffer));
	ft_bzero(g->buf, sizeof(t_buffer));
	g->buf->h = y;
	g->buf->l = x;
	g->buf->data = mlx_get_data_addr(g->img, &g->buf->bpp, &g->buf->size_line, &g->buf->endian);
	mlx_put_image_to_window(g->mlx, g->screen, g->img, 0, 0);
	mlx_key_hook(g->screen, event, g);
	return (g);
}

