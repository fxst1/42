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

void		free_tetrinoid(t_tetrinoid *t)
{
	if (t)
	{
		free(t);
	}
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
			j++;
		}
		i++;
	}
	return (compt == 4);
}
