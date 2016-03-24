/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stkinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/05 09:53:57 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:41:35 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void			ft_stkinit(t_stack *stk, const unsigned int max_size)
{
	stk->max_size = max_size;
	stk->size = -1;
	stk->content = (t_stacktype*)malloc(sizeof(t_stacktype) * max_size);
}
