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
	ft_printf("%c%c%c", perm & 4 ? 'r' : '-',
						perm & 2 ? 'w' : '-',
						perm & 1 ? 'x' : '-');
}

void	print_stat_bis(char *path, t_args *a, t_file *f)
{
	char	*tmp;
	char	buf[1024];
	int		i;
	char	*ret;

	i = 0;
	ft_printf("%lu", f->dat.st_size);
	print_time(f->dat.st_mtime);
	if (a->colormap)
	{
		ret = ft_strrchr(f->name, '.');
		if (!ret)
			ret = f->name;
		print_color(ft_mapget(a->colormap, ret,
			&ft_strcmp),
			f->dat.st_mode);
	}
	if ((f->dat.st_mode & S_IFMT) == S_IFLNK)
	{
		tmp = ft_strdup(path);
		ft_strcat(tmp, PATH_SEPARATOR);
		ft_strcat(tmp, f->name);
		readlink(tmp, buf, sizeof(char) * 1024);
		while (ft_isprint(buf[i]))
			i++;
		buf[i] = 0;
		ft_printf("%s -> %s%s\n", f->name, buf, (a->colormap) ? RESET : "");
		free(tmp);
	}
	else
		ft_printf("%s%s\n", f->name, (a->colormap) ? RESET : "");
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
	ft_printf("%d", f->dat.st_nlink);
	offset = a->offset[1] - ft_strlen(getpwuid(f->dat.st_uid)->pw_name);
	ft_printf(" %s", getpwuid(f->dat.st_uid)->pw_name);
	print_offset(offset, ' ');
	ft_printf(" %s", getgrgid(f->dat.st_gid)->gr_name);
	offset = a->offset[2] - ft_strlen(getgrgid(f->dat.st_gid)->gr_name);
	print_offset(offset + 1, ' ');
	tmp = ft_itoa_base(f->dat.st_size, BASE_DEC);
	offset = a->offset[3] - ft_strlen(tmp);
	free(tmp);
	print_offset(offset - 1, ' ');
	print_stat_bis(path, a, f);
}
