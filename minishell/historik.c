/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historik.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 19:52:43 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/15 19:52:44 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniterm.h"

void	set_up(t_term *t, int *last_size, char **cmd)
{
	int	index;

	index = t->act;
	if (index < t->n_cmds && t->his[index])
	{
		while (*last_size > 1)
		{
			write(1, "\033[1D", 4);
			(*last_size)--;
		}
		*last_size = ft_strlen(t->his[index]);
		ft_strcpy(*cmd, t->his[index]);
		write(1, "\033[K", 3);
		(*cmd)[*last_size] = 0;
		write(1, *cmd, *last_size);
		(*last_size)++;
		t->act += (index < t->n_cmds && t->his[index]);
	}
}

void	set_down(t_term *t, int *last_size, char **cmd)
{
	int	index;

	index = t->act - 1;
	if (index >= 0 && t->his[index])
	{
		while (*last_size > 1)
		{
			write(1, "\033[1D", 4);
			(*last_size)--;
		}
		*last_size = ft_strlen(t->his[index]);
		ft_strcpy(*cmd, t->his[index]);
		write(1, "\033[K", 3);
		(*cmd)[*last_size] = 0;
		write(1, *cmd, *last_size);
		(*last_size)++;
		t->act -= (index > 0);
	}
}

int		historic(t_term *t, int action, char **cmd, int *last_size)
{
	int		index;

	index = 0;
	if (action == HIST_DOWN && t->his[0])
		set_up(t, last_size, cmd);
	else if (action == HIST_UP)
		set_down(t, last_size, cmd);
	else if (action == HIST_ADD)
	{
		while (t->his[index] && index + 1 < t->n_cmds)
			index++;
		t->his[index] = ft_strdup(*cmd);
	}
	return (*last_size);
}
