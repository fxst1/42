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

static void		print_mask(int mask)
{
	if (mask & IS_DUMP)
		printf(MASK_COLOR_GC"Dump\033[0m ");
	else
		printf(MASK_COLOR_GC"Reference\033[0m ");		
	printf("\n");
}

static void		print_process(t_mem *lst)
{
	int		index;
	void	*addr;
	int		len;
	int		mask;

	index = 0;
	while (lst)
	{
		index = lst->index;
		len = 0;
		addr = (void*)lst->pointer;
		mask = lst->mask;
		printf((char*)CATEGORIES_FORMAT1_GC, lst->index, lst, (void*)lst->pointer);			
		while (lst && index == lst->index)
		{
			len += lst->size;
			lst = lst->next;
		}
		printf(CATEGORIES_FORMAT2_GC, addr + len, len);
		print_mask(mask);
		ft_print_memory(addr, len);
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
		printf("\033[1;48;5;1mCannot map memory ft_gc :\033[0m %p", gc);
	printf("\n");
}
