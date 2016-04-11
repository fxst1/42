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

static void		save_color(int fd, char *str, int m)
{
	write(fd, ",0x", 3);
	write(fd, str, ft_strlen(str));
	if (m)
		write(fd, " ", 1);
}

void			save_fdf(t_point ***p, char *fname)
{
	int		fd;
	int		i;
	int		j;
	char	*str;

	i = 0;
	if ((fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0666)) > 0)
		while (p[i])
		{
			j = 0;
			while (p[i][j] && ((str = ft_itoa(p[i][j]->z))))
			{
				write(fd, str, ft_strlen(str));
				free(str);
				str = ft_itoa_base(p[i][j]->coul, BASE_HEX_MAJ);
				save_color(fd, str, !!p[i][++j]);
				free(str);
			}
			if (p[++i])
				write(fd, "\n", 1);
		}
	else
		ft_putstr_fd("Cannot save your fdf... try an other path\n", 2);
	close(fd);
}

void			build_3d_pt(t_env *e, t_point *p, t_point *dst)
{
	dst->x = e->x + (p->x * e->dx) + (p->z * e->z_dx) + (2 * p->y);
	dst->y = (e->y + (p->y * e->dy) - (p->z * e->z_dy));
	dst->coul = p->coul;
}
