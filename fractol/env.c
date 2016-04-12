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

t_env	*new_env(t_env *e, int h, int l, char *name)
{
	e->mask = 0;
	e->h = h;
	e->l = l;
	e->buffer = (t_buffer*)malloc(sizeof(t_buffer));
	e->mlx = mlx_init();
	e->screen = mlx_new_window(e->mlx, l, h, name);
	e->img = mlx_new_image(e->mlx, l, h);
	e->buffer->data = mlx_get_data_addr(e->img, &e->buffer->bpp,
		&e->buffer->size_line, &e->buffer->endian);
	e->buffer->l = l;
	e->buffer->h = h;
	return (e);
}

void	free_env(t_env *e)
{
	if (e)
	{
		mlx_destroy_window(e->mlx, e->screen);
		mlx_destroy_image(e->mlx, e->img);
		ft_memdel((void**)&e->buffer);
		ft_memdel((void**)&e->mlx);
	}
}
