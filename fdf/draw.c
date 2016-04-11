/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 22:40:19 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/24 22:40:21 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_env *e, int x, int y, int c)
{
	t_buffer	*buf;

	buf = e->buf;
	if (x > 0 && x < e->l && y > 0 && y < e->h)
	{
		buf->data[(y * buf->size_line + x * buf->bpp / 8) + 3] =  (c >> 24) & 0xff;
		buf->data[(y * buf->size_line + x * buf->bpp / 8) + 2] =
			(c >> 16) & 0xff;
		buf->data[(y * buf->size_line + x * buf->bpp / 8) + 1] =
			(c >> 8) & 0xff;
		buf->data[(y * buf->size_line + x * buf->bpp / 8)] =
			(c & 0xff);
	}
}

int		*init_gradient(int n, t_point p1, t_point p2)
{
	int		i;
	t_rgb	delt;
	t_rgb	c2;
	t_rgb	c1;
	int		*coul;

	c2 = init_rgb(p1.coul);
	c1 = init_rgb(p2.coul);
	coul = NULL;
	if (n > 0 && (coul = (int*)malloc(sizeof(int) * (n))))
	{
		delt.r = (c2.r - c1.r) / n;
		delt.g = (c2.g - c1.g) / n;
		delt.b = (c2.b - c1.b) / n;
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
	return (coul);
}

void	draw_line_x(t_env *e, t_line *l, t_point p1, t_color c)
{
	t_point	abs;
	t_point	sd;
	t_point	p;
	int		i;

	abs = l->abs;
	sd = l->sd;
	p = l->p;
	i = 0;
	while (i < abs.x)
	{
		p.y += abs.y;
		if (p.y >= abs.x)
		{
			p.y -= abs.x;
			p1.y += sd.y;
		}
		p1.x += sd.x;
		put_pixel(e, p1.x, p1.y, ((l->coul) ? l->coul[i] : (int)c));
		i++;
	}
}

void	draw_line_y(t_env *e, t_line *l, t_point p1, t_color c)
{
	t_point	abs;
	t_point	sd;
	t_point	p;
	int		i;

	abs = l->abs;
	sd = l->sd;
	p = l->p;
	i = 0;
	while (i < abs.y)
	{
		p.x += abs.x;
		if (p.x >= abs.y)
		{
			p.x -= abs.y;
			p1.x += sd.x;
		}
		p1.y += sd.y;
		put_pixel(e, p1.x, p1.y, (l->coul) ? l->coul[i] : (int)c);
		i++;
	}
}

void	draw_line(t_env *e, t_point p1, t_point p2, int color)
{
	t_line	l;

	l = init_line(p1, p2);
	if (l.abs.x >= l.abs.y)
	{
		l.coul = init_gradient((int)l.abs.x, p1, p2);
		draw_line_x(e, &l, p1, color);
	}
	else
	{
		l.coul = init_gradient((int)l.abs.y, p1, p2);
		draw_line_y(e, &l, p1, color);
	}
	if (l.coul)
		free(l.coul);
}
