/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:50:46 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:50:55 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implemt.h"

void	ft_putnstr(char *str, int offset)
{
	int	len;

	len = ft_strlen(str);
	while (offset > 0)
	{
		write(1, str, len);
		offset--;
	}
	while (offset < 0)
	{
		write(1, str, len);
		offset++;
	}
}
