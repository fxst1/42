/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stkpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/05 09:53:57 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:41:35 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

void			ft_stkpush(t_stack *stk, t_stacktype content)
{
	if (!ft_stkfull(stk))
		stk->content[++stk->size] = content;
}
