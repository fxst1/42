/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stknew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/05 09:53:57 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:41:35 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_stack			*ft_stknew(const unsigned int max_size)
{
	t_stack	*ptr;

	if ((ptr = (t_stack*)malloc(sizeof(t_stack))))
	{
		ft_stkinit(ptr, max_size);
	}
	return (ptr);
}
