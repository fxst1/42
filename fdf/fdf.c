/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 22:34:10 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/24 22:34:11 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_point	**init_fdf_line(char *buf)
{
	t_point	**p;
	int		n;

	p = NULL;
	n = 0;
	while (*buf)
	{
		while (*buf == ' ' || *buf == '\t' || *buf == '\n')
			buf++;
		while (*buf && (ft_isalnum(*buf) || *buf == '-'))
			buf++;
		n++;
		buf++;
	}
	n += 3;
	p = (t_point**)malloc(sizeof(t_point*) * (n + 1));
	while (n >= 0)
		p[n--] = NULL;
	return (p);
}

t_point			***init_fdf_points(char *fname)
{
	int		fd;
	int		n;
	t_point	***p;
	char	*ptr;

	fd = open(fname, O_RDONLY);
	n = 0;
	p = NULL;
	ptr = NULL;
	while (get_next_line(fd, &ptr) > 0)
	{
		free(ptr);
		ptr = NULL;
		n++;
	}
	free(ptr);
	close(fd);
	n += 3;
	p = (t_point***)malloc(sizeof(t_point**) * (n + 1));
	while (n >= 0)
		p[n--] = NULL;
	return (p);
}

static void		init_content_fdf(t_env *e, char *ptr, t_point ***p, int x)
{
	int	l;

	l = 0;
	p[x] = init_fdf_line(ptr);
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n')
			ptr++;
		if (*ptr && (*ptr == '-' || ft_isalnum(*ptr)))
		{
			p[x][l] = new_point(l, x, ft_atoi(ptr), 0xff);
			init_color(e, p[x][l]);
			while (*ptr && (ft_isalnum(*ptr) || *ptr == '-'))
				ptr++;
		}
		l++;
	}
}

t_point			***init_fdf(t_env *e, int const fd, t_point ***p)
{
	int		n;
	char	*ptr;

	n = 0;
	ptr = NULL;
	while (get_next_line(fd, &ptr) > 0)
	{
		init_content_fdf(e, ptr, p, n++);
		free(ptr);
	}
	free(ptr);
	return (p);
}
