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

char		*set_filename(char *s1, char *s2, int add_sep)
{
	int		i;
	int		j;
	char	*str;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = (char*)malloc(sizeof(char) * (i + j + 1 + add_sep));
	*str = 0;
	ft_strcat(str, s1);
	ft_strcat(str + i, s2);
	if (add_sep && *(str + i + j - 1) != '/')
		*(str + i + j) = '/';
	*(str + i + j + add_sep) = 0;
	return (str);
}

void		build_offset(int *off, t_print *p)
{
	int		offset;

	offset = ft_strlen(p->nlink);
	if (off[0] < offset)
		off[0] = offset;
	offset = ft_strlen(p->usr);
	if (off[1] < offset)
		off[1] = offset;
	offset = ft_strlen(p->grp);
	if (off[2] < offset)
		off[2] = offset;
	offset = ft_strlen(p->size);
	if (off[3] < offset)
		off[3] = offset;	
}

int			compt_blocks(t_args *a, t_file *f)
{
	int	n;

	n = 0;
	while (f)
	{
		if (a->mask & ALL || (!(a->mask & ALL) && f->name[0] != '.'))
			n += f->dat.st_blocks;
		f = f->next;
	}
	return (n);
}

t_print	init_print(char *name, struct stat *s, int sort)
{
	t_print			p;
	void			*ptr;

	p.alloc = 0;
	p.mode = s->st_mode;
	p.nlink = ft_itoa(s->st_nlink);
	if ((ptr = (struct passwd*)getpwuid(s->st_uid)))
		p.usr = ((struct passwd*)ptr)->pw_name;
	else
	{
		p.usr = ft_itoa(s->st_uid);
		p.alloc |= 1;
	}
	if ((ptr = (struct group*)getgrgid(s->st_gid)))
		p.grp = ((struct group*)ptr)->gr_name;
	else
	{
		p.grp = ft_itoa(s->st_gid);
		p.alloc |= 2;
	}
	p.tim = (sort & CTIME) ? s->st_ctime : s->st_mtime;
	p.size = s->st_size;
	p.name = name;
# if (OS_FT == MAC_OS)

	p.sec = (sort & CTIME) ? s->st_ctimespec : s->st_mtimespec;

# endif

	return (p);
}

void		parcours(char *path, t_args *a, t_file *f)
{
	t_print	p;

	build_offset(a, f);
	if (a->mask & LIST && f && a->set & PRINT_TOTAL)
	{
		write(1, "total ", 6);
		ft_putnbr_fd(compt_blocks(a, f), 1);
		write(1, "\n", 1);
	}
	while (f)
	{
		if (a->mask & LIST)
		{
			p = init_print(f, a);
			print_stat(path, a, &p);
		}
		else
		{
			ft_putstr_fd(f->name, 1);
			if (f->next)
				write(1, "\e[0m\n", 6);
			else
				write(1, "\e[0m\t", 6);
		}
		f = f->next;
	}
}
