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

#include "ls.h"

void	first_of_all(t_args *arg, int n)
{
	arg->set = SHOW_ERR;
	arg->ret = 0;
	arg->deep = 0;
	arg->mask = 0;
	arg->sort = 0;
	arg->path = malloc(sizeof(char*) * (n));
	ft_memset(arg->path, 0, sizeof(char*) * (n));
	arg->path[0] = ft_strdup(".");
}

void	file_errors_bis(int n, char **paths)
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
			t = init_file("", *paths);
			if (!((t->dat.st_mode & S_IFMT) == S_IFDIR))
				addfile(&f, t);
		}
		if (d)
			closedir(d);
		paths++;
		n--;
	}
}

void	file_errors(t_args *a, char **paths)
{
	DIR		*d;
	int		n;
	int		i;
	t_file	*f;

	i = 0;
	n = 0;
	f = NULL;
	while (paths[n])
	{
		d = opendir(paths[n]);
		if (!d && errno != ENOTDIR)
		{
			ft_fprintf(2, "ft_ls: %s: %s\n", paths[n], strerror(errno));
			paths[n] = NULL;
		}
		else if (d)
			closedir(d);
		n++;
	}
	file_errors_bis(n, paths);
	a->set &= ~PRINT_TOTAL;
	parcours("", a, f);
	del(f);
}

t_map	*init_extension_map_from_file(char *filename)
{
	int		fd;
	t_map	*m;
	char	*line;
	char	*key;
	int		index;

	m = NULL;
	index = 0;
	if ((fd = open(filename, O_RDONLY)) > 0)
	{
		while (get_next_line(fd, &line) > 0)
		{
			key = ft_strnew(32);
			index = 0;
			while (line[index] != ',')
			{
				key[index] = line[index];
				index++;
			}
			key[index] = 0;
			ft_mapadd_begin(&m, ft_mapnew(key, ft_strdup(line + index + 2)));
			free(line);
		}
	}
	return (m);
}

char	*set_str(char *tmp, char *s1, char *s2)
{
	tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + PSL);
	tmp = set_name_path(tmp, s1, s2);
	return (tmp);
}
