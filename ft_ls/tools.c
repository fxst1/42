/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 01:52:53 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 01:53:05 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char		*set_name_path(char *dst, char *path, char *dirname)
{
	ft_strcpy(dst, path);
	ft_strcat(dst, dirname);
	ft_strcat(dst, PATH_SEPARATOR);
	return (dst);
}

void		build_offset(t_args *arg, t_file *f)
{
	int		offset;
	char	*str;

	ft_memset(arg->offset, 0, sizeof(int) * 4);
	while (f)
	{
		str = ft_itoa_base(f->dat.st_nlink, BASE_DEC);
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

void		parcours(char *path, t_args *a, t_file *f)
{
	if (a->mask & LIST && f)
	{
		build_offset(a, f);
		ft_printf("total %d\n", compt_blocks(a, f));
	}
	while (f)
	{
		if (a->mask & LIST)
			print_stat(path, a, f);
		else
		{
			if (a->colormap)
			{
				print_color(ft_mapget(a->colormap, ft_strrchr(f->name, '.'),
					&ft_strcmp),
				f->dat.st_mode);
				ft_printf("%s%s", f->name, RESET);
			}
			else
				ft_printf("%s", f->name);
		}
		if (f->next && !(a->mask & LIST))
			ft_printf("  ");
		f = f->next;
	}
}

void		parcours_recur(char *path, t_args *a, t_file *f)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = 0;
	parcours(path, a, f);
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
			ft_printf("\n\n%s:\n", tmp);
			ft_strcpy(tmp + len - PATH_SEPARATOR_LEN, PATH_SEPARATOR);
			parcours_recur(tmp, a, f->dir);
			free(tmp);
		}
		f = f->next;
	}
}
