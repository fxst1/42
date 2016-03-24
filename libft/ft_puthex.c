/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/05 09:53:57 by fjacquem          #+#    #+#             */
/*   Updated: 2014/07/05 09:55:10 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implemt.h"

static void		ft_puthex_rec(unsigned int number)
{
	char	c;
	char	*map;

	map = "0123456789abcdef";
	if (number)
	{
		c = (char)(number & 0xF);
		number = (number >> 4);
		ft_puthex_rec(number);
		ft_putchar(map[(int)c]);
	}
}

void			ft_puthex(unsigned int number)
{
	ft_putstr("0x");
	if (number)
		ft_puthex_rec(number);
	else
		ft_putstr("0");
}
