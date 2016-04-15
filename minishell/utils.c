/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 22:22:55 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/14 22:22:57 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniterm.h>

void	delete_tab(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	suppr_unprintable(char *str)
{
	while (*str && ft_isprint(*str))
		str++;
	*str = 0;
}

char	*realloc_buffer(char *buffer, size_t size)
{
	char	*tmp;

	if (!(size + 1) % 1024)
	{
		tmp = ft_strdup(buffer);
		free(buffer);
		buffer = ft_strnew(size + 1024);
		ft_strcpy(buffer, tmp);
	}
	return (buffer);
}

void	set_rawmode(struct termios *termios_p)
{
	termios_p->c_lflag &= ~(ECHO | ICANON);
	termios_p->c_cc[VMIN] = 1;
	termios_p->c_cc[VTIME] = 0;
}

int		last_index(char **t)
{
	int	index;

	index = 0;
	while (t[index])
		index++;
	return (index);
}
