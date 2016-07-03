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

#include <explorer.h>

void	print_time(time_t *tim, int mask)
{
	char	*str;
	int		mon;
	time_t	now;

	time(&now);
	str = ctime(tim);
	mon = 30 * 24 * 60 * 60 * 6;
	if (mask & MTIME && now - mon > *tim)
	{
		str[24] = 0;
		str += 4;
		ft_strcpy(&str[6], &str[14]);
		str[6] = ' ';
	}
	else
	{
		str[16] = 0;
		str += 4;
	}
	write(1, " ", 1);
	write(1, str, ft_strlen(str));
	write(1, " ", 1);
}

void	print_perm(int perm)
{
	print_type(perm & S_IFMT);
	write(1, (perm & S_IRUSR) ? "r" : "-", 1);
	write(1, (perm & S_IWUSR) ? "w" : "-", 1);
	if ((perm & S_ISUID))
		write(1, (perm & S_IXUSR) ? "s" : "S", 1);
	else
		write(1, (perm & S_IXUSR) ? "x" : "-", 1);
	write(1, (perm & S_IRGRP) ? "r" : "-", 1);
	write(1, (perm & S_IWGRP) ? "w" : "-", 1);
	if ((perm & S_ISGID))
		write(1, (perm & S_IXGRP) ? "s" : "S", 1);
	else
		write(1, (perm & S_IXGRP) ? "x" : "-", 1);
	write(1, (perm & S_IROTH) ? "r" : "-", 1);
	write(1, (perm & S_IWOTH) ? "w" : "-", 1);
	print_spec(perm);
}

void	print_map(t_print *f, t_args *a)
{
	if (f->maj && f->min)
	{
		write(1, f->maj, f->len_ma);
		write(1, ",", 1);
		print_offset(a->offset[5] - f->len_mi + 1, ' ');
		write(1, f->min, f->len_mi);
	}
	else
		write(1, f->size, f->len_size);
	print_time(&f->tim, a->mask);
	print_maps(a, f);
}

void	print_stat_bis(int offset, t_args *a, t_print *f)
{
	char	*buf;

	buf = f->lnk;
	print_offset(offset, ' ');
	print_map(f, a);
	if ((f->mode & S_IFMT) == S_IFLNK)
	{
		write(1, f->name, f->len_name);
		write(1, "\033[m -> ", 7);
		write(1, buf, ft_strlen(buf));
	}
	else
		write(1, f->name, f->len_name);
	write(1, "\033[m\n", 4);
}

void	print_stat(t_args *a, t_print *f)
{
	print_perm(f->mode);
	if (f->attr > 0)
		write(1, "@", 1);
	else if (f->acl)
		write(1, "+", 1);
	else
		write(1, " ", 1);
	print_offset(a->offset[0] - f->len_nlink + 1, ' ');
	write(1, f->nlink, f->len_nlink);
	write(1, " ", 1);
	write(1, f->usr, f->len_usr);
	print_offset(a->offset[1] - f->len_usr + 1, ' ');
	write(1, " ", 1);
	write(1, f->grp, f->len_grp);
	print_offset(a->offset[2] - f->len_grp + 1, ' ');
	if (f->maj && f->min)
		print_stat_bis(a->offset[4] - f->len_ma, a, f);
	else
		print_stat_bis(a->offset[3] - f->len_size +
			a->offset[4] + a->offset[5] + 1, a, f);
}
