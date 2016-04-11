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

int				ls(t_args *arg)
{
	int		n;
	t_file	*root;
	char	*path;

	n = 0;
	ft_strsort(arg->path, 0);
	while (arg->path[n])
	{
		if (*arg->path[n])
		{
			path = set_filename("\0", arg->path[n], 1);
			root = ft_open(arg, path, arg->cmp);
			arg->mask |= PRINT_TOTAL;
			if (root && arg->mask & RECURSIF)
				ls_run(path, arg, root, arg->deep);
			else if (root)
			{
				arg->prt(arg, root);
				del(&root);
			}
			free(path);
		}
		n++;
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

char			*ft_getenv(char **env, char *name)
{
	int	size;

	size = ft_strlen(name);
	while (*env && ft_strncmp(name, *env, size))
		env++;
	return (*env);
}
