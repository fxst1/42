/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gcnew.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 21:23:01 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/01 21:23:03 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

t_mem	*ft_gcnew(void *addr, int len, int index, int mask)
{
	t_mem		*root;
	t_mem		*new;

	root = NULL;
	while (len > 0)
	{
		new = (t_mem*)malloc(sizeof(t_mem));
		new->index = index;
		new->mask = mask;
		new->size = (len >= (int)sizeof(t_mem)) ?
					(int)sizeof(t_mem) - 1 : len;
		new->pointer = (long int)addr;
		new->next = NULL;
		ft_gcadd(&root, new);
		len -= new->size;
		addr += new->size;
	}
	return (root);
}
