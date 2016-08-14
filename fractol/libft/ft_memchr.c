/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 13:12:13 by fjacquem          #+#    #+#             */
/*   Updated: 2015/11/24 13:12:14 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	char	*ptr;
	char	tmp;
	int		i;

	i = 0;
	tmp = (char)c;
	ptr = (char*)s;
	while (len--)
	{
		if (ptr[i] == tmp)
			return (ptr + i);
		i++;
	}
	return (NULL);
}
