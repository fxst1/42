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

void	print_cmdline(t_cmdline *cmd)
{
	printf("\nbuffer = <%s>\n", cmd->buffer);
	printf("keep = <%s>\n", cmd->keep);
	printf("cursor = <%d>\n", cmd->cursor);
	printf("size = <%d>\n", cmd->size);
	printf("delt = <%d>\n", cmd->delt_select);
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

char		*read_line(int fd)
{
	char	*str;
	char	*tmp;
	int		len;
	int		ret;

	len = 0;
	ret = 0;
	str = (char*)malloc(sizeof(char) * (len + 1));
	str[0] = 0;
	//str[1] = 0;
	while ((ret = read(fd, &str[len], 1)) > 0 && str[len] != '\n')
	{
		tmp = (char*)malloc(sizeof(char) * (len + 1));
		ft_memcpy(tmp, str, len);
		tmp[len] = 0;
		free(str);
		str = (char*)malloc(sizeof(char) * (len + 1));
		ft_memcpy(str, tmp, len);
		str[len] = 0;
		free(tmp);
		len++;
	}
	if (ret < 0)
		ft_memdel((void**)&str);
		printf("%d, %s\n", fd, str);
		return (str);
}
