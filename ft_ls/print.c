/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 02:48:39 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 02:48:42 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_offset(int offset, int c)
{
	char	str[offset + 1];
	int		index;

	index = 0;
	while (offset > index)
		str[index++] = c;
	write(1, str, offset);
}

void	print_perm(int perm)
{
	print_type(perm & S_IFMT);
	write(1, (perm & S_IRUSR) ? "r" : "-", 1);
	write(1, (perm & S_IWUSR) ? "w" : "-", 1);
	if (!(perm & S_IXUSR) && (perm & S_ISUID))
		write(1, "S", 1);
	else if ((perm & S_ISUID) && (perm & S_IXUSR))
		write(1, "s", 1);
	else
		write(1, (perm & S_IXUSR) ? "x" : "-", 1);
	write(1, (perm & S_IRGRP) ? "r" : "-", 1);
	write(1, (perm & S_IWGRP) ? "w" : "-", 1);
	if (!(perm & S_IXGRP) && (perm & S_ISGID))
		write(1, "S", 1);
	else if ((perm & S_ISUID) && (perm & S_IXGRP))
		write(1, "s", 1);
	else
		write(1, (perm & S_IXGRP) ? "x" : "-", 1);
	write(1, (perm & S_IROTH) ? "r" : "-", 1);
	write(1, (perm & S_IWOTH) ? "w" : "-", 1);
	print_spec(perm);
}

void	print_map(t_print *f, t_args *a)
{
	write(1, " ", 1);
	write(1, f->size, ft_strlen(f->size));
	print_time(&f->tim);
	if (a->mask & COLOR)
		print_color(a->typemap, f->mode);
	/*if (a->colormap)
	{
		ret = ft_strrchr(f->name, '.');
		print_color(a->typemap, NULL, ft_mapget(a->colormap, ret ? ret : f->name,
			&ft_strcmp),
			f->mode);
	}*/
}

void	print_stat_bis(int offset, char *path, t_args *a, t_print *f)
{
	char	buf[1024];
	char	tmp[1024];
	int		i;

	i = 0;
	print_offset(offset, ' ');
	print_map(f, a);
	if ((f->mode & S_IFMT) == S_IFLNK)
	{
		ft_strcpy(tmp, path);
		ft_strcat(tmp, PATH_SEPARATOR);
		ft_strcat(tmp, f->name);
		readlink(tmp, buf, sizeof(char) * 1024);
		while (ft_isprint(buf[i]))
			i++;
		buf[i] = 0;
		write(1, f->name, ft_strlen(f->name));
		write(1, "\e[m -> ", 7);
		write(1, buf, ft_strlen(buf));
	}
	else
		write(1, f->name, ft_strlen(f->name));
	write(1, "\e[m\n", 4);
}

void	print_stat(char *path, t_args *a, t_print *f)
{
	char	*tmp;
	int		offset;

	offset = 0;
	print_perm(f->mode);
	offset = a->offset[0] - ft_strlen(f->nlink);
	free(tmp);
	print_offset(offset + 1, ' ');
	ft_putnbr_fd(f->nlink, 1);
	offset = a->offset[1] - ft_strlen(f->usr);
	write(1, " ", 1);
	ft_putstr_fd(f->usr, 1);
	print_offset(offset, ' ');
	write(1, " ", 1);
	ft_putstr_fd(f->grp, 1);
	offset = a->offset[2] - ft_strlen(f->grp);
	print_offset(offset + 1, ' ');
	offset = a->offset[3] - ft_strlen(f->size);
	print_stat_bis(offset, path, a, f);
}
