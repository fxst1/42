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

#include <explorer.h>

void	print_color_bis_bis(char **cl, int mode)
{
	if (S_IFLNK == (mode & S_IFMT))
	{
		ft_putansi_str(cl[2], 1);
		ft_putansi_str(cl[3], 1);
	}
	if (S_IFDIR == (mode & S_IFMT))
	{
		ft_putansi_str(cl[0], 1);
		ft_putansi_str(cl[1], 1);
	}
}

void	print_color_bis(char **cl, int mode)
{
	if ((S_IFMT & mode) == S_IFCHR)
	{
		ft_putansi_str(cl[12], 1);
		ft_putansi_str(cl[13], 1);
	}
	if (mode & S_ISUID && ((S_IXGRP & mode) || (S_IXUSR & mode)))
	{
		ft_putansi_str(cl[14], 1);
		ft_putansi_str(cl[15], 1);
	}
	if (S_ISGID & mode && ((S_IXGRP & mode) || (S_IXUSR & mode)))
	{
		ft_putansi_str(cl[16], 1);
		ft_putansi_str(cl[17], 1);
	}
	if (S_IFDIR == (mode & S_IFMT) && (mode & S_IWOTH) && (mode & S_ISVTX))
	{
		ft_putansi_str(cl[18], 1);
		ft_putansi_str(cl[19], 1);
	}
	if (S_IFDIR == (mode & S_IFMT) && (mode & S_IWOTH) && !(mode & S_ISVTX))
	{
		ft_putansi_str(cl[20], 1);
		ft_putansi_str(cl[21], 1);
	}
}

void	print_color(char **cl, int mode)
{
	if (S_IFSOCK == (mode & S_IFMT))
	{
		ft_putansi_str(cl[4], 1);
		ft_putansi_str(cl[5], 1);
	}
	if (S_IFIFO == (mode & S_IFMT))
	{
		ft_putansi_str(cl[6], 1);
		ft_putansi_str(cl[7], 1);
	}
	if ((S_IFDIR != (mode & S_IFMT)) && (S_IXUSR & mode))
	{
		ft_putansi_str(cl[8], 1);
		ft_putansi_str(cl[9], 1);
	}
	if (S_IFBLK == (mode & S_IFMT))
	{
		ft_putansi_str(cl[10], 1);
		ft_putansi_str(cl[11], 1);
	}
	print_color_bis(cl, mode);
	print_color_bis_bis(cl, mode);
}

void	print_type(mode_t mode)
{
	if (S_IFLNK == mode)
		write(1, "l", 1);
	else if (S_IFDIR == mode)
		write(1, "d", 1);
	else if (S_IFIFO == mode)
		write(1, "p", 1);
	else if (S_IFBLK == mode)
		write(1, "b", 1);
	else if (S_IFSOCK == mode)
		write(1, "s", 1);
	else if (S_IFCHR == mode)
		write(1, "c", 1);
	else
		write(1, "-", 1);
}

void	print_spec(mode_t mode)
{
	if (mode & S_ISVTX && !(mode & S_IXOTH))
		write(1, "T", 1);
	else if (mode & S_ISVTX && (mode & S_IXOTH))
		write(1, "t", 1);
	else if (mode & 1 & 0x7)
		write(1, "x", 1);
	else
		write(1, "-", 1);
}
