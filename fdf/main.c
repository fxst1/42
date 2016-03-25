/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:36:44 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 04:36:48 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define PI 3.14159265359

char	*init_args(t_env *e, char **s, char *fname)
{
	s++;
	e->save = NULL;
	while (*s)
	{
		if (**s == '-')
		{
			if (!ft_strcmp(*s, "--color=random"))
				e->colorfdf |= RANDOM;
			else if (!ft_strcmp(*s, "--color=depth"))
				e->colorfdf |= NORMAL;
			else if (!ft_strcmp(*s, "--color=graduate"))
				e->colorfdf |= GRADUATE;
			else if (!ft_strncmp(*s, "--save=", 7))
				e->save = ft_strdup((*s) + 7);
			else if (!ft_strcmp(*s, "--axis"))
				e->mask |= DRAW_AXIS;
			else if (!ft_strcmp(*s, "--editor"))
				e->mask |= EDITOR;
		}
		else
			fname = ft_strdup(*s);
		s++;
	}
	return (fname);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*fname;
	t_env	*e;

	fname = NULL;
	if (argc > 1)
	{
		if ((e = new_env(600, 800)))
		{
			fname = init_args(e, argv, fname);
			if ((fd = open(fname, O_RDONLY)) >= 0)
			{
				e->fdf = init_fdf_points(fname);
				e->fdf = init_fdf(e, fd, e->fdf);
				if (e->colorfdf == GRADUATE)
					reset_color(e->fdf);
				set_scales(e, e->fdf);
				mlx_hook(e->screen, 3, 3, key_hook, e);
				mlx_expose_hook(e->screen, expose_hook, e);
				mlx_loop(e->mlx);
			}
			close(fd);
		}
	}
	return (0);
}
