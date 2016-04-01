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
**	Add a new entry to GC (only reference it) DEBUG ONLY or NO FREEABLE POINTER
**
*/

void	*ft_gcref(void *addr, size_t len, int mask)
{
	t_mem	*new;
	t_mem	**gc;

	if (len > 0)
	{
		gc = ft_gc();
		if (!*gc)
			new = ft_gcnew(addr, len, 0, mask & ~(IS_DUMP));
		else
			new = ft_gcnew(addr, len, (*gc)->index + 1, mask & ~(IS_DUMP));
		if (*gc)
			new->next = *gc;
		*gc = new;
		return (addr);
	}
	else
		return (NULL);
}
