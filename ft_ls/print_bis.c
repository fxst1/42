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
	if (ext)
		ft_printf("%a", ext);
	else
	{
		if (S_IFLNK == (mode & S_IFMT))
			ft_printf("%a%a", INCR_BOLD, LINK);
		else if (S_IFDIR == (S_IFMT & mode))
			ft_printf("%a%a", INCR_BOLD, DIRECTORY);
		else if (S_IXUSR & mode)
			ft_printf("%a%a", INCR_BOLD, EXEC);
	}
}

void	print_type(mode_t mode)
{
	if (S_IFLNK == mode)
		ft_printf("l");
	else if (S_IFDIR == mode)
		ft_printf("d");
	else if (S_IFIFO == mode)
		ft_printf("p");
	else if (S_IFBLK == mode)
		ft_printf("b");
	else if (S_IFSOCK == mode)
		ft_printf("s");
	else if (S_IFCHR == mode)
		ft_printf("c");
	else
		ft_printf("-");
}

void	print_spec(mode_t mode)
{
	ft_printf("%c%c", 0x7 & mode & 4 ? 'r' : '-',
					0x7 & mode & 2 ? 'w' : '-');
	if (((mode & S_ISUID) && !(mode & S_IXUSR)) ||
		((mode & S_ISGID) && !(mode & S_IXGRP)))
		ft_printf("S");
	else if (((mode & S_ISUID) && (mode & S_IXUSR)) ||
		((mode & S_ISGID) && (mode & S_IXGRP)))
		ft_printf("s");
	else if (mode & S_ISVTX && !(mode & S_IXOTH))
		ft_printf("T");
	else if (mode & S_ISVTX && (mode & S_IXOTH))
		ft_printf("t");
	else if (mode & 1 & 0x7)
		ft_printf("x");
	else
		ft_printf("-");
}

void	print_time(time_t time)
{
	char	*str;

	str = ctime(&time);
	str[16] = 0;
	str += 4;
	ft_printf(" %s ", str);
}
