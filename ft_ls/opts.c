/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 20:03:52 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/24 20:03:54 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_map	*init_extension_map_from_file(char *filename)
{
	int		fd;
	t_map	*m;
	char	*line;
	char	*key;
	int		index;

	m = NULL;
	index = 0;
	if ((fd = open(filename, O_RDONLY)) > 0)
	{
		while (get_next_line(fd, &line) > 0)
		{
			key = ft_strnew(32);
			index = 0;
			while (line[index] != ',')
			{
				key[index] = line[index];
				index++;
			}
			key[index] = 0;
			ft_mapadd_begin(&m, ft_mapnew(key, ft_strdup(line + index + 2)));
			free(line);
		}
	}
	return (m);
}

char	*set_str(char *tmp, char *s1, char *s2)
{
	tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + PSL);
	tmp = set_name_path(tmp, s1, s2);
	return (tmp);
}
