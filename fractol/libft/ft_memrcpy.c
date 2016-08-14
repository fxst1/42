/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:21:16 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 04:21:18 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memrcpy(void *dst, const void *src, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	j = len - 1;
	while (i < len)
	{
		((unsigned char*)dst)[j] = ((unsigned char*)src)[i];
		j--;
		i++;
	}
	return (dst);
}
