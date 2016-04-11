/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 08:57:52 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/11 08:57:54 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_keycode(int keycode, int *tab, int size, int *end)
{
	int	index;

	index = 0;
	*end = 0;
	while (index < size && tab[index] != keycode)
		index++;
	return (index);
}

int			mlx_key_number(int keycode, int *end)
{
	static int	value = 0;
	static int	nums[10] = {ZERO, ONE, TWO, THREE, FOUR,
							FIVE, SIX, SEVEN, EIGHT, NINE};
	int			tmp;

	if (keycode == 27)
		value = -value;
	else
	{
		if (((tmp = get_keycode(keycode, nums, 10, end))) < 10)
		{
			value *= 10;
			value += tmp;
			if (value > 1000 || value < -1000)
				value = (value > 0) ? 1000 : -1000;
		}
		else
		{
			tmp = value;
			*end = 1;
			value = 0;
			return (tmp);
		}
	}
	return (value);
}

char		*mlx_key_str(int keycode, int *end)
{
	static int		n = 0;
	static char		*str = NULL;
	static int		keys[38] = {65, DIVIDE, ZERO, ONE, TWO, THREE, FOUR,
	FIVE, SIX, SEVEN, EIGHT, NINE, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F,
	KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P,
	KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z};
	int				tmp;
	char			*sw;

	tmp = get_keycode(keycode, keys, 38, end);
	if (tmp < 38 && n < 1022)
	{
		str = (!str) ? ft_strnew(1024) : str;
		if (tmp < 2)
			str[n++] = (tmp == 0) ? '.' : '/';
		else
			str[n++] = (tmp < 12) ? (tmp - 2) + '0' : (tmp - 12) + 'a';
	}
	else if (str && (sw = ft_strdup(str)))
	{
		n = 0;
		ft_memdel((void**)&str);
		*end = 1;
	}
	return ((*end) ? sw : str);
}

void		open_close_color(t_env *e, int mask)
{
	if (mask && !e->buf_e)
	{
		e->buf_e = (t_buffer*)malloc(sizeof(t_buffer));
		e->screen_e = mlx_new_window(e->mlx, 200, 200, "pick a color");
		e->img_e = mlx_new_image(e->mlx, 200, 200);
		e->buf_e->data = mlx_get_data_addr(e->img_e, &e->buf_e->bpp,
		&e->buf_e->size_line, &e->buf_e->endian);
		mlx_mouse_hook(e->screen_e, mouse_pick_color, e);
		mlx_key_hook(e->screen_e, pseudo_useless_key_event, e);
		mlx_expose_hook(e->screen_e, expose_hook, e);
		color_editor(e, 200, 200);
	}
	else
	{
		free(e->buf_e);
		e->buf_e = NULL;
		if (e->screen_e)
			mlx_destroy_window(e->mlx, e->screen_e);
		e->screen_e = NULL;
		if (e->img_e)
			mlx_destroy_image(e->mlx, e->img_e);
		e->img_e = NULL;
	}
}

void		color_editor(t_env *e, int w, int h)
{
	int	x;
	int	y;
	int	color;

	x = w;
	while (x--)
	{
		y = h;
		while (y--)
		{
			color = (x * 255) / w + ((((w - x) * 255) / w) << 16) +
			(((y * 255) / h) << 8);
			mlx_pixel_put(e->mlx, e->screen_e, x, y, color);
		}
	}
}
