/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 22:45:31 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/24 22:45:32 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void		key_spec(int keycode, t_env *e)
{
	t_point	p;

	if (keycode == 67)
	{
		p = init_point(2, 2, 2, 0);
		do_fdf(e->fdf, &homothesie, &p);
	}
	else if (keycode == 75)
	{
		p = init_point(0.5, 0.5, 0.5, 0);
		do_fdf(e->fdf, &homothesie, &p);
	}
	else if (keycode == 69)
	{
		e->z_dx += 0.25;
		e->z_dy += 0.25;
	}
	else if (keycode == 78)
	{
		e->z_dx -= 0.25;
		e->z_dy -= 0.25;
	}
}

int			key_hook(int keycode, t_env *e)
{
	printf("%d\n", keycode);
	if (keycode == 53)
	{
		free_env(e);
		exit(0);
	}
	else if (keycode == 126)
		e->y -= 100;
	else if (keycode == 125)
		e->y += 100;
	else if (keycode == 124)
		e->x += 100;
	else if (keycode == 123)
		e->x -= 100;
	else if (keycode == 0)
		e->mask = (e->mask & DRAW_AXIS) ? e->mask & ~(DRAW_AXIS)
			: e->mask | DRAW_AXIS;
	else if (keycode == 14)
		e->mask = (e->mask & EDITOR) ? e->mask & ~(EDITOR)
			: e->mask | EDITOR;
	else
		key_spec(keycode, e);
	expose_hook(e);
	return (keycode);
}

int			expose_hook(t_env *e)
{
	if (e->mask & EDITOR)
		active_editor(e);
	clear(e);
	draw_fdf(e, e->fdf);
	if (e->mask & DRAW_AXIS)
		draw_axis(e);
	mlx_put_image_to_window(e->mlx, e->screen, e->img, 0, 0);
	return (0);
}
