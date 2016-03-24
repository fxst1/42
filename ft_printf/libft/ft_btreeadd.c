/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreeadd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:53:55 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:53:57 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	ft_btreeadd(unsigned int index, t_btree **root, t_btree *new)
{
	if (*root && index)
	{
		if (index % 2)
			ft_btreeadd(index / 2, &(*root)->left, new);
		else
			ft_btreeadd(index / 2, &(*root)->right, new);
	}
	else
		(*root) = new;
}
