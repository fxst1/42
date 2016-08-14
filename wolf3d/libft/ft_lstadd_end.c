/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_begin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:20:18 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 04:20:20 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_end(t_list **l, t_list *new)
{
	t_list	*lst;

	if (*l)
	{
		lst = *l;
		while (lst->next)
		{
			lst = lst->next;
		}
		lst->next = new;
	}
	*l = new;
}
