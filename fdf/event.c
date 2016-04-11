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
			put_pixel(e, x, y, 0x0);
			y++;
		}
		x++;
	}
}

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
	else if (e->select && e->set_z)
	{
		 e->select->z = mlx_key_number(keycode);
		printf("z = %d\n", (int)e->select->z);
	}
	else if (e->select && !e->set_z)
	{
		e->select->coul = mlx_key_number(keycode);	
		printf("c = %d\n", (int)e->select->coul);
	}
}

int			key_hook(int keycode, t_env *e)
{
	printf("%d\n", keycode);
	if (keycode == ECH)
	{
		free_env(e);
		exit(0);
	}
	else if (keycode == UP)
		e->y -= 100;
	else if (keycode == DOWN)
		e->y += 100;
	else if (keycode == LEFT)
		e->x += 100;
	else if (keycode == RIGHT)
		e->x -= 100;
	else if (keycode == 0)
		e->mask = (e->mask & DRAW_AXIS) ? e->mask & ~(DRAW_AXIS)
			: e->mask | DRAW_AXIS;
/*	else if (keycode == KEY_EDIT)
		e->mask = (e->mask & EDITOR) ? e->mask & ~(EDITOR)
			: e->mask | EDITOR;
*/	else
		key_spec(keycode, e);
	expose_hook(e);
	return (keycode);
}

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
			put_pixel(e, t.x + i - 5, t.y + j - 5, p->coul);	
			j++;
		}
		i++;
	}
}

int			mouse_hook(int btn, int x, int y, t_env *e)
{
	t_point	*p;

	(void)btn;
	if ((p = get_point_at(e, x, y)))
	{
		e->select = p;
		e->set_z = (btn == 1);
	}
	else
		e->select = NULL;
	printf("%p\n", e->select);
	expose_hook(e);
	return (0);
}

void		print_info(t_env *e, t_point *p)
{
	char	*tmp;

//	mlx_string_put(e->mlx, e->screen, 0, 0, 0xffffff, "X = ");
	if (p)
	{
		mlx_string_put(e->mlx, e->screen, 0, 10, 0xffffff, "X = ");
		tmp = ft_itoa(p->x);
		mlx_string_put(e->mlx, e->screen, 20, 10, 0xffffff, tmp);
		free(tmp);

		mlx_string_put(e->mlx, e->screen, 0, 30, 0xffffff, "Y = ");
		tmp = ft_itoa(p->y);
		mlx_string_put(e->mlx, e->screen, 20, 30, 0xffffff, tmp);
		free(tmp);

		mlx_string_put(e->mlx, e->screen, 0, 50, 0xffffff, "Z = ");
		tmp = ft_itoa(p->z);
		mlx_string_put(e->mlx, e->screen, 20, 50, 0xffffff, tmp);
		free(tmp);

		mlx_string_put(e->mlx, e->screen, 0, 70, 0xffffff, "C = ");
		tmp = ft_itoa(p->coul);
		mlx_string_put(e->mlx, e->screen, 20, 70, 0xffffff, tmp);
		free(tmp);
	}
}

int			expose_hook(t_env *e)
{
	clear(e);
	draw_fdf(e, e->fdf);
	if (e->select)
		draw_pt(e, e->select);
	if (e->mask & DRAW_AXIS)
		draw_axis(e);
	mlx_put_image_to_window(e->mlx, e->screen, e->img, 0, 0);
	print_info(e, e->select);
	return (0);
}
