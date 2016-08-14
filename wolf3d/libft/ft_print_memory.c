/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:11:04 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 04:11:05 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implemt.h"

static void	putline(int value, int offset)
{
	if (value >= BASE)
	{
		putline(value / BASE, offset - 1);
		putline(value % BASE, offset - 1);
	}
	else
	{
		if (value && offset > 0)
			write(1, "0", 1);
		if (value > 9)
			value += 'a' - 10;
		else
			value += '0';
		write(1, &value, 1);
	}
}

static void	myputstr(char *s, int n)
{
	int	l;

	l = 0;
	while (l < 16 && l < n)
	{
		if (*s < 127 && *s >= 32)
			write(1, s, 1);
		else
			write(1, ".", 1);
		s++;
		l++;
	}
}

static int	sizeline(int v)
{
	int l;

	l = 0;
	if (v >= BASE)
	{
		l += sizeline(v / BASE);
		l += sizeline(v % BASE);
	}
	else
		return (1);
	return (l);
}

static void	write_content(void *addr, int size, int len)
{
	int	i;

	i = 0;
	while (i < OFFSET_LINE && len + i < size)
	{
		if (*(unsigned char*)(addr + len + i) == 0)
			write(1, "00", 2);
		else
			putline(*(unsigned char*)(addr + len + i), 1);
		if (i % 2)
			write(1, " ", 1);
		i++;
	}
	while (i < OFFSET_LINE)
	{
		write(1, "  ", 2);
		if (i % 2)
			write(1, " ", 1);
		i++;
	}
}

void		*ft_print_memory(const void *addr, size_t size)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (len < size)
	{
		i = 8 - sizeline(len);
		while (i)
		{
			write(1, "0", 1);
			i--;
		}
		putline(len, 0);
		write(1, ": ", 2);
		write_content((void*)addr, size, len);
		myputstr((void*)addr + len, size - len);
		write(1, "\n", 1);
		len += OFFSET_LINE;
	}
	return ((void*)addr);
}
