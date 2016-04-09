/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:04:20 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 04:04:22 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	*ft_mapget(t_map *root, void *key, int (*cmp)())
{
	t_map	*m;

	if (key && root)
	{
		m = root->last;
		while (root)
		{
			if (!(*cmp)(key, root->key))
				return (root->value);
			root = root->next;
		}
		while (m)
		{
			if (m->key && !(*cmp)(key, m->key))
				return (m->value);
			m = m->last;
		}
	}
	return (NULL);
}
