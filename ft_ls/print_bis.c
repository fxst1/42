/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 02:56:14 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 02:56:17 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	print_color(char *ext, int mode)
{
	ft_putstr("\x1B[");
	if (ext)
		ft_putstr(ext);
	else
	{
		if (S_IFLNK == (mode & S_IFMT))
		{
			ft_putstr(INCR_BOLD);
			ft_putstr(LINK);
		}
		else if (S_IFDIR == (S_IFMT & mode))
		{
			ft_putstr(INCR_BOLD);
			ft_putstr(DIRECTORY);
		}
		else if (S_IXUSR & mode)
		{
			ft_putstr(INCR_BOLD);
			ft_putstr(EXEC);
		}
	}
	ft_putstr("m");
}

void	print_type(mode_t mode)
{
	if (S_IFLNK == mode)
		ft_putchar('l');
	else if (S_IFDIR == mode)
		ft_putchar('d');
	else if (S_IFIFO == mode)
		ft_putchar('p');
	else if (S_IFBLK == mode)
		ft_putchar('b');
	else if (S_IFSOCK == mode)
		ft_putchar('s');
	else if (S_IFCHR == mode)
		ft_putchar('c');
	else
		ft_putchar('-');
}

void	print_spec(mode_t mode)
{
	ft_putchar(0x7 & mode & 4 ? 'r' : '-');
	ft_putchar(0x7 & mode & 2 ? 'w' : '-');
	if (((mode & S_ISUID) && !(mode & S_IXUSR)) ||
		((mode & S_ISGID) && !(mode & S_IXGRP)))
		ft_putchar('S');
	else if (((mode & S_ISUID) && (mode & S_IXUSR)) ||
		((mode & S_ISGID) && (mode & S_IXGRP)))
		ft_putchar('s');
	else if (mode & S_ISVTX && !(mode & S_IXOTH))
		ft_putchar('T');
	else if (mode & S_ISVTX && (mode & S_IXOTH))
		ft_putchar('t');
	else if (mode & 1 & 0x7)
		ft_putchar('x');
	else
		ft_putchar('-');
}

void	print_time(time_t time)
{
	char	*str;

	str = ctime(&time);
	str[16] = 0;
	str += 4;
	ft_putchar(' ');
	ft_putstr(str);
	ft_putchar(' ');
}
