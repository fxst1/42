/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gcadd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 21:22:41 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/01 21:22:43 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void		ft_gcadd(t_mem **gc, t_mem *new)
{
	t_mem	*root;

	root = *gc;
	if (root)
	{
		while (root->next)
			root = root->next;
		root->next = new;
	}
	else
		*gc = new;
}
