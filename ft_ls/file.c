#include <ls.h>

t_file	*init_file(char *path, char *name)
{
	t_file	*file;
	char	tmp[1024] = {0};

	ft_memset(tmp, 0, sizeof(char) * 1024);
	ft_strcpy(tmp, path);
	ft_strcat(tmp, name);
	if ((file = (t_file*)malloc(sizeof(t_file))))
	{
		file->name = ft_strnew(ft_strlen(name) + 2);
		file->name = ft_strcpy(file->name, name);
		file->dir = NULL;
		file->next = NULL;
		file->type = 0;
		stat(tmp, &file->dat);
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

void	sort_files(t_args *a, t_file *root)
{
	t_file	*swap;
	t_file	*tmp;
	t_file	*d;

	while (root)
	{
		tmp = root;
		while (tmp)
		{
			swap = root;
			if	(
				(
				(
				((a->sort & SIZE) && ((!(a->mask & REVERSE) && swap->dat.st_size < tmp->dat.st_size) ||
				(a->mask & REVERSE && swap->dat.st_size > tmp->dat.st_size))))
				||
				((a->sort & MTIME) && ((!(a->mask & REVERSE) && swap->dat.st_mtime < tmp->dat.st_mtime) ||
				(a->mask & REVERSE && swap->dat.st_mtime > tmp->dat.st_mtime))
				)
				)
				)
			{
				ft_swapn(&swap->dat, &tmp->dat, sizeof(struct stat));
				ft_swap(&swap->name, &tmp->name);
				ft_swap(&swap->type, &tmp->type);
				d = tmp->dir;
				tmp->dir = swap->dir;
				swap->dir = d;
			}
			sort_files(a, tmp->dir);
			tmp = tmp->next;
		}
		root = root->next;
	}
}

void	sort_filesalph(t_args *a, t_file *root)
{
	t_file	*swap;
	t_file	*tmp;
	t_file	*d;

	while (root)
	{
		tmp = root;
		while (tmp)
		{
			swap = root;
			if	(((!a->sort) || ((a->sort & SIZE) && (swap->dat.st_size == tmp->dat.st_size)) ||
				((a->sort & MTIME) && (swap->dat.st_mtime == tmp->dat.st_mtime))) &&
				((!(a->mask & REVERSE) && ft_strcasecmp(swap->name[0] == '.' ? swap->name + 1 : swap->name, 
				tmp->name[0] == '.' ? tmp->name + 1 : tmp->name) > 0) ||
				(a->mask & REVERSE && ft_strcasecmp(swap->name[0] == '.' ? swap->name + 1 : swap->name, 
				tmp->name[0] == '.' ? tmp->name + 1 : tmp->name) < 0))
				)
			{
				ft_swapn(&swap->dat, &tmp->dat, sizeof(struct stat));
				ft_swap(&swap->name, &tmp->name);
				ft_swap(&swap->type, &tmp->type);
				d = tmp->dir;
				tmp->dir = swap->dir;
				swap->dir = d;
			}
			sort_files(a, tmp->dir);
			tmp = tmp->next;
		}
		root = root->next;
	}
}


t_file	*ft_open(t_args *a, char *path, char *name, int deep)
{
	t_dir	*entry;
	t_file	*file;
	t_file	*ret;
	DIR		*d;
	char	*tmp = NULL;

	d = opendir(name);
	ret = NULL;
	file = NULL;
	if (d)
	{
		while ((entry = readdir(d)))
		{
			if ((!(a->mask & ALL) && (entry->d_name[0] != '.')) ||
				(a->mask & ALL))
			{
				file = init_file(path, entry->d_name);
				if (entry->d_type & DT_DIR)
				{
					if (deep != 0 &&
						ft_strcmp(entry->d_name, "..") &&
						ft_strcmp(entry->d_name, "."))
					{
						tmp = ft_strnew(ft_strlen(path) + ft_strlen(file->name) +
							PATH_SEPARATOR_LEN);
						tmp = set_name_path(tmp, path, file->name);
						file->dir = ft_open(a, tmp, tmp, deep - 1);
						free(tmp);
					}
				}
				addfile(&ret, file);
			}
			file = NULL;
		}
		closedir(d);
	}
	else if (a->set & SHOW_ERR)
	{
		a->ret = 1;
		name[ft_strlen(name) - 1] = 0;
		ft_fprintf(2, "%s: cannot access %s: %s\n", a->prgm,
			name, strerror(errno));
		return (NULL);		
	}
	return (ret);
}