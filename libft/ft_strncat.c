/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:47:50 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:47:51 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t len)
{
	char	*cur;

	cur = dst;
	while (*cur != '\0')
	{
		cur++;
	}
	while (*src != '\0' && len > 0)
	{
		*cur = *src;
		cur++;
		src++;
		len--;
	}
	*cur = '\0';
	return (dst);
}
