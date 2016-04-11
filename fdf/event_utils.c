/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 10:53:41 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/11 10:53:43 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point		*get_point_at(t_env *e, int x, int y)
{
	int		i;
	int		j;
	t_point	***fdf;
	t_point	p;

	i = 0;
	j = 0;
	fdf = e->fdf;
	while (fdf[i])
	{
		j = 0;
		while (fdf[i][j])
		{
			build_3d_pt(e, fdf[i][j], &p);
			if (p.x - 5 <= x && p.x + 5 >= x
				&& p.y - 5 <= y && p.y + 5 >= y)
				return (fdf[i][j]);
			j++;
		}
		i++;
	}
	return (NULL);
}

int			mouse_pick_color(int btn, int x, int y, t_env *e)
{
	(void)btn;
	if (e->select)
	{
		e->select->coul = (x * 255) / 200 + ((((200 - x) * 255) / 200) << 16) +
						(((y * 255) / 200) << 8);
		open_close_color(e, 0);
	}
	return (0);
}

int			pseudo_useless_key_event(int keycode, t_env *e)
{
	if (keycode == ECH)
		open_close_color(e, 0);
	return (0);
}

void		draw_pt(t_env *e, t_point *p)
{
	int		i;
	int		j;
	t_point	t;

	i = 0;
	j = 0;
	build_3d_pt(e, p, &t);
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			put_pixel(e->buf, t.x + i - 5, t.y + j - 5, p->coul & 0xffffff);
			j++;
		}
		i++;
	}
}

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
			put_pixel(e->buf, x, y, 0x0);
			y++;
		}
		x++;
	}
}
