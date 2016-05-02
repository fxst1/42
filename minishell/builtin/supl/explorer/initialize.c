/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/08 02:35:38 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/08 02:35:39 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <explorer.h>

void		delete_print(t_print *p)
{
	free(p->nlink);
	p->nlink = NULL;
	free(p->size);
	p->size = NULL;
	if (p->alloc & 1)
		free(p->usr);
	if (p->alloc & 2)
		free(p->grp);
	p->usr = NULL;
	p->grp = NULL;
	free(p->maj);
	free(p->min);
	p->maj = NULL;
	p->min = NULL;
}

void		init_time(t_print *p, int sort, t_stat *s)
{
	(void)p;
	(void)s;
	if (sort & CTIME)
	{
//		p->tim = s->st_birthtime;
	//	p->sec = s->st_birthtimespec;
	}
	else
	{
		p->tim = s->st_mtime;
	//	p->sec = s->st_mtimespec;
	}
}

void		init_print_sizes(t_print *p, char *name, t_stat *s)
{
	p->len_usr = ft_strlen(p->usr);
	p->len_grp = ft_strlen(p->grp);
	p->len_size = ft_strlen(p->size);
	p->len_nlink = ft_strlen(p->nlink);
	p->len_name = ft_strlen(name);
	if (S_IFCHR == (S_IFMT & s->st_mode) || S_IFBLK == (S_IFMT & s->st_mode))
	{
		p->maj = ft_itoa(major(s->st_rdev));
		p->min = ft_itoa(minor(s->st_rdev));
		p->len_ma = ft_strlen(p->maj);
		p->len_mi = ft_strlen(p->min);
	}
	else
	{
		p->maj = NULL;
		p->min = NULL;
		p->len_ma = 0;
		p->len_mi = 0;
	}
	p->acl = 0;
	p->attr = 0;
}

void		init_print(char *name, t_stat *s, int sort, t_print *p)
{
	void			*ptr;

	p->alloc = 0;
	p->mode = s->st_mode;
	p->nlink = ft_itoa(s->st_nlink);
	if (!(sort & NUM_ID) && (ptr = (struct passwd*)getpwuid(s->st_uid)))
		p->usr = ((struct passwd*)ptr)->pw_name;
	else
	{
		p->usr = ft_itoa(s->st_uid);
		p->alloc |= 1;
	}
	if (!(sort & NUM_ID) && (ptr = (struct group*)getgrgid(s->st_gid)))
		p->grp = ((struct group*)ptr)->gr_name;
	else
	{
		p->grp = ft_itoa(s->st_gid);
		p->alloc |= 2;
	}
	p->size = ft_itoa(s->st_size);
	p->name = ft_strdup(name);
	init_time(p, sort, s);
	init_print_sizes(p, name, s);
}
