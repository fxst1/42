/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putansi_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 10:50:38 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 10:50:40 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implemt.h"

void	ft_putansi_nbr(int code, const int fd)
{
	ft_putstr_fd("\033[", fd);
	ft_putnbr_fd(code, fd);
	write(fd, "m", 1);
}
