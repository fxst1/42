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

void		key_spec(int keycode, t_env *e)
{
	t_point	p;

	if (keycode == MULT)
	{
		p = init_point(2, 2, 2, 0);
		do_fdf(e->fdf, &homothesie, &p);
	}
	else if (keycode == DIVIDE)
	{
		p = init_point(0.5, 0.5, 0.5, 0);
		do_fdf(e->fdf, &homothesie, &p);
	}
	else if (keycode == PLUS)
	{
		e->z_dx += 0.25;
		e->z_dy += 0.25;
	}
	else if (keycode == LESS)
	{
		e->z_dx -= 0.25;
		e->z_dy -= 0.25;
	}
}

int			key_input(int keycode, t_env *e)
{
	int	stop;

	stop = 0;
	if (e->mask & IN_SAVE)
	{
		if ((e->save = mlx_key_str(keycode, &stop)) && stop)
		{
			ft_strcat(e->save, ".fdf");
			save_fdf(e->fdf, e->save);
			free(e->save);
			e->mask ^= IN_SAVE;
			e->save = NULL;
		}
	}
	else if (e->select)
		e->select->z = mlx_key_number(keycode, &stop);
	if (stop)
	{
		e->mask ^= IN_INPUT;
		open_close_color(e, 0);
	}
	return (0);
}

int			key_hook(int keycode, t_env *e)
{
	if (keycode == ECH)
	{
		free_env(e);
		exit(0);
	}
	else if (e->mask & IN_INPUT)
		key_input(keycode, e);
	else if (keycode == KEY_S)
	{
		e->mask ^= IN_INPUT;
		e->mask ^= IN_SAVE;
	}
	else if (keycode == KEY_I)
		e->mask ^= INFO;
	else if (keycode == UP)
		e->y -= 100;
	else if (keycode == DOWN)
		e->y += 100;
	else if (keycode == LEFT)
		e->x += 100;
	else if (keycode == RIGHT)
		e->x -= 100;
	else
		key_spec(keycode, e);
	return (expose_hook(e));
}

int			mouse_hook(int btn, int x, int y, t_env *e)
{
	t_point	*p;
	int		nan;

	nan = 0;
	(void)btn;
	if ((p = get_point_at(e, x, y)))
	{
		e->select = p;
		open_close_color(e, 1);
		mlx_key_number(0, &nan);
		e->mask |= IN_INPUT;
	}
	else
	{
		open_close_color(e, 0);
		e->select = NULL;
		e->mask &= ~IN_INPUT;
	}
	expose_hook(e);
	return (0);
}

int			expose_hook(t_env *e)
{
	clear(e);
	draw_fdf(e, e->fdf);
	if (e->select)
		draw_pt(e, e->select);
	mlx_put_image_to_window(e->mlx, e->screen, e->img, 0, 0);
	print_info(e, e->select);
	return (0);
}
