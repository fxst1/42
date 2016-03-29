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

#include <ls.h>

void	print_offset(int offset, int c)
{
	while (offset-- >= 0)
		write(1, &c, 1);
}

void	print_perm(int perm)
{
	ft_putchar(perm & 4 ? 'r' : '-');
	ft_putchar(perm & 2 ? 'w' : '-');
}

void	print_map(t_args *a, t_file *f)
{
	char	*ret;

	if (a->colormap)
	{
		ret = ft_strrchr(f->name, '.');
		print_color(ft_mapget(a->colormap, ret ? ret : f->name,
			&ft_strcmp),
			f->dat.st_mode);
	}
}

void	print_stat_bis(char *path, t_args *a, t_file *f)
{
	char	*tmp;
	char	buf[1024];
	int		i;

	i = 0;
	ft_putnbr(f->dat.st_size);
	print_time(f->dat.st_mtime);
	print_map(a, f);
	if ((f->dat.st_mode & S_IFMT) == S_IFLNK)
	{
		tmp = ft_strdup(path);
		ft_strcat(tmp, PATH_SEPARATOR);
		ft_strcat(tmp, f->name);
		readlink(tmp, buf, sizeof(char) * 1024);
		while (ft_isprint(buf[i]))
			i++;
		buf[i] = 0;
		ft_putstr(f->name);
		ft_putstr(" -> ");
		ft_putstr(buf);
		ft_putstr((a->colormap) ? RESET : "");
		free(tmp);
	}
	else
	{
		ft_putstr(f->name);
		ft_putendl((a->colormap) ? RESET : "");
	}
}

void	print_stat(char *path, t_args *a, t_file *f)
{
	char	*tmp;
	int		offset;

	offset = 0;
	print_type(f->dat.st_mode & S_IFMT);
	print_perm((f->dat.st_mode >> 6) & 0x7);
	print_perm((f->dat.st_mode >> 3) & 0x7);
	print_spec(f->dat.st_mode);
	tmp = ft_itoa_base(f->dat.st_nlink, BASE_DEC);
	offset = a->offset[0] - ft_strlen(tmp);
	free(tmp);
	print_offset(offset + 1, ' ');
	ft_putnbr(f->dat.st_nlink);
	offset = a->offset[1] - ft_strlen(getpwuid(f->dat.st_uid)->pw_name);
	ft_putstr(" ");
	ft_putstr(getpwuid(f->dat.st_uid)->pw_name);
	print_offset(offset, ' ');
	ft_putstr(" ");
	ft_putstr(getgrgid(f->dat.st_gid)->gr_name);
	offset = a->offset[2] - ft_strlen(getgrgid(f->dat.st_gid)->gr_name);
	print_offset(offset + 1, ' ');
	tmp = ft_itoa_base(f->dat.st_size, BASE_DEC);
	offset = a->offset[3] - ft_strlen(tmp);
	free(tmp);
	print_offset(offset - 1, ' ');
	print_stat_bis(path, a, f);
}
