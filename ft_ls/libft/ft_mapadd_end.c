/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:02:33 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 04:02:35 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	ft_mapadd_end(t_map **root, t_map *new)
{
	t_map	*m;
	t_map	*l;

	if (*root)
	{
		l = NULL;
		m = *root;
		while (m->next)
		{
			l = m;
			m = m->next;
		}
		m->last = l;
		m = new;
	}
	else
		*root = new;
}
