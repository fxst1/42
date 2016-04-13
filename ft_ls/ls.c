/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 01:46:07 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/08 16:20:11 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void			print_maps(t_args *a, t_print *f)
{
	char	*ret;

	if (a->mask & COLOR)
		print_color(a->typemap, f->mode);
	if (a->colormap)
	{
		ret = ft_strrchr(f->name, '.');
		ret = ft_mapget(a->colormap, ret ? ret : f->name, &ft_strcmp);
		if (ret)
			ft_putansi_str(ret, 1);
	}
}

void			set_fct_cmp(t_args *arg)
{
	if (arg->mask & LIST)
		arg->prt = &parcours;
	else if (arg->mask & OUT_LINE)
		arg->prt = &parcours_basic;
	else
		arg->prt = &parcours_simple;
	if (arg->mask & SIZE)
		arg->cmp = &addfile_size;
	else if (arg->mask & MTIME || arg->mask & CTIME)
		arg->cmp = &addfile_time;
	else
		arg->cmp = &addfile;
	if (arg->mask & LIST && !(arg->mask & (CTIME | SIZE)))
		arg->mask |= MTIME;
}

void			ls_do(t_args *arg, char *path, int n, int m)
{
	t_file	*root;
	char	*reset_path;
	char	str[1024];

	reset_path = NULL;
	root = NULL;
	if ((m & LIST) && path[n - 1] != '/' &&
		(n = readlink(path, str, 1024)) > 0)
		root = init_file(arg, "\0", path);
	else
	{
		reset_path = set_filename("\0", path, 1);
		root = ft_open(arg, reset_path, arg->cmp);
		arg->mask |= PRINT_TOTAL;
	}
	if (root && (m & RECURSIF))
		ls_run(reset_path, arg, root, arg->deep);
	else if (root)
	{
		arg->prt(arg, root);
		del(&root);
	}
	free(reset_path);
}

int				ls(t_args *arg)
{
	char	**path;

	path = arg->path;
	ft_strsort(path, 0);
	while (*path)
	{
		if (**path)
			ls_do(arg, *path, ft_strlen(*path), arg->mask);
		path++;
	}
	return (0);
}

int				stop_ls(t_args *arg)
{
	int	n;

	n = 0;
	while (arg->path[n])
		free(arg->path[n++]);
	n = 0;
	if (arg->typemap)
		while (arg->typemap[n])
			free(arg->typemap[n++]);
	free(arg->typemap);
	if (arg->colormap)
		ft_mapdel(&arg->colormap, 1, &free, &free);
	return (arg->ret);
}
