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

t_file		*init_file(t_args *a, char *path, char *name)
{
	t_file	*file;
	char	*tmp;
	acl_t	ac;
	int		i;

	tmp = set_filename(path, name, 0);
	i = 0;
	if ((file = (t_file*)malloc(sizeof(t_file))))
	{
		file->next = NULL;
		lstat(tmp, &file->s);
		init_print(name, &file->s, a->mask, &file->p);
		if ((ac = acl_get_file(tmp, ACL_TYPE_EXTENDED)))
		{
			file->p.acl = 1;
			acl_free((void *)ac);
		}
		if ((file->s.st_mode & S_IFMT) == S_IFLNK &&
			(i = readlink(tmp, file->p.lnk, sizeof(char) * 1024)))
			file->p.lnk[i] = 0;
		file->p.attr = listxattr(tmp, NULL, 0, i ?
			XATTR_SHOWCOMPRESSION | XATTR_NOFOLLOW : 0);
	}
	free(tmp);
	return (file);
}

void		del(t_file **f)
{
	t_file	*tmp;
	t_file	*l;
	t_print	*p;

	tmp = NULL;
	l = *f;
	while (l)
	{
		tmp = l->next;
		p = &l->p;
		free(p->name);
		delete_print(p);
		free(l);
		l = NULL;
		l = tmp;
	}
	*f = NULL;
}

void		ls_run(char *path, t_args *arg, t_file *f, int deep)
{
	t_file	*new;
	t_file	*root;
	char	*str;
	char	*name;
	void	*add;

	arg->prt(arg, f);
	add = arg->cmp;
	if (!deep && f)
		del(&f);
	while (f && deep != 0)
	{
		root = f->next;
		if ((name = f->p.name) && (f->p.mode & S_IFDIR) &&
			ft_strcmp(".", name) && ft_strcmp("..", name))
		{
			str = set_filename(path, name, 1);
			if ((new = ft_open(arg, str, add)))
				ls_run(str, arg, new, deep - 1);
			free(str);
		}
		free(name);
		free(f);
		f = root;
	}
}

void		ft_error(t_args *arg, char *name)
{
	write(2, "ft_ls: ", 7);
	write(2, name, ft_strlen(name));
	write(2, " : ", 3);
	ft_putendl_fd(strerror(errno), 2);
	arg->ret = 1;
}

t_file		*ft_open(t_args *a, char *dn, void (*add)())
{
	DIR		*d;
	t_dir	*e;
	t_file	*file;

	file = NULL;
	if ((d = opendir(dn)))
	{
		if (a->mask & PRINT_LINE)
			write(1, "\n", 1);
		else
			a->mask |= PRINT_LINE;
		write(1, dn, ft_strlen(dn) - 1);
		write(1, ":\n", 2);
		while ((e = readdir(d)))
		{
			if ((!(a->mask & ALL) && (e->d_name[0] != '.')) ||
				((a->mask & ALL)))
				(*add)(&file, init_file(a, dn, e->d_name), a->mask & REVERSE);
		}
		closedir(d);
	}
	else if (errno != ENOTDIR)
		ft_error(a, dn);
	return (file);
}
