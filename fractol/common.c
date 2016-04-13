#include "env.h"

void	put_pixel(t_buffer *buf, int x, int y, int c)
{
	int		size_line;
	int		bpp;
	char	*data;

	data = buf->data;
	bpp = buf->bpp;
	size_line = buf->size_line;
	if (x > 0 && x < buf->l && y > 0 && y < buf->h)
	{
		data[(y * size_line + x * bpp / 8) + 3] = 0;
		data[(y * size_line + x * bpp / 8) + 2] =
			(c >> 16) & 0xff;
		data[(y * size_line + x * bpp / 8) + 1] =
			(c >> 8) & 0xff;
		data[(y * size_line + x * bpp / 8)] =
			(c & 0xff);
	}
}

void		clear(t_env *e, int c)
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
			put_pixel(e->buffer, x, y, c);
			y++;
		}
		x++;
	}
}

void		reset_color(t_env *e, int c)
{
	int			x;
	int			y;
	int			i;
	t_buffer	*buf;

	x = 0;
	y = 0;
	buf = e->buffer;
	while (x < e->l)
	{
		y = 0;
		while (y < e->w)
		{
			i = y * buf->size_line + x * buf->bpp / 8;
			if (buf->data[i + 1] && buf->data[i + 2] && buf->data[i])
			{
				buf->data[i + 3] = 0;
				buf->data[i + 2] ^= ((c >> 16) & 0xff);
				buf->data[i + 1] ^= ((c >> 8) & 0xff);
				buf->data[i] ^= (c & 0xff);
				buf->data[i + 2] &= (0xff);
				buf->data[i + 1] &= (0xff);
				buf->data[i] &= (0xff);
			}
			y++;
		}
		x++;
	}
}


int		wtf(double h, double s, double v)
{
	double c;
	double x;
	double m;

	c = v * s;
	m = v - c;
	h = fmod(h , 360);
	x = c * (1 - fabs(fmod(h / 60.0, 2) - 1.0));
	if (h >= 0 && h < 60)
		return(((u_char)((c + m) * 255) << 16)
			+ ((u_char)((x + m) *255) << 8) + m * 255);
	if (h >= 60 && h < 120)
		return(((u_char)((x + m) * 255) << 16)
			+ ((u_char)((c + m) * 255) << 8) + m * 255);
	if (h >= 120 && h < 180)
		return(((u_char)(m * 255) << 16)
			+ ((u_char)((c + m) * 255) << 8) + (u_char)((x + m)* 255));
	if (h >= 180 && h < 240)
		return(((u_char)(m * 255) << 16)
			+ ((u_char)((x + m) * 255) << 8) + (u_char)((c + m)* 255));
	if (h >= 240 && h < 300)
		return(((u_char)((x + m) * 255) << 16)
			+ ((u_char)(m * 255) << 8) + (u_char)((c + m)* 255));
	if (h < 360)
		return(((u_char)((c + m) * 255) << 16)
			+ ((u_char)(m * 255) << 8) + (u_char)((x + m)* 255));
	return(((u_char)((m) * 255) << 16)
		+ ((u_char)(m * 255) << 8) + (u_char)((m)* 255));
}
