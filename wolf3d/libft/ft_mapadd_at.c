/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapadd_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 03:52:08 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 03:52:12 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	ft_mapadd_at(t_map **root, t_map *new, int index)
{
	t_map	*m;
	t_map	*i;

	if (!(m = *root))
		*root = new;
	else if (index < 0)
	{
		while (m->last && index++ != 0)
		{
			i = m;
			m = m->last;
		}
		m->last = new;
		new->next = i;
	}
	else
	{
		while (m->next && index-- != 0)
		{
			i = m;
			m = m->next;
		}
		m->next = new;
		new->last = i;
	}
}
