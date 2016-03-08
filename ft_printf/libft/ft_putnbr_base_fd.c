/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:51:22 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:51:25 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base_fd(int nb, char *base, int fd)
{
	int length;

	length = ft_strlen(base);
	if (length > 0)
	{
		if (nb < 0)
		{
			if (length == 10)
				write(fd, "-", 1);
			nb = -nb;
		}
		if (nb >= length)
		{
			ft_putnbr_base_fd(nb / length, base, fd);
			ft_putnbr_base_fd(nb % length, base, fd);
		}
		else
			write(fd, &base[nb], 1);
	}
}
