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

static char		*init_args(char **s, int *mask)
{
	char *fname;

	fname = NULL;
	while (*s)
	{
		if (**s == '-')
		{
			if (!ft_strcmp(*s, "--color=random"))
				*mask |= RANDOM;
			else if (!ft_strcmp(*s, "--color=depth"))
				*mask |= NORMAL;
			else if (!ft_strcmp(*s, "--color=graduate"))
				*mask |= GRADUATE;
		}
		else
			fname = ft_strdup(*s);
		s++;
	}
	return (fname);
}

static void		process(t_env *e, int const fd, char *fname, int mask)
{
	t_point	***fdf;

	fdf = init_fdf_points(fd);
	fdf = init_fdf(mask, open(fname, O_RDONLY), fdf);
	if (fdf && (new_env(e, 600, 800, fname)))
	{
		e->mask = mask;
		e->fdf = fdf;
		if (e->mask & GRADUATE)
			reset_color(e->fdf);
		set_scales(e, e->fdf);
		mlx_key_hook(e->screen, key_hook, e);
		mlx_mouse_hook(e->screen, mouse_hook, e);
		mlx_expose_hook(e->screen, expose_hook, e);
		mlx_loop(e->mlx);
	}
	else
		free_env(e);
	close(fd);
}

int				main(int argc, char **argv)
{
	int		fd;
	char	*fname;
	int		mask;
	t_env	e;

	fname = NULL;
	mask = 0;
	if (argc > 1)
	{
		ft_memset(&e, 0, sizeof(t_env));
		fname = init_args(argv + 1, &mask);
		if ((fd = open(fname, O_RDONLY)) > 0)
			process(&e, fd, fname, mask);
		else
			ft_putstr_fd("fdf: cannot open file\n", 2);
	}
	else
		ft_putstr_fd(USAGE, 2);
	return (0);
}
