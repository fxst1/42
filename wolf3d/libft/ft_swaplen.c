/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swaplen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:08:58 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 04:09:00 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implemt.h"

void	ft_swaplen(void *a, void *b, size_t len_a, size_t len_b)
{
	char	tmp;

	while (len_a && len_b)
	{
		tmp = *(char*)a;
		*(char*)(a++) = *(char*)b;
		*(char*)(b++) = tmp;
		len_a--;
		len_b--;
	}
}
