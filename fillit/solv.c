/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:53:55 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:53:57 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void			build_solution(t_octet size, t_solution *s, t_tetrinoid *item)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (((1 << j) & item->mat[i]) >> j)
				s->buffer[i + j * size] = (item->c);
			j++;
		}
		i++;
	}
}

void			leave_solution(t_octet size, t_solution *s, t_tetrinoid *item)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (s->buffer[i + j * size] == item->c)
				s->buffer[i + j * size] = '.';
			j++;
		}
		i++;
	}
}

t_octet			*reset_item_bis(t_octet size, t_octet *item)
{
	unsigned int	n;
	int				m;

	n = 0;
	m = 0;
	while (n < size && !item[n])
		n++;
	while (n < size && item[n])
	{
		item[m] = item[n];
		item[n] = 0;
		n++;
		m++;
	}
	return (item);
}

t_octet			*reset_item(t_octet size, t_octet *item, int flag)
{
	unsigned int	n;
	int				bool;

	bool = 0;
	while (!bool)
	{
		n = 0;
		while (n < size && !(item[n] != 0 && item[n] % 2 == 1))
			n++;
		if (item[n] % 2 == 1)
			bool = 1;
		n = 0;
		while (!bool && n < size)
		{
			item[n] = item[n] >> 1;
			n++;
		}
	}
	if (flag && !item[0])
		item = reset_item_bis(size, item);
	return (item);
}

int				v4(t_tetrinoid **m, t_octet *item, t_octet *ref,
	t_solution *s)
{
	int			verif;
	int			ret;
	int			bool;

	bool = 0;
	ret = -1;
	if (*m)
	{
		while (move_item(ref, s->size, (*m)->mat, bool) == 1)
		{
			if ((verif = v4(m + 1, item, concat(ref, (*m)->mat, s->size), s))
				>= 0)
			{
				ret = 0;
				leave_solution(verif ? ((unsigned)verif) : (s->size), s, (*m));
				build_solution(s->size, s, (*m));
			}
			ref = reset(ref, (*m)->mat, (verif > 0) ? verif : (int)s->size);
			bool = 1;
		}
		return (ret);
	}
	else if (s)
		return (solution(s->size, ref, &s));
	return (-1);
}
