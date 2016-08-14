/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:18:25 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 04:18:28 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implemt.h"

void	*ft_realloc(void *addr, size_t len)
{
	void	*ptr;

	ptr = NULL;
	if (addr && (ptr = ft_memalloc(len)))
	{
		ft_memcpy(ptr, addr, len);
		free(addr);
	}
	return (ptr);
}
