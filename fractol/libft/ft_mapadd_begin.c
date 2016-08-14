/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapadd_begin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:02:40 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 04:02:43 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	ft_mapadd_begin(t_map **root, t_map *new)
{
	if (*root)
	{
		new->next = *root;
		new->next->last = new;
	}
	*root = new;
}
