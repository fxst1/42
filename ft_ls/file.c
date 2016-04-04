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

t_file		*init_file(char *path, char *name)
{
	t_file	*file;
	char	*tmp;

	tmp = NULL;
	file = NULL;
	tmp = set_filename(path, name, 0);
	if ((file = (t_file*)malloc(sizeof(t_file))))
	{
		file->name = ft_strdup(name);
		file->next = NULL;
		lstat(tmp, &file->dat);
	}
	else
		file = NULL;
	free(tmp);
	return (file);
}

void		del(t_file **f)
{
	t_file	*tmp;
	t_file	*l;

	tmp = NULL;
	l = *f;
	while (l)
	{
		free(l->name);
		tmp = l->next;
		free(l);
		l = NULL;
		l = tmp;
	}
	*f = NULL;
}

void		addfile(t_file **f, t_file *add)
{
	t_file *tmp;

	tmp = *f;
	if (*f)
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = add;
	}
	else
		*f = add;
}

void		ls_run(char *path, t_args *arg, t_file *f, int deep)
{
	t_file	*new;
	char	*str;

	new = NULL;
	arg->set |= PRINT_LINE;
	build_offset(arg, f);
	sort_files(arg, f);
	sort_filesalph(arg, f);
	parcours(path, arg, f);
	while (f && arg->mask & RECURSIF && deep != 0)
	{
		if ((f->dat.st_mode & S_IFDIR) &&
			ft_strcmp(".", f->name) && ft_strcmp("..", f->name))
		{
			str = set_filename(path, f->name, 1);
			if ((new = ft_open(arg, str)))
			{
				ls_run(str, arg, new, deep - 1);
				del(&new);
			}
			free(str);
		}
		f = f->next;
	}
}

void		ft_error(t_args *arg, char *name)
{
	write(2, "ft_ls: ", 7);
	write(2, name, ft_strlen(name));
	write(2, " : ", 3);
	ft_putendl_fd(strerror(errno), 2);
	arg->ret = 2;
}

t_file		*ft_open(t_args *arg, char *dirname)
{
	DIR		*d;
	t_dir	*e;
	t_file	*file;

	file = NULL;
	if ((d = opendir(dirname)))
	{
		if (arg->set & PRINT_LINE)
			write(1, "\n", 1);
		write(1, dirname, ft_strlen(dirname));
		write(1, ":\n", 2);
		while ((e = readdir(d)))
		{
			if ((!(arg->mask & ALL) && (e->d_name[0] != '.')) ||
				((arg->mask & ALL)))
				addfile(&file, init_file(dirname, e->d_name));
			else if (errno != 0)
				ft_error(arg, e->d_name);
		}
		closedir(d);
	}
	else if (errno != ENOTDIR && errno != 0)
		ft_error(arg, dirname);
	return (file);
}
