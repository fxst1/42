#include "fdf.h"

void	draw_axis(t_env *e)
{
	t_point	o;
	t_point	x;
	t_point	y;
	t_point	z;

	set_point(&o, e->x, e->y, 1);
	o.coul = 0xffffff;
	set_point(&x, e->x + 100, e->y, 1);
	x.coul = 0xFF;
	set_point(&y, e->x, e->y + 100, 1);
	y.coul = 0xFF0000;
	set_point(&z, e->x + e->z_dx, e->y + e->z_dy, 1);
	z.coul = 0xFF00;
	draw_line(e, x, o, 0xff);
	draw_line(e, o, y,0xff00);
	draw_line(e, o, z, 0xff0000);
}

void	clear_image(t_env *e)
{
	ft_memset(e->buf->data, 0, (e->h * e->buf->bpp * e->l));
}

void	put_pixel(t_env *e, int x, int y, int c)
{
	t_buffer	*buf;

	buf = e->buf;
	if (x > 0 && x < e->l && y > 0 && y < e->h)
	{
		buf->data[(y * buf->size_line + x * buf->bpp / 8) + 2] = (c >> 16) & 0xff;
		buf->data[(y * buf->size_line + x * buf->bpp / 8) + 1] = (c >> 8) & 0xff;
		buf->data[(y * buf->size_line + x * buf->bpp / 8)] = (c & 0xff);
	}
}

int		*init_gradient(int n, t_point p1, t_point p2)
{
	int		i;
	t_rgb	delt;
	t_rgb	c2;
	t_rgb	c1;
	int		*coul;

	i = 0;
	c2.r = (p2.coul & 0xff0000) >> 16;
	c2.g = (p2.coul & 0xff00) >> 8;
	c2.b = p2.coul & 0xff;
	c1.r = (p1.coul & 0xff0000) >> 16;
	c1.g = (p1.coul & 0xff00) >> 8;
	c1.b = p1.coul & 0xff;
	if (n)
	{
		delt.r = (c2.r - c1.r) / n;
		delt.g = (c2.g - c1.g) / n;
		delt.b = (c2.b - c1.b) / n;
		coul = (int*)malloc(sizeof(int) * (n));
		i = 0;
		while (i < n)
		{
			coul[i++] = (c2.r << 16) |
				(c2.g << 8) | c2.b;
			c2.r = c2.r - delt.r;
			c2.b = c2.b - delt.b;
			c2.g = c2.g - delt.g;
		}
	}
	else
		coul = NULL;
	return (coul);
}

void	draw_line(t_env *e, t_point p1, t_point p2, int color)
{
	int		i;
	t_point	abs;
	t_point	p;
	t_point	sd;
	int		*coul;

	i = 0;
	abs.x = ft_abs(p2.x - p1.x);
	abs.y = ft_abs(p2.y - p1.y);
	p.x = ((int)abs.x) >> 1;
	p.y = ((int)abs.y) >> 1;
	sd.x = (p2.x > p1.x) ? 1 : -1;
	sd.y = (p2.y > p1.y) ? 1 : -1;
	if (abs.x >= abs.y)
	{
		coul = init_gradient((int)abs.x, p2, p1);
		while (i < abs.x)
		{
			p.y += abs.y;
			if (p.y >= abs.x)
			{
				p.y -= abs.x;
				p1.y += sd.y;
			}
			p1.x += sd.x;
			put_pixel(e, p1.x, p1.y, coul[i]);
			i++;
		}
	}
	else
	{
		coul = init_gradient((int)abs.y, p2, p1);
		while (i < abs.y)
		{
			p.x += abs.x;
			if (p.x >= abs.y)
			{
				p.x -= abs.y;
				p1.x += sd.x;
			}
			p1.y += sd.y;
			put_pixel(e, p1.x, p1.y, (coul) ? coul[i] : color);
			i++;
		}
	}
	if (coul)
		free(coul);
}

void	draw_vline(t_env *e, int x, int len, int coul)
{
	int y;

	y = 0;
	while (y < len)
	{
		mlx_pixel_put(e->mlx, e->screen, x, y, coul);
		y++;
	}
}

void	draw_hline(t_env *e, int y, int len, int coul)
{
	int x;

	x = 0;
	while (x < len)
	{
		mlx_pixel_put(e->mlx, e->screen, x, y, coul);
		x++;
	}
}


void	draw_rect(t_env *e, t_point *center, int len, int h, int coul)
{
	int x, y;

	x = 0;
	while (x < len / 2)
	{
		y = 0;
		while (y < h / 2)
		{
			mlx_pixel_put(e->mlx, e->screen, center->x + x, center->y + y, coul);
			y++;
		}
		x++;
	}
}
