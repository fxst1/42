/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 20:03:52 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/24 20:03:54 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	first_of_all(t_args *arg, int n)
{
	arg->typemap = NULL;
	arg->colormap = NULL;
	arg->ret = 0;
	arg->deep = 0;
	arg->mask = REVERSE;
	arg->path = malloc(sizeof(char*) * (n));
	arg->cmp = &addfile;
	arg->prt = &parcours_simple;
	ft_memset(arg->path, 0, sizeof(char*) * (n));
	ft_memset(arg->offset, 0, sizeof(int) * 6);
}

void	file_errors_bis(t_args *a, int n, char **paths)
{
	DIR		*d;
	t_file	*t;
	t_file	*f;

	f = NULL;
	while (n > 0)
	{
		while (!*paths)
			paths++;
		d = opendir(*paths);
		if (errno == ENOTDIR)
		{
			t = init_file(a, "\0", *paths);
			if (!((t->p.mode & S_IFMT) == S_IFDIR))
				(a->cmp)(&f, t, a->mask & REVERSE);
		}
		if (d)
			closedir(d);
		paths++;
		n--;
	}
	a->prt(a, f);
	del(&f);
}

void	file_errors(t_args *a, char **paths)
{
	DIR		*d;
	int		n;

	n = 0;
	set_fct_cmp(a);
	while (paths[n])
	{
		d = opendir(paths[n]);
		if (!d && errno != ENOTDIR)
		{
			ft_putstr_fd("ft_ls: ", 2);
			ft_putstr_fd(paths[n], 2);
			ft_putstr_fd(" : ", 2);
			ft_putendl_fd(strerror(errno), 2);
			free(paths[n]);
			paths[n] = ft_strnew(1);
			a->ret = 1;
		}
		else if (d)
			closedir(d);
		n++;
	}
	file_errors_bis(a, n, paths);
	a->mask &= ~PRINT_TOTAL;
}
