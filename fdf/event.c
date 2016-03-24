#include "fdf.h"

void		clear(t_env *e)
{
	int x;
	int	y;

	x = 0;
	y = 0;
	while (x < e->l)
	{
		y = 0;
		while (y < e->h)
		{
			put_pixel(e, x, y, 0);
			y++;
		}
		x++;
	}
}

int			key_hook(int keycode, t_env *e)
{
	t_point	p;

	p.x = 0;
	p.y = 0;
	p.z = 0;
	printf("%d\n", keycode);
	if (keycode == 53)
	{
		free_env(e);
		exit(0);
	}
	else if (keycode == 126)
	{
		e->y -= 10;
		p.y -= 1;
		do_fdf(e->fdf, &translate, &p);
	}
	else if (keycode == 125)
	{
		e->y += 10;
		p.y += 1;
		do_fdf(e->fdf, &translate, &p);
	}
	else if (keycode == 124)
	{
		e->x += 10;
		p.x += 1;
		do_fdf(e->fdf, &translate, &p);
	}
	else if (keycode == 123)
	{
		e->x -= 10;
		p.x -= 1;
		do_fdf(e->fdf, &translate, &p);
	}
	else if (keycode == 67)
	{
		p.x = 2;
		p.y = 2;
		p.z = 2;
		do_fdf(e->fdf, &homothesie, &p);
	}
	else if (keycode == 75)
	{
		p.x = 0.5;
		p.y = 0.5;
		p.z = 0.5;
		do_fdf(e->fdf, &homothesie, &p);
	}
	else if (keycode == 69)
	{
		e->z_dx += 0.5;
		e->z_dy += 0.5;
	}
	else if (keycode == 78)
	{
		e->z_dx -= 0.5;
		e->z_dy -= 0.5;
	}
	else if (keycode == 0)
		e->mask = (e->mask & DRAW_AXIS) ? e->mask & ~(DRAW_AXIS)
			: e->mask | DRAW_AXIS;
	//mlx_clear_window(e->mlx, e->screen);
	//ft_memset(e->buf->data, 0, e->buf->size_line * e->buf->bpp * e->l);
	clear(e);
	draw_fdf(e, e->fdf);
	if (e->mask & DRAW_AXIS)
		draw_axis(e);
	mlx_put_image_to_window(e->mlx, e->screen, e->img, 0, 0);
	return (keycode);
}

int			expose_hook(t_env *e)
{
	//mlx_clear_window(e->mlx, e->screen);
	draw_fdf(e, e->fdf);
	if (e->mask & DRAW_AXIS)
		draw_axis(e);
	mlx_put_image_to_window(e->mlx, e->screen, e->img, 0, 0);
	return (0);
}
