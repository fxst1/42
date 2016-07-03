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

void	print_historic(t_term *t, int *index)
{
	int	i;

	i = 0;
	write(1, "\n<=====> HISTORIC <=====>\n", 26);
	while (i < t->n_cmds && t->his[i])
	{
		write(1, t->his[i], ft_strlen(t->his[i]));
		write(1, "\n", 1);
		i++;
	}
	i = ft_strlen(t->line.buffer);
	print_prompt(t);
	write(1, t->line.buffer, i);
	*index = i;
}

int		historic(t_term *t, int action, char **cmd, int *last_size)
{
	int		index;

	index = 0;
	if (action == HIST_DOWN && t->his[0])
		set_up(t, last_size, cmd);
	else if (action == HIST_UP)
		set_down(t, last_size, cmd);
	else if (action == HIST_ADD && ft_strlen(*cmd) > 0)
	{
		while (t->his[index] && index + 1 < t->n_cmds)
			index++;
		t->his[index] = ft_strdup(*cmd);
	}
	return (*last_size);
}
