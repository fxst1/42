/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gcstop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 21:23:39 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/01 21:23:41 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

static void		ft_freerec_gt(t_mem *gc)
{
	if (gc)
	{
		ft_freerec_gt(gc->next);
		gc->size = 0;
		gc->index = -1;
		gc->pointer = 0x0;
		if (gc->mask & IS_DUMP)
			free(gc);
		gc = NULL;
	}
}

/*
**	ft_freeall_gc
**
**	Clear gc
**
*/

void			ft_gcstop(void)
{
	t_mem	**gc;

	gc = ft_gc();
	ft_freerec_gt(*gc);
	*gc = NULL;
	gc = NULL;
}
