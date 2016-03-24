/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 13:09:37 by fjacquem          #+#    #+#             */
/*   Updated: 2015/11/24 13:09:39 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *lst;

	if ((lst = (t_list*)malloc(sizeof(t_list))) != NULL)
	{
		lst->next = NULL;
		lst->content = (content) ?\
		(malloc(sizeof(content_size))) : (NULL);
		if (lst->content)
		{
			lst->content = ft_memcpy(lst->content, content, content_size);
			lst->content_size = content_size;
		}
		else
		{
			lst->content = NULL;
			lst->content_size = 0;
		}
	}
	return (lst);
}
