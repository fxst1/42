/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:53:55 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:53:57 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_octet			*move_left(t_octet *item, t_octet size)
{
	t_octet	n;

	n = 0;
	while (n < size)
	{
		item[n] = item[n] << 1;
		n++;
	}
	return (item);
}

t_octet			*move_down(t_octet *ref, t_octet *item, t_octet size)
{
	t_octet	n;
	t_octet	j;

	j = 0;
	while (ref[j] != 0)
	{
		j++;
	}
	item = reset_item(size, item, 0);
	n = size - 1;
	while (n > 0)
	{
		item[n] = item[n - 1];
		n--;
	}
	item[0] = 0;
	return (item);
}

int				move_item(t_octet *ref, t_octet size, t_octet *tmp, int bool)
{
	int	b;

	b = 0;
	if (bool)
		tmp = move_left(tmp, size);
	while (b < 1)
	{
		b = verification(ref, tmp, size);
		if (b == 0)
			tmp = move_down(ref, tmp, size);
		else if (b == -1)
			tmp = move_left(tmp, size);
		else if (b == -2)
		{
			tmp = reset_item(size, tmp, 1);
			return (0);
		}
	}
	return (1);
}

t_octet			*concat(t_octet *ref, t_octet *item, t_octet size)
{
	t_octet i;

	i = 0;
	while (i < size)
	{
		ref[i] = item[i] | ref[i];
		i++;
	}
	return (ref);
}

t_octet			*reset(t_octet *ref, t_octet *item, t_octet size)
{
	t_octet	i;

	i = 0;
	while (i < size)
	{
		ref[i] = (~item[i] & ref[i]);
		i++;
	}
	return (ref);
}
