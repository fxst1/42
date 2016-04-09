/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:53:55 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:53:57 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	print_base(unsigned int value, char c, unsigned int bits)
{
	unsigned int i;

	i = 0;
	while (i < bits)
	{
		write(1, !((1 << i) & value) >> i ? (".") : (&c), 1);
		value = value >> 1;
		bits--;
	}
}

void	print_solution(t_solution *s)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while (i < s->size)
	{
		j = 0;
		while (j < s->size)
		{
			write(1, &s->buffer[i + s->size * j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}
