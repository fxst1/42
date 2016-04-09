/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fcts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 19:42:34 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/07 19:42:36 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		addfile(t_file **f, t_file *add, int rev)
{
	t_file	*tmp;
	t_file	*last;
	char	*name;

	tmp = *f;
	last = NULL;
	if (tmp && (name = add->p.name))
	{
		while (tmp && ft_strcmp(tmp->p.name, name) > 0 == !rev)
		{
			last = tmp;
			tmp = tmp->next;
		}
		add->next = tmp;
		if (last)
			last->next = add;
		else
			*f = add;
	}
	else
		*f = add;
}

void		addfile_size(t_file **f, t_file *add, int rev)
{
	t_file	*tmp;
	t_file	*last;
	int		ret;
	int		size;
	char	*name;

	tmp = *f;
	last = NULL;
	size = add->s.st_size;
	if (tmp && (name = add->p.name))
	{
		while (tmp && ((ret = tmp->s.st_size - size) > 0 != !rev ||
			(!ret && ft_strcmp(tmp->p.name, name) > 0 == !rev)))
		{
			last = tmp;
			tmp = tmp->next;
		}
		add->next = tmp;
		if (last)
			last->next = add;
		else
			*f = add;
	}
	else
		*f = add;
}

int			is_time(time_t a, time_t b, struct timespec *t1,
				struct timespec *t2)
{
	if (b > a)
		return (1);
	else if (a == b)
		return (t2->tv_nsec - t1->tv_nsec);
	return (-1);
}

void		addfile_time(t_file **f, t_file *add, int rev)
{
	t_file	*tmp;
	t_file	*last;
	int		ret;
	t_print	*p;

	tmp = *f;
	last = NULL;
	p = &add->p;
	if (tmp)
	{
		while (tmp && ((((ret = is_time(tmp->p.tim, p->tim,
			&tmp->p.sec, &p->sec)) > 0) == !rev) ||
			(!ret && ft_strcmp(tmp->p.name, add->p.name) > 0 != rev)))
		{
			last = tmp;
			tmp = tmp->next;
		}
		add->next = tmp;
		if (last)
			last->next = add;
		else
			*f = add;
	}
	else
		*f = add;
}
