/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 03:53:06 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 03:53:10 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "implemt.h"

void	ft_swap(void *a, void *b)
{
	long unsigned int	tmp;

	tmp = (*(long unsigned int*)a);
	*(long unsigned int*)a = (*(long unsigned int*)b);
	*(long unsigned int*)b = tmp;
}
