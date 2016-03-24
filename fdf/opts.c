/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 23:03:10 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/24 23:03:13 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	save_fdf(t_point ***p, char *fname)
{
	int		fd;
	int		i;
	int		j;
	char	*str;

	i = -1;
	str = NULL;
	if ((fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0666)) > 0)
	{
		while (p[++i])
		{
			j = -1;
			while (p[i][++j] && ((str = ft_itoa(p[i][j]->z))))
			{
				write(fd, str, ft_strlen(str));
				if (p[i][j + 1])
					write(fd, " ", 1);
				free(str);
				j++;
			}
			if (p[i + 1])
				write(fd, "\n", 1);
		}
	}
	close(fd);
}

void	build_3d_pt(t_env *e, t_point *p, t_point *dst)
{
	dst->x = e->x + (p->x * e->dx) + (p->z * e->z_dx);
	dst->y = (e->y + (p->y * e->dy) - (p->z * e->z_dy));
	dst->coul = p->coul;
}

void	draw_axis(t_env *e)
{
	t_point	o;
	t_point	x;
	t_point	y;
	t_point	z;

	set_point(&o, e->x, e->y, 1);
	o.coul = 0xffffff;
	set_point(&x, e->x + 100, e->y, 1);
	x.coul = 0xFF;
	set_point(&y, e->x, e->y + 100, 1);
	y.coul = 0xFF0000;
	set_point(&z, e->x + e->z_dx, e->y + e->z_dy, 1);
	z.coul = 0xFF00;
	draw_line(e, x, o, 0xff);
	draw_line(e, o, y, 0xff00);
	draw_line(e, o, z, 0xff0000);
}
