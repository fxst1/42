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

void		usage(void)
{
	ft_printf("%k<======================= ft_ls ", 38);
	ft_printf("=======================>%s\n", RESET);
	ft_printf("\n%k<=---------------= c o m m a n d s", 131);
	ft_printf(" =---------------=>%s\n", RESET);
	ft_printf("\n  -R<deep> : recursif search, deep correspond\n");
	ft_printf("\tto the number of subfolders'deep (not neccesairy)\n");
	ft_printf("  -l : details\n");
	ft_printf("  -A : not sort by alphanum\n");
	ft_printf("  -S : sort by size (INCOMPATIBLE WITH -t)\n");
	ft_printf("  -t : sort by modification time (newest first)\n");
	ft_printf("  -r : reverse output\n");
	ft_printf("  -G : use formated text; default configs\n\t");
	ft_printf("(--color=<filename> for user configs !! OVERWRITE -C !!)\n");
	ft_printf("  -e (--error): stop if any error occured\n");
	ft_printf("  -h (--help): print this help\n");
	ft_printf("\n%k<=---------------=   r e t u r n   ", 131);
	ft_printf("=---------------=>%s\n\n", RESET);
	ft_printf("  0: Success\n");
	ft_printf("  1: Path error, but continue execution if necessairy");
	ft_printf("\n\t(stop with -e / --error)\n");
	ft_printf("  2: Command error, stop execution\n");
	ft_printf("\n%k<==================================", 38);
	ft_printf("===================>%s\n", RESET);
}
