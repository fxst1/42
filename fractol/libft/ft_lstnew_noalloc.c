/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_noalloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 00:49:19 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 00:49:31 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstnew_noalloc(void *cnt, size_t cnt_size)
{
	t_list	*lst;

	if ((lst = (t_list*)malloc(sizeof(t_list))))
	{
		lst->next = NULL;
		lst->content = cnt;
		lst->content_size = cnt_size;
	}
	else
		lst = NULL;
	return (lst);
}
