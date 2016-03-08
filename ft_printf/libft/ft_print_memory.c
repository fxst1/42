/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:51:59 by fjacquem          #+#    #+#             */
/*   Updated: 2016/01/14 21:47:52 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "implemt.h"

void	ft_print_memory(void *addr, unsigned int size)
{
	unsigned int	offset;

	offset = 0;
	while (offset < size)
	{
		ft_puthex(offset);
		write(1, ":", 1);
		ft_puthex(*((unsigned int*)addr + offset));
		ft_putnstr((char*)addr + offset, PRINTMEM_OFFSET);
		write(1, "\n", 1);
		offset += PRINTMEM_OFFSET;
	}
}
