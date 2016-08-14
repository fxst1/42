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
	char		*tmp;

	tmp = ft_itoa(e->nb_iter);
	mlx_string_put(e->mlx, e->screen, 0, 10, 0xffffff, "=============== Values ===============");
	mlx_string_put(e->mlx, e->screen, 0, 20, 0xffffff, "= iterations: ");
	mlx_string_put(e->mlx, e->screen, 100, 20, 0xffffff, tmp);
	free(tmp);
	mlx_string_put(e->mlx, e->screen, 0, 30, 0xffffff, "= fractal: ");
	if (e->fractal == &julia)
		mlx_string_put(e->mlx, e->screen, 100, 30, 0xffffff, "Julia");
	else if (e->fractal == &mandelbrot)
		mlx_string_put(e->mlx, e->screen, 100, 30, 0xffffff, "Mandelbrot");
	else if (e->fractal == &burning_ship)
		mlx_string_put(e->mlx, e->screen, 100, 30, 0xffffff, "Burning ship");
	else
		mlx_string_put(e->mlx, e->screen, 100, 30, 0xff, "Error occured");		
	mlx_string_put(e->mlx, e->screen, 0, 40, 0xffffff, "= mode: ");
	if (e->mask & PAUSE_MODE)
		mlx_string_put(e->mlx, e->screen, 100, 40, 0xffffff, "PAUSE");
	else
		mlx_string_put(e->mlx, e->screen, 100, 40, 0xffffff, "MOUSE");
	mlx_string_put(e->mlx, e->screen, 0, 50, 0xffffff, "======================================");
}

t_env	*new_env(t_env *e, int h, int l, char *name)
{
	e->mask = 0;
	e->buffer = (t_buffer*)malloc(sizeof(t_buffer));
	e->mlx = mlx_init();
	e->screen = mlx_new_window(e->mlx, l, h, name);
	e->img = mlx_new_image(e->mlx, l, h);
	e->buffer->data = mlx_get_data_addr(e->img, &e->buffer->bpp,
		&e->buffer->size_line, &e->buffer->endian);
	e->buffer->l = l;
	e->buffer->h = h;
	e->filename = NULL;
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

void	init_arg(t_arg *a, t_env *e, double s, double v)
{
	a->s = s;
	a->v = v;
	(void)e;
}