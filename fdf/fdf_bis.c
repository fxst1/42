/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 00:54:19 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/25 00:54:21 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			do_fdf(t_point ***vct, t_point *(*fct)(), t_point *arg)
{
	int	i;
	int	j;

	i = 0;
	while (vct[i])
	{
		j = 0;
		while (vct[i][j])
		{
			vct[i][j] = (*fct)(vct[i][j], arg);
			j++;
		}
		i++;
	}
}

void			draw_fdf(t_env *e, t_point ***p)
{
	int		i;
	int		j;
	t_point	p1;
	t_point	p2;

	i = 0;
	while (p[i])
	{
		j = -1;
		while (p[i][++j])
		{
			build_3d_pt(e, p[i][j], &p1);
			if (p[i][j + 1])
			{
				build_3d_pt(e, p[i][j + 1], &p2);
				draw_line(e, p1, p2, p1.coul + p2.coul);
			}
			if (p[i + 1] && p[i + 1][j])
			{
				build_3d_pt(e, p[i + 1][j], &p2);
				draw_line(e, p1, p2, p1.coul + p2.coul);
			}
		}
		i++;
	}
}

void			free_fdf(t_point ***p)
{
	int	i;
	int	j;

	i = 0;
	while (p[i])
	{
		j = 0;
		while (p[i][j])
		{
			free(p[i][j]);
			j++;
		}
		free(p[i]);
		i++;
	}
	free(p);
}

void			compute_fdf(t_env *e, t_point ***vct)
{
	int	i;
	int	j;

	i = 0;
	while (vct[i])
	{
		j = 0;
		while (vct[i][j])
		{
			vct[i][j]->x = e->x + (vct[i][j]->x * e->dx);
			vct[i][j]->y = e->y + (vct[i][j]->y * e->dy);
			j++;
		}
		i++;
	}
}
