/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:04:09 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 04:04:11 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_map	*ft_mapnew(void *key, void *value)
{
	t_map *m;

	if ((m = (t_map*)malloc(sizeof(t_map))))
	{
		m->key = key;
		m->value = value;
		m->next = NULL;
		m->last = NULL;
	}
	else
		m = NULL;
	return (m);
}
