/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 01:46:07 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 01:46:09 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void		ls_run(char *path, int *t, t_args *arg, t_file *root)
{
	sort_files(arg, root);
	sort_filesalph(arg, root);
	if (arg->mask & RECURSIF || t[1] > 1)
	{
		arg->path[t[0]][ft_strlen(arg->path[t[0]]) - PATH_SEPARATOR_LEN] =
		0;
		if (t[0] >= 1)
			ft_printf("\n");
		if (t[1] > 1)
			ft_printf("%s:\n", arg->path[t[0]]);
		ft_strcat(arg->path[t[0]], PATH_SEPARATOR);
	}
	if (arg->mask & RECURSIF)
		parcours_recur(path, arg, root);
	else
		parcours(path, arg, root);
}

static void		ls_loop(char *path, t_file *root, t_args *arg, int size)
{
	int		n;
	int		len;
	int		t[2];

	n = 0;
	len = 0;
	t[1] = size;
	while (n < size)
	{
		t[0] = n;
		len = ft_strlen(arg->path[n]);
		if (ft_strcmp(arg->path[n] + len - ft_strlen(PATH_SEPARATOR),
			PATH_SEPARATOR))
			ft_strcat(arg->path[n], PATH_SEPARATOR);
		ft_strcpy(path, arg->path[n]);
		root = ft_open(arg, path, arg->path[n], arg->deep);
		ls_run(path, t, arg, root);
		del(root);
		if (!(arg->mask & LIST) && arg->ret != 1)
			ft_printf("\n");
		free(arg->path[n]);
		n++;
	}
}

int				ls(t_args *arg, int size)
{
	char	path[256];
	t_file	*root;

	ft_memset(path, 0, sizeof(char) * 255);
	root = NULL;
	if (!arg->path[0])
	{
		arg->path[0] = ft_strnew(PATH_SEPARATOR_LEN + 1);
		arg->path[0][0] = '.';
		ft_strcat(arg->path[0] + 1, PATH_SEPARATOR);
		size++;
	}
	ls_loop(path, root, arg, size);
	return (0);
}

void			stop_ls(t_args *arg, int n)
{
	while (arg->path[n] && n > 0)
		free(arg->path[n--]);
	if (arg->colormap && (arg->set & INIT_COLOR))
		ft_mapdel(&arg->colormap, 1, &free, &free);
	else if (arg->colormap)
		ft_mapdel(&arg->colormap, 1, NULL, NULL);
}
