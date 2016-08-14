/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:53:55 by fjacquem          #+#    #+#             */
/*   Updated: 2015/12/01 20:53:57 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H
# include "libft.h"
# define AFFIX	2
# define SUFFIX 4
# define PREFIX	8

typedef struct		s_btree
{
	void			*content;
	size_t			content_size;

	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

t_btree				*ft_btreenew(void *cnt, size_t size_cnt);
void				ft_btreeadd(unsigned int index, t_btree **root,\
													t_btree *new);
void				ft_btreeforeach(t_btree *root, unsigned int flag, \
													void (*fct)());
void				ft_btreefree(t_btree *root);
#endif
