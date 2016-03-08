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

void	ft_putnstr(char *str, unsigned int offset)
{
	if (str && *str)
	{
		if (offset)
		{
			if (ft_isprint(*str))
				write(1, str, 1);
			else
				write(1, ".", 1);
			ft_putnstr(str + 1, offset - 1);
		}
	}
}
