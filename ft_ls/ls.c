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

int				build_lsstr(char *path, char *arg)
{
	int	len;

	if (ft_strcmp(arg, "/"))
		ft_strcat(arg, PATH_SEPARATOR);
	ft_strcpy(path, arg);
	len = ft_strlen(path - PATH_SEPARATOR_LEN);
	return (len);
}

void			ls_run(char *path, int *t, t_args *arg, t_file *root)
{
	sort_files(arg, root);
	sort_filesalph(arg, root);
	arg->set |= PRINT_TOTAL;
	if (arg->mask & RECURSIF || t[1] > 1)
	{
		arg->path[t[0]][ft_strlen(arg->path[t[0]]) - PATH_SEPARATOR_LEN] =
			0;
		ft_strcat(arg->path[t[0]], PATH_SEPARATOR);
	}
	if (arg->mask & RECURSIF)
		parcours_recur(path, arg, root);
	else
		parcours(path, arg, root);
}

int				test(char **path, int size, t_args *a)
{
	int		n;
	int		i;

	n = 0;
	i = 0;
	while (n < size && i < 2)
	{
		if (path[n])
			i++;
		n++;
	}
	if (i == 2)
		a->set |= PRINT_PATH;
	return (i);
}

static void		ls_loop(char *path, t_file *root, t_args *arg, int size)
{
	int		n;
	int		t[2];
	int		i;

	i = test(arg->path, size, arg);
	n = 0;
	t[1] = size;
	while (n < size)
	{
		if (arg->path[n])
		{
			t[0] = n;
			if (arg->set & PRINT_PATH)
			{
				i = build_lsstr(path, arg->path[n]);
				if (arg->set & PRINT_LINE)
					ft_putstr("\n");
				arg->path[n][i + 1] = 0;
				ft_putstr(arg->path[n]);
				ft_putstr(":\n");
				arg->set |= PRINT_LINE;
			}
			if ((root = ft_open(arg, path, arg->path[n], arg->deep)))
			{
				ls_run(path, t, arg, root);
				del(root);
			}
			if (!(arg->mask & LIST) && arg->ret != 1)
				ft_putstr("\n");
			free(arg->path[n]);
		}
		n++;
	}
}

int				ls(t_args *arg, int size)
{
	char	path[256];
	t_file	*root;

	ft_memset(path, 0, sizeof(char) * 255);
	root = NULL;
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
