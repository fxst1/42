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

#include "fdf.h"

t_env	*new_env(int h, int l)
{
	t_env	*e;

	e = NULL;
	if ((e = (t_env*)malloc(sizeof(t_env))) &&
		((e->mlx = mlx_init())))
	{
		e->editor = NULL;
		e->mask = 0;
		e->h = h;
		e->l = l;
		e->x = 10;
		e->y = 10;
		e->dx = 1;
		e->dy = 1;
		e->z_dx = 1;
		e->z_dy = 1;
		e->colorfdf = NORMAL;
		e->buf = (t_buffer*)malloc(sizeof(t_buffer));
		e->screen = mlx_new_window(e->mlx, l, h, "win");
		e->img = mlx_new_image(e->mlx, l, h);
		e->buf->data = mlx_get_data_addr(e->img, &e->buf->bpp,
			&e->buf->size_line, &e->buf->endian);
		e->save = NULL;
		e->select = NULL;
	}
	return (e);
}

void	nb_pts(t_point ***pts, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (pts[i])
	{
		j = 0;
		while (pts[i][j])
			j++;
		if (*y < j)
			*y = j;
		i++;
	}
	*x = i;
}

void	set_scales(t_env *e, t_point ***pt)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	nb_pts(pt, &x, &y);
	if (x)
		e->dx = e->l / x;
	if (y)
		e->dy = e->h / y;
}

void	free_env(t_env *e)
{
	if (e)
	{
		if (e->save)
		{
			save_fdf(e->fdf, e->save);
			free(e->save);
		}
		free_fdf(e->fdf);
		if (e->editor)
			mlx_destroy_window(e->mlx, e->editor);
		mlx_destroy_window(e->mlx, e->screen);
		mlx_destroy_image(e->mlx, e->img);
		ft_memdel((void**)&e->buf);
		ft_memdel((void**)&e->mlx);
		ft_memdel((void**)&e);
	}
}
