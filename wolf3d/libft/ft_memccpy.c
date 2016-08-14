/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 16:32:55 by fjacquem          #+#    #+#             */
/*   Updated: 2014/11/26 15:56:49 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n--)
	{
		*(unsigned char*)dst++ = *(unsigned char*)src;
		if (*(unsigned char*)src++ == (unsigned char)c)
			return ((unsigned char*)dst);
	}
	return (NULL);
}
