#include <ls.h>

char	*set_name_path(char *dst, char *path, char *dirname)
{
	ft_strcpy(dst, path);
	ft_strcat(dst, dirname);
	ft_strcat(dst, PATH_SEPARATOR);
	return (dst);
}



void	build_offset(t_args *arg, t_file *f)
{
	int		offset;
	char	*str;

	arg->offset[0] = 0;
	arg->offset[1] = 0;
	arg->offset[2] = 0;
	arg->offset[3] = 0;
	while (f)
	{
		str = ft_itoa_base(1, BASE_DEC);
		offset = ft_strlen(str);
		if (arg->offset[0] < offset)
			arg->offset[0] = offset;
		free(str);

		offset = ft_strlen(getpwuid(f->dat.st_uid)->pw_name);
		if (arg->offset[1] < offset)
			arg->offset[1] = offset;
		
		offset = ft_strlen(getgrgid(f->dat.st_gid)->gr_name);
		if (arg->offset[2] < offset)
			arg->offset[2] = offset;
		
		str = ft_itoa_base(f->dat.st_size, BASE_DEC);
		offset = ft_strlen(str);
		if (arg->offset[3] < offset)
			arg->offset[3] = offset;
		free(str);
		f = f->next;
	}
}


int			compt_blocks(t_args *a, t_file *f)
{
	int	n;

	n = 0;
	while (f)
	{
		if (a->mask & ALL || (!(a->mask & ALL) && f->name[0] != '.'))
			n += f->dat.st_blocks;
		f = f->next;
	}
	return (n);
}

void		parcours(t_args *a, t_file *f)
{
	int	wrote;

	wrote = 0;
	build_offset(a, f);
	if (a->mask & LIST && f)
		ft_printf("total %d\n", compt_blocks(a, f) / 2);
	while (f)
	{
		if ((!(a->mask & ALL) && (f->name[0] != '.')) || (a->mask & ALL))
		{
			if (a->mask & LIST)
				print_stat(a, f);
			else
			{
				if (a->colormap)
				{
					print_color(ft_mapget(a->colormap, ft_strrchr(f->name, '.'), &ft_strcmp),
					f->dat.st_mode);
					ft_printf("%s"RESET, f->name);
				}
				else
					ft_printf("%s", f->name);
			}
			wrote = 1;
			if (wrote && f->next && !(a->mask & LIST))
				ft_printf("  ");
		}
		f = f->next;
	}
}

void		parcours_recur(char *path, t_args *a, t_file *f)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = 0;
	parcours(a, f);
	while (f)
	{
		if (S_IFMT & S_IFDIR & f->dat.st_mode
			&& ft_strcmp(f->name, "..") && ft_strcmp(f->name, "."))
		{
			len = ft_strlen(path) + ft_strlen(f->name) +
				PATH_SEPARATOR_LEN;
			tmp = ft_strnew(len);
			set_name_path(tmp, path, f->name);
			tmp[len - PATH_SEPARATOR_LEN] = 0;
			ft_printf("\n%s:\n",tmp);
			ft_strcpy(tmp + len - PATH_SEPARATOR_LEN, PATH_SEPARATOR);
			parcours_recur(tmp, a, f->dir);
			free(tmp);
		}
		f = f->next;
	}
}
