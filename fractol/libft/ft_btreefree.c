/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btreefree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:53:55 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:53:57 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

void	ft_btreefree(t_btree *root)
{
	if (root)
	{
		ft_btreefree(root->left);
		ft_btreefree(root->right);
		free(root);
	}
}
