/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:20:31 by fjacquem          #+#    #+#             */
/*   Updated: 2015/11/24 10:15:49 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char			*tmp;
	unsigned int	i;

	i = 0;
	tmp = (char*)dst;
	while (i < n)
	{
		((char*)dst)[i] = ((const char*)src)[i];
		i++;
	}
	return (tmp);
}
