/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:49:31 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:49:35 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dst, const char *src)
{
	char *ptr;

	ptr = dst;
	while (*dst)
	{
		dst++;
	}
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
	*dst = 0;
	return (ptr);
}
