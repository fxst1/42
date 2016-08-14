/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/07/05 09:53:57 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:41:35 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H
# include "libft.h"

typedef char		t_stacktype;
typedef	struct		s_stack
{
	t_stacktype		*content;
	int				size;
	unsigned int	max_size;
}					t_stack;

void				ft_stkinit(t_stack *stk, const unsigned int max_size);
void				ft_stkclear(t_stack *stk);
unsigned int		ft_stkempty(t_stack *stk);
unsigned int		ft_stkfull(t_stack *stk);
t_stacktype			ft_stkpop(t_stack *stk);
void				ft_stkpush(t_stack *stk, t_stacktype content);

#endif
