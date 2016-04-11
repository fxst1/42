#include "implemt.h"

static void			addfile(t_file **f, t_file *add)
{
	t_file	*tmp;
	t_file	*last;
	char	*name;

	tmp = *f;
	last = NULL;
	if (tmp && (name = add->name))
	{
		while (tmp && ft_strcmp(tmp->name, name) > 0)
		{
			last = tmp;
			tmp = tmp->next;
		}
		add->next = tmp;
		if (last)
			last->next = add;
		else
			*f = add;
	}
	else
		*f = add;
}

static t_file		*init_file(char *path, char *name)
{
	t_file	*file;
	char	*tmp;

	tmp = ft_setfilename(path, name, 0);
	if ((file = (t_file*)malloc(sizeof(t_file))))
	{
		file->next = NULL;
		lstat(tmp, &file->s);
		file->name = tmp;
	}
	return (file);
}

static void			error(char *name)
{
	write(2, name, ft_strlen(name));
	write(2, " : ", 3);
	ft_putendl_fd(strerror(errno), 2);
}

t_file				*ft_open(char *dn)
{
	DIR		*d;
	t_dir	*e;
	t_file	*file;

	file = NULL;
	if ((d = opendir(dn)))
	{
		while ((e = readdir(d)))
			addfile(&file, init_file(dn, e->d_name));
		closedir(d);
	}
	else if (errno != ENOTDIR)
		error(dn);
	return (file);
}