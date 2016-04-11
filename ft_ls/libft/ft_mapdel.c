/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:04:36 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 04:04:41 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void	pos_delt(t_map **root, int clear, void (*freek)(), void (*freev)())
{
	t_map	*n;
	t_map	*tmp;

	n = *root;
	while (n)
	{
		tmp = n->next;
		if (freev)
			(*freev)(n->value);
		n->value = NULL;
		if (freek)
			(*freek)(n->key);
		n->key = NULL;
		if (clear)
		{
			free(n);
			n = NULL;
		}
		n = tmp;
	}
}

void		ft_mapdel(t_map **root, int clear, void (*freek)(), void (*freev)())
{
	t_map	*l;
	t_map	*tmp;

	l = (*root) ? (*root)->last : NULL;
	pos_delt(root, clear, freek, freev);
	while (l)
	{
		tmp = l->last;
		if (freev)
			(*freev)(l->value);
		l->value = NULL;
		if (freek)
			(*freek)(l->key);
		l->key = NULL;
		if (clear)
		{
			free(l);
			l = NULL;
		}
		l = tmp;
	}
}
