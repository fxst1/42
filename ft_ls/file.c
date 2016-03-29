/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 03:02:05 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 03:02:07 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

t_file	*init_file(char *path, char *name)
{
	t_file	*file;
	char	tmp[1024];

	ft_memset(tmp, 0, sizeof(char) * 1024);
	ft_strcat(tmp, path);
	ft_strcat(tmp, name);
	if ((file = (t_file*)malloc(sizeof(t_file))))
	{
		file->name = ft_strnew(ft_strlen(name) + 2);
		file->name = ft_strcpy(file->name, name);
		file->dir = NULL;
		file->next = NULL;
		file->type = 0;
		lstat(tmp, &file->dat);
	}
	else
		file = NULL;
	return (file);
}

void	del(t_file *f)
{
	t_file	*tmp;

	tmp = NULL;
	while (f)
	{
		del(f->dir);
		free(f->name);
		tmp = f->next;
		free(f);
		f = tmp;
	}
}

void	addfile(t_file **f, t_file *add)
{
	t_file *tmp;

	tmp = *f;
	if (*f)
	{
		while (tmp && tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = add;
	}
	else
		*f = add;
}

t_file	*open_dir(t_args *a, char *path, DIR *d, int deep)
{
	t_dir	*e;
	char	*tmp;
	t_file	*ret;
	t_file	*f;

	ret = NULL;
	while ((e = readdir(d)))
	{
		if ((!(a->mask & ALL) && (e->d_name[0] != '.')) || (a->mask & ALL))
		{
			if ((f = init_file(path, e->d_name)) && f->dat.st_mode & S_IFDIR)
			{
				if (deep && ft_strcmp(e->d_name, "..") &&
					ft_strcmp(e->d_name, "."))
				{
					tmp = set_str(tmp, path, f->name);
					f->dir = ft_open(a, tmp, tmp, deep - 1);
					free(tmp);
				}
			}
			addfile(&ret, f);
		}
	}
	return (ret);
}

t_file	*ft_open(t_args *a, char *path, char *name, int deep)
{
	DIR		*d;
	t_file	*files;

	files = NULL;
	printf("<%s><%s>\n", path, name);
	if ((d = opendir(!*name && !ft_strcmp(path, "/") : "/" : name)))
	{
		files = open_dir(a, path, d, deep);
		closedir(d);
	}
	else if (errno != ENOTDIR)
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(" : ", 2);
		ft_putendl_fd(strerror(errno), 2);
		if (a->set & SHOW_ERR)
			a->ret = 1;
	}
	return (a->ret == 1 ? NULL : files);
}
