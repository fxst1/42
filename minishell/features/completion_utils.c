/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/16 02:56:21 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/16 02:56:23 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniterm.h"

int		display_results(t_list *l)
{
	int	ok;

	ok = 0;
	while (ok != 'n' && ok != 'y')
		read(0, &ok, 1);
	if (ok == 'y')
	{
		while (l)
		{
			ft_putendl(l->content);
			l = l->next;
		}
		ft_putendl("=========================");
	}
	return (1);
}

void	free_list(t_list *l)
{
	t_list	*nextl;

	nextl = NULL;
	while (l)
	{
		l->next = nextl;
		free(l->content);
		free(l);
		l = NULL;
		l = nextl;
	}
}

void	print_it(t_term *t, t_list *l, char *cmd)
{
	if (l && l->next)
	{
		ft_putstr("\nDisplay ");
		ft_putnbr(ft_lstsize(l));
		ft_putstr(" results ? [y/n]\n");
		display_results(l);
		print_prompt(t);
		ft_putstr(cmd);
	}
}
