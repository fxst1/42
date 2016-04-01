/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gcprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 21:23:14 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/01 21:23:16 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

static void		print_process(t_mem *lst)
{
	int		index;

	index = 0;
	while (lst)
	{
		index = lst->index;
		while (lst && index == lst->index)
		{
			printf((char*)CATEGORIES_FORMAT_GC, lst->index, lst,
				(void*)lst->pointer, (void*)lst->pointer + lst->size,
				lst->size, lst->mask);
			ft_print_memory((void*)lst->pointer, lst->size);
			lst = lst->next;
		}
		printf("\n");
	}
	printf(STR2_GC);
}

void			ft_gcprint(void)
{
	t_mem	**gc;

	gc = ft_gc();
	if (*gc)
	{
		printf(STR1_GC, gc);
		printf(CATEGORIES_PRINT_GC);
		print_process(*gc);
	}
	else
		printf("\033[1;38;5;1mCannot map memory ft_gc :\033[0m %p", gc);
	printf("\n");
}
