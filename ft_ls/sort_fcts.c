/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_fcts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/03 02:57:13 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/03 02:57:15 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void	sort_files(t_args *a, t_file *root)
{
	t_file	*tmp;

	tmp = root->next;
	while (tmp)
	{
		swap = root;
		if (test_sort_mask(swap, tmp, a))
		{
			ft_swap(&swap->name, &tmp->name);
			ft_swap(&swap->print, &tmp->print);
		}
		tmp = tmp->next;
	}
}

void	sort_filesalph(t_args *a, t_file *root)
{
	t_file	*tmp;

	tmp = root->next;
	while (tmp)
	{
		if (test_sort_alph(root, tmp, a))
		{
			ft_swap(&root->print, &tmp->print);
			ft_swap(&root->name, &tmp->name);
		}
		tmp = tmp->next;
	}
}
