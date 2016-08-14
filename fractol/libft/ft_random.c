/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:09:41 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 04:09:45 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implemt.h"

long int	ft_random(void)
{
	static long int	r = 0xACDC;
	static int		n = 1;
	char			*ptr;

	ptr = (char*)malloc(sizeof(char*));
	r |= (long int)ptr;
	r = (r * n) + 0xACDC;
	n++;
	free(ptr);
	return (r);
}
