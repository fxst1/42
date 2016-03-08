/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 14:04:37 by fjacquem          #+#    #+#             */
/*   Updated: 2016/01/22 14:04:39 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*realloc_buffer(char *addr, size_t len)
{
	char	*ptr;

	ptr = NULL;
	if (addr && (ptr = ft_strnew(len)))
	{
		ft_strcpy(ptr, addr);
		ptr[len] = 0;
		free(addr);
	}
	return (ptr);
}

static	char	*set_line(char *buf, char *line, size_t len)
{
	size_t	index;

	index = 0;
	while (index < len && *buf != '\n' && *buf)
	{
		line[index] = *(buf++);
		index++;
	}
	if (*buf)
		buf++;
	line[index] = 0;
	return (buf);
}

static	char	*stop(t_gnl *g, char *buf, int *len)
{
	int	ret;

	ret = 1;
	if (g->buffer)
		ft_strcpy(buf, g->buffer);
	*len = ft_strlen(buf);
	while (ret > 0)
	{
		if (!ft_strchr(buf, '\n'))
		{
			*len += BUFF_SIZE;
			buf = realloc_buffer(buf, *len);
			ret = read(g->fd, buf + (*len - BUFF_SIZE), BUFF_SIZE);
			if (ret < 0)
			{
				ft_memdel((void**)&g->buffer);
				ft_memdel((void**)&buf);
				return (NULL);
			}
		}
		else
			ret = -1;
	}
	return (buf);
}

static	int		read_buffer(const int fd, char **line)
{
	static char *(keep[255]) = {0};
	char		*buf;
	int			len;
	t_gnl		g;

	g.fd = fd;
	g.buffer = keep[fd];
	buf = ft_strnew((keep[fd]) ? ft_strlen(keep[fd]) : BUFF_SIZE);
	if ((buf = stop(&g, buf, &len)) == NULL)
		return (-2);
	*line = ft_strnew(len);
	if (keep[fd])
		ft_memdel((void**)&keep[fd]);
	keep[fd] = ft_strnew(len);
	keep[fd] = ft_strcpy(keep[fd], set_line(buf, *line, len));
	if (!*buf)
	{
		if (keep[fd])
			ft_memdel((void**)&keep[fd]);
		ft_memdel((void**)&buf);
		return (-1);
	}
	ft_memdel((void**)&buf);
	return (len);
}

int				get_next_line(int const fd, char **line)
{
	int	size;

	if (fd < 0 || !line)
		return (-1);
	size = read_buffer(fd, line);
	if (size == -2)
		return (-1);
	else if (size == -1)
		return (0);
	return (!!(*line && size));
}
