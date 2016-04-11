/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/11 09:52:58 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/11 09:53:00 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		print_edit(t_env *e, t_point *p, int x)
{
	char	*tmp;

	mlx_string_put(e->mlx, e->screen, 0, x + 10, 0xffffff, EDITOR_STR);
	mlx_string_put(e->mlx, e->screen, 0, x + 20, 0xffffff, "X = ");
	tmp = ft_itoa(p->x);
	mlx_string_put(e->mlx, e->screen, 40, x + 20, 0xffffff, tmp);
	free(tmp);
	mlx_string_put(e->mlx, e->screen, 0, x + 40, 0xffffff, "Y = ");
	tmp = ft_itoa(p->y);
	mlx_string_put(e->mlx, e->screen, 40, x + 40, 0xffffff, tmp);
	free(tmp);
	mlx_string_put(e->mlx, e->screen, 0, x + 60, 0xffffff, "Z = ");
	tmp = ft_itoa(p->z);
	mlx_string_put(e->mlx, e->screen, 40, x + 60, 0xffffff, tmp);
	free(tmp);
	mlx_string_put(e->mlx, e->screen, 0, x + 80, 0xffffff, "C = ");
	tmp = ft_itoa_base(p->coul, BASE_HEX_MIN);
	mlx_string_put(e->mlx, e->screen, 40, x + 80, 0xffffff, tmp);
	free(tmp);
	return (x + 90);
}

static int		print_data(t_env *e, int x)
{
	char	*tmp;

	mlx_string_put(e->mlx, e->screen, 0, x + 10, 0xffffff, INFO_STR);
	mlx_string_put(e->mlx, e->screen, 0, x + 20, 0xffffff, "X loc = ");
	tmp = ft_itoa((int)e->x);
	mlx_string_put(e->mlx, e->screen, 100, x + 20, 0xffffff, tmp);
	free(tmp);
	mlx_string_put(e->mlx, e->screen, 0, x + 40, 0xffffff, "Y loc = ");
	tmp = ft_itoa((int)e->y);
	mlx_string_put(e->mlx, e->screen, 100, x + 40, 0xffffff, tmp);
	free(tmp);
	mlx_string_put(e->mlx, e->screen, 0, x + 60, 0xffffff, "X scale = ");
	tmp = ft_itoa((int)e->dx);
	mlx_string_put(e->mlx, e->screen, 100, x + 60, 0xffffff, tmp);
	free(tmp);
	mlx_string_put(e->mlx, e->screen, 0, x + 80, 0xffffff, "Y scale = ");
	tmp = ft_itoa((int)e->dy);
	mlx_string_put(e->mlx, e->screen, 100, x + 80, 0xffffff, tmp);
	free(tmp);
	mlx_string_put(e->mlx, e->screen, 0, x + 100, 0xffffff, "Zx scale = ");
	tmp = ft_itoa((int)e->z_dx);
	mlx_string_put(e->mlx, e->screen, 110, x + 100, 0xffffff, tmp);
	free(tmp);
	mlx_string_put(e->mlx, e->screen, 0, x + 120, 0xffffff, "Zy scale = ");
	return (x + 120);
}

static int		print_save(t_env *e, int x)
{
	if (e->mask & IN_SAVE)
		mlx_string_put(e->mlx, e->screen, 0, x + 10, 0xffffff, SAVE_STR);
	if (e->save)
		mlx_string_put(e->mlx, e->screen, 0, x + 20, 0xffffff, e->save);
	return (x + 30);
}

void			print_info(t_env *e, t_point *p)
{
	char	*tmp;
	int		x;

	x = 0;
	if (p)
		x += print_edit(e, p, 0);
	x += print_save(e, x);
	if (e->mask & INFO)
	{
		print_data(e, x);
		tmp = ft_itoa((int)e->z_dy);
		mlx_string_put(e->mlx, e->screen, 110, x + 120, 0xffffff, tmp);
		free(tmp);
		mlx_string_put(e->mlx, e->screen, 0, x + 140, 0xffffff, "color = ");
		if (!e->mask & GRADUATE)
			tmp = (!e->mask & RANDOM) ? NORMAL_STR : RANDOM_STR;
		else
			tmp = GRAD_STR;
		mlx_string_put(e->mlx, e->screen, 90, x + 140, 0xffffff, tmp);
	}
}
