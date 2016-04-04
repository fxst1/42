/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gcref.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 21:23:28 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/01 21:23:31 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

/*
**	ft_add_gc
**
**	Add a new entry to GC (only reference it)
**
*/

void	*ft_gcref(void *addr, size_t len, int mask)
{
	t_mem	*new;
	t_mem	**gc;
	t_mem	*next;

	if (len > 0)
	{
		gc = ft_gc();
		next = *gc;
		if (*gc)
		{
			while (next->next)
				next = next->next;
			new = ft_gcnew(addr, len, next->index + 1, mask & ~(1));
			next->next = new;
		}
		else
		{
			*gc = ft_gcnew(addr, len, 0, mask & ~(1));
			new = (*gc);
		}
		return (addr);
	}
	else
		return (NULL);
}
