/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gcdym.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 21:22:51 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/01 21:22:54 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

/*
**	ft_dym_gc
**
**	Add a new dynamic entry to GC.
**		change return pointer value will be directly effective
**
**	addr:	pointer to clone
**	len	:	addr's alloc size
**
*/

void	*ft_gcdym(void *addr, size_t len, int mask)
{
	t_mem	*new;
	t_mem	**gc;
	void	*pointer;

	if (len > 0)
	{
		gc = ft_gc();
		pointer = malloc(sizeof(len));
		ft_memcpy(pointer, addr, len);
		if (!*gc)
			new = ft_gcnew(pointer, len, 0, IS_DUMP | mask);
		else
			new = ft_gcnew(pointer, len, (*gc)->index + 1, IS_DUMP | mask);
		if (*gc)
			new->next = *gc;
		*gc = new;
		return (pointer);
	}
	else
		return (NULL);
}
