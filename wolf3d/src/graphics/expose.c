#include <graphics.h>

void		clear(t_buffer *buf)
{
	int x;
	int	y;

	x = 0;
	y = 0;
	while (x < buf->l)
	{
		y = 0;
		while (y < buf->h)
		{
			put_pixel(buf, x, y, 0x0);
			y++;
		}
		x++;
	}
}

int			expose_hook(t_graphics *e)
{
	clear(e->buf);
	mlx_put_image_to_window(e->mlx, e->screen, e->img, 0, 0);
	return (0);
}
