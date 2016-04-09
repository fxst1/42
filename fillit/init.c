/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:53:55 by fjacquem          #+#    #+#             */
/*   Updated: 2016/01/15 02:16:36 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_solution	*init_solution(unsigned int size)
{
	t_solution	*s;

	if ((s = (t_solution*)malloc(sizeof(t_solution))) != NULL)
	{
		s->size = size;
		ft_memset(s->buffer, '.', MAX);
	}
	return (s);
}

t_tetrinoid	*init_tetrinoid(unsigned int *mat, char c)
{
	t_tetrinoid	*t;

	if ((t = malloc(sizeof(t_tetrinoid))) != NULL)
	{
		t->c = c;
		if (mat)
			ft_memcpy(t->mat, mat, 4);
	}
	return (t);
}

int			dbg(unsigned int *mat)
{
	int	i;
	int	b;

	i = 0;
	b = 0;
	while (i < 3)
	{
		if (!b && mat[i])
			b = 1;
		if (b && mat[i] && mat[i + 1] && !(mat[i] & mat[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

int			is_tetrinoid(unsigned int *mat)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	compt;

	compt = 0;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if ((mat[i] >> j) & 1 && ((j < 3 && mat[i] >> (j + 1) & 1) ||
				(j > 0 && mat[i] >> (j - 1) & 1) ||
				(i < 4 && mat[i] & mat[i + 1]) ||
				(i > 0 && mat[i] & mat[i - 1])))
				compt++;
			else if (compt < 4 && compt > 0 && !mat[i])
				return (0);
			j++;
		}
		i++;
	}
	return (compt == 4 && dbg(mat));
}
