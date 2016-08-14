/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putansi_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 10:50:55 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 10:50:57 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implemt.h"

void	ft_putansi_str(char *code, const int fd)
{
	ft_putstr_fd("\033[", fd);
	ft_putstr_fd(code, fd);
	write(fd, "m", 1);
}
