/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 00:40:26 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/25 00:40:29 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void			print_info(t_env *e)
{
	int	x;

	x = 0;
	mlx_string_put(e->mlx, e->info, 0, x + 10, 0xffffff, "=============== ENVIROMENT ===============");
	if (e->filename)
	{
		mlx_string_put(e->mlx, e->info, 0, x + 30, 0xffffff, "============== MUSIC ==============");
		mlx_string_put(e->mlx, e->info, 0, x + 50, 0xffffff, "filename:");
		mlx_string_put(e->mlx, e->info, 110, x + 50, 0xffffff, e->filename);
	}
}


int			key_info(int keycode, t_env *e)
{
	int	stop;

	stop = 0;
	
	if (e->mask & INPUT_MODE)
	{
		e->filename = mlx_key_str(keycode, &stop);
		if (stop)
			e->mask ^= INPUT_MODE;
	}
	else if (keycode == 35)
		e->mask |= INPUT_MODE;
	else
	{
	}
	print_info(e);
	return (0);
}

int			expose_info(t_env *e)
{
	mlx_clear_window(e->mlx, e->info);
	print_info(e);
	return (0);
}

t_env	*new_env(t_env *e, int h, int l, char *name)
{
	e->mask = 0;
	e->w = h;
	e->l = l;
	e->buffer = (t_buffer*)malloc(sizeof(t_buffer));
	e->mlx = mlx_init();
	e->screen = mlx_new_window(e->mlx, l, h, name);
	e->img = mlx_new_image(e->mlx, l, h);
	e->buffer->data = mlx_get_data_addr(e->img, &e->buffer->bpp,
		&e->buffer->size_line, &e->buffer->endian);
	e->buffer->l = l;
	e->buffer->h = h;
	e->info = mlx_new_window(e->mlx, 600, 300, "information");
	e->filename = NULL;
	mlx_key_hook(e->info, key_info, e);
	mlx_expose_hook(e->info, expose_info, e);
	return (e);
}

void	free_env(t_env *e)
{
	if (e)
	{
		mlx_destroy_window(e->mlx, e->screen);
		mlx_destroy_window(e->mlx, e->info);
		mlx_destroy_image(e->mlx, e->img);
		ft_memdel((void**)&e->buffer);
		ft_memdel((void**)&e->mlx);
	}
}

void	init_arg(t_arg *a, t_env *e, double s, double v)
{
	a->s = s;
	a->v = v;
}