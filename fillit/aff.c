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
		ft_putchar(!((1 << i) & value) >> i ? ('.') : (c));
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
			ft_putchar(s->buffer[i + s->size * j]);
			j++;
		}
		ft_putstr("\n");
		i++;
	}
}

void	print_tab(unsigned int *tab, unsigned int size, char c)
{
	unsigned int i;

	i = 0;
	if (tab)
		while (i < size)
		{
			print_base(tab[i], (c) ? c : '#', size);
			ft_putstr(" | ");
			ft_putnbr(tab[i]);
			ft_putstr("\n");
			i++;
		}
	else
		ft_putstr("(null)");
	ft_putstr("\n");
}
