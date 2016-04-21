/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 19:06:21 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/15 19:06:23 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniterm.h"

void	line_up_down(int str_len, int index, int read)
{
	int			prmpt;
	int			col;
	int			offset;

	(void)read;
	prmpt = get_prompt_offset();
	col = get_miniterm(NULL)->ws.ws_col;
	offset = prmpt + str_len;
	if (!(offset % col))
	{
		write(1, "\n", 1);
	}
	if (read == 4414235 && (index + prmpt) % col == col - 1)
	{
		write(1, "\033[B", 3);
		ft_putnstr("\033[D", col);
	}
	else if ((read == 127 || read == 4479771) && (index + prmpt) % col ==
		col - 1)
	{
		write(1, "\033[A", 3);
		ft_putnstr("\033[C", col);
	}
}

void	inputs_l_r(int read_value, int *index, int size)
{
	if (read_value == 4414235)
	{
		if (*index < size - 1)
		{
			write(1, "\033[C", 3);
			(*index)++;
		}
	}
	else
	{
		if (*index > 0)
		{
			write(1, "\033[D", 3);
			(*index)--;
		}
	}
}

int		inputs_u_d(t_term *t, int read_value, char **line, int *size)
{
	if (read_value == 4283163)
		return (historic(t, HIST_UP, line, size) - 1);
	return (historic(t, HIST_DOWN, line, size) - 1);
}

void	inputs_del_norm(int read_value, char **line, int *index, int *size)
{
	char *tmp;

	if (read_value == 127)
	{
		if (*size > *index && *index > 0 && (*size)--)
		{
			write(1, "\033[1D\033[s\033[K", 10);
			(*line)[(*index) - 1] = 0;
			ft_strcat(*line, &(*line)[*index]);
			ft_putstr(&(*line)[(*index) - 1]);
			(*index)--;
			write(1, "\033[u", 3);
		}
	}
	else if ((tmp = ft_strdup(&(*line)[*index])))
	{
		ft_strcpy(&(*line)[*(index) + 1], tmp);
		write(1, "\033[s", 3);
		(*line)[*index] = read_value;
		ft_putstr(&(*line)[*index]);
		write(1, "\033[u\033[1C", 7);
		(*index)++;
		free(tmp);
		(*size)++;
	}
}

char	*get_cmd_line(t_term *t, char **line, int read_value)
{
	int		size;
	int		index;
	int		offset;

	offset = get_prompt_offset();
	size = 1;
	index = 0;
	t->reading = 1;
	t->line = line;
	write(1, "\033[7h", 4);
	while (read(0, &read_value, sizeof(int)) && read_value != '\n')
	{
		*line = realloc_buffer(*line, size);
		if (read_value == 4283163 || read_value == 4348699)
			index = inputs_u_d(t, read_value, line, &size);
		else if ((read_value == 32521 || read_value == '\t'))
			start_completion(t, line, &index, &size);
		else if (read_value == 4414235 || read_value == 4479771)
			inputs_l_r(read_value, &index, size);
		else
			inputs_del_norm(read_value, line, &index, &size);
		read_value = 0;
	}
	write(1, "\n", 1);
	return (*line);
}
