/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreenew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:53:55 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:53:57 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

t_btree		*ft_btreenew(void *cnt, size_t size_cnt)
{
	t_btree *t;

	t = (t_btree*)malloc(sizeof(t_btree));
	if (t)
	{
		t->content = cnt;
		t->content_size = size_cnt;
		t->left = NULL;
		t->right = NULL;
	}
	return (t);
}
