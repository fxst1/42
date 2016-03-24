/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 20:53:55 by fjacquem          #+#    #+#             */
/*   Updated: 2016/01/15 02:13:36 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void				*put_error(void)
{
	ft_putstr_fd("error\n", 1);
	return (NULL);
}

t_octet				*get_matrix(t_octet *mat, int fd, int c)
{
	unsigned int	i;
	unsigned int	n;

	n = 0;
	i = 1;
	mat[0] = (c == '#') ? (1) : 0;
	while (i < 16 && read(fd, &c, 1))
	{
		if (c == '#' || c == '.')
			mat[i++ / 4] += (c == '#') ? 1 << (i % 4) : 0;
		else if (c != '\n')
		{
			free(mat);
			return (NULL);
		}
		else
			n++;
	}
	read(fd, &c, 1);
	if (n != 3 || c != '\n' || c == '.' || c == '#')
	{
		free(mat);
		return (NULL);
	}
	return (is_tetrinoid(mat) ? mat : NULL);
}

t_tetrinoid			**build_tetrinoid(const int fd, t_tetrinoid **tab)
{
	unsigned int	n;
	char			c;

	n = 0;
	c = 1;
	while (read(fd, &c, 1) && c)
	{
		if (c != '\n' && n > 0)
			return (put_error());
		if (c == '\n')
			read(fd, &c, 1);
		tab[n] = init_tetrinoid(NULL, n + 'A');
		ft_memset(tab[n]->mat, 0, sizeof(int) * 26);
		if (!get_matrix(tab[n]->mat, fd, c) || c == '\n' ||
			(n > 0 && !tab[n - 1]))
			return (put_error());
		reset_item(4, tab[n]->mat, 1);
		n++;
	}
	if (n == 0)
		return (put_error());
	tab[n] = NULL;
	return (tab);
}

t_tetrinoid			**init_fillit(char **argv)
{
	int				fd;
	t_tetrinoid		**tab;

	tab = (t_tetrinoid **)malloc(sizeof(t_tetrinoid*) * 26);
	while (*argv)
	{
		fd = open(*argv, O_RDONLY);
		if (fd >= 0)
		{
			if (!build_tetrinoid(fd, tab))
				return (NULL);
		}
		else
			ft_putstr_fd("error\n", 1);
		close(fd);
		argv++;
	}
	return (tab);
}

void				free_matrix(t_tetrinoid **tab)
{
	unsigned int	n;

	n = 0;
	while (tab[n])
	{
		if (tab[n])
			free(tab[n]);
		n++;
	}
}
