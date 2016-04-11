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

t_point			***init_fdf_points(const int fd)
{
	int		n;
	t_point	***p;
	char	*ptr;

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

static char		*read_color(t_color *c, char *ptr)
{
	*c = ft_atoi_casebase(ptr, BASE_HEX_MIN);
	while (*ptr && (ft_isalnum(*ptr)))
		ptr++;
	return (ptr);
}

static void		*init_content_fdf(int mask, char *ptr, t_point ***p, int x)
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
			init_color(mask, p[x][l]);
			while (*ptr && (ft_isalnum(*ptr) || *ptr == '-') && *ptr != ',')
				ptr++;
			if (!ft_strncmp(ptr, ",0x", 3))
				ptr = read_color(&p[x][l]->coul, ptr + 3);
		}
		else
		{
			ft_putstr_fd("fdf: An error occured: bad character\n", 2);
			return (NULL);
		}
		l++;
	}
	return (p);
}

t_point			***init_fdf(int mask, int const fd, t_point ***p)
{
	int		n;
	char	*ptr;

	n = 0;
	ptr = NULL;
	while (p && get_next_line(fd, &ptr) > 0)
	{
		if (!init_content_fdf(mask, ptr, p, n++))
		{
			free_fdf(p);
			p = NULL;
		}
		free(ptr);
		ptr = NULL;
	}
	close(fd);
	free(ptr);
	return (p);
}
