/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 01:52:53 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 01:53:05 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		print_offset(int offset, int c)
{
	char	str[offset + 1];
	int		index;

	index = 0;
	while (offset > index)
	{
		str[index] = c;
		index++;
	}
	str[index] = 0;
	write(1, str, offset);
}

char		*set_filename(char *s1, char *s2, int add_sep)
{
	int		i;
	int		j;
	char	*str;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = (char*)malloc(sizeof(char) * (i + j + 2));
	ft_memset(str, 0, sizeof(char) * (i + j + 2));
	ft_strcat(str, s1);
	ft_strcat(str + i, s2);
	if (add_sep && *(s2 + j) != '/')
		*(str + i + j) = '/';
	*(str + i + j + add_sep) = 0;
	return (str);
}

void		build_offset(int *off, t_print *p)
{
	int		offset;

	offset = p->len_nlink;
	if (off[0] < offset)
		off[0] = offset;
	offset = p->len_usr;
	if (off[1] < offset)
		off[1] = offset;
	offset = p->len_grp;
	if (off[2] < offset)
		off[2] = offset;
	offset = p->len_size;
	if (off[3] < offset)
		off[3] = offset;
	offset = p->len_ma;
	if (off[4] < offset)
		off[4] = offset;
	offset = p->len_mi;
	if (off[5] < offset)
		off[5] = offset;
}

int			prepare(t_args *a, t_file *root)
{
	int		*off;
	int		cmpt;

	off = a->offset;
	cmpt = 0;
	ft_memset(off, 0, sizeof(int) * 6);
	while (root)
	{
		build_offset(off, &root->p);
		cmpt += root->s.st_blocks;
		root = root->next;
	}
	return (cmpt);
}

void		parcours(t_args *a, t_file *f)
{
	int		blks;

	blks = prepare(a, f);
	if (f && a->mask & PRINT_TOTAL)
	{
		write(1, "total ", 6);
		ft_putnbr_fd(blks, 1);
		write(1, "\n", 1);
	}
	while (f)
	{
		print_stat(a, &f->p);
		f = f->next;
	}
}
