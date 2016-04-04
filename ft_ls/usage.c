/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 20:04:00 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/24 20:04:02 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	usage_bis(void)
{
	ft_putstr_fd("h=4;35\n\t* If LS_COLORS contains type's colors set,", 1);
	ft_putstr_fd("\n\t  it will ignored (for compatibility with MacOS / ", 1);
	ft_putstr_fd("Linux)\n  -e (--error): stop if any error occured while ", 1);
	ft_putstr_fd("execution\n  -h (--help): print this help\n", 1);
	ft_putstr_fd("\n\033[38;5;131m    <=---------------=   r e t u r n   ", 1);
	ft_putstr_fd("=---------------=>\033[0m\n\n", 1);
	ft_putstr_fd("  0: Success\n", 1);
	ft_putstr_fd("  1: Path error, but continue execution if necessairy", 1);
	ft_putstr_fd("\n\t(stop with -e / --error)\n", 1);
	ft_putstr_fd("  2: Command error, stop execution\n", 1);
	ft_putstr_fd("\n\033[38;5;38m<==================================", 1);
	ft_putstr_fd("===========================>\033[0m\n", 1);
}

void		usage(void)
{
	ft_putstr_fd("\033[38;5;38m<=========================== ft_ls ", 1);
	ft_putstr_fd("===========================>\033[0m\n", 1);
	ft_putstr_fd("\n\033[38;5;131m    <=---------------= c o m m a n d s", 1);
	ft_putstr_fd(" =---------------=>\033[0m\n", 1);
	ft_putstr_fd("\n  -R<deep> : recursif search, deep correspond\n", 1);
	ft_putstr_fd("\tto the number of subfolders'deep (not neccesairy)\n", 1);
	ft_putstr_fd("  -l : details\n", 1);
	ft_putstr_fd("  -S : sort by size (INCOMPATIBLE WITH -t)\n", 1);
	ft_putstr_fd("  -t : sort by modification time (newest first)\n", 1);
	ft_putstr_fd("  -r : reverse output\n", 1);
	ft_putstr_fd("  -G : use colors", 1);
	ft_putstr_fd("\n\t* If CLICOLOR is set at 1, this option is active", 1);
	ft_putstr_fd(" by default\n\t* Colors values should ", 1);
	ft_putstr_fd("be stock under LSCOLORS (see man ls)", 1);
	ft_putstr_fd("\n\t  default values are: ", 1);
	ft_putstr_fd(C_DEF, 1);
	ft_putstr_fd("\n\t* LS_COLORS or (--color=<filename>) should contains", 1);
	ft_putstr_fd("\n\t  extension and color sets, by exemple: .c=1;31:.", 1);
	usage_bis();
}

void		print_help(char *prgm)
{
	ft_putstr_fd("Try '", 2);
	ft_putstr_fd(prgm, 2);
	ft_putstr_fd(" -h' option for more information.\n", 2);
}
