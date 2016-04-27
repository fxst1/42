/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fcts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 19:42:34 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/07 19:42:36 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <explorer.h>

void		addfile(t_file **f, t_file *add, int rev)
{
	t_file	*tmp;
	t_file	*last;
	char	*name;

	tmp = *f;
	last = NULL;
	if (tmp && (name = add->p.name))
	{
		while (tmp && (ft_strcmp(tmp->p.name, name) > 0) == !rev)
		{
			last = tmp;
			tmp = tmp->next;
		}
		add->next = tmp;
		if (last)
			last->next = add;
		else
			*f = add;
	}
	else
		*f = add;
}
