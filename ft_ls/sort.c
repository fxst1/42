/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 03:23:32 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 03:23:33 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

# if (OS_FT == MAC_OS)
int		test_sort_alph(t_file *swap, t_file *tmp, t_args *a)
{
	return ((((!a->sort) || ((a->sort & SIZE) &&
			(swap->dat.st_size == tmp->dat.st_size)) ||
			((a->sort & MTIME) && (swap->dat.st_mtime == tmp->dat.st_mtime &&
			swap->dat.st_mtimespec.tv_nsec == tmp->dat.st_mtimespec.tv_nsec)))
			&&
			((!(a->mask & REVERSE) && ft_strcmp(swap->name, tmp->name) > 0) ||
			(a->mask & REVERSE && ft_strcmp(swap->name, tmp->name) < 0))));
}

int		test_sort_mask(t_file *swap, t_file *tmp, t_args *a)
{
	return (((
		((a->sort & SIZE) && ((!(a->mask & REVERSE) &&
		swap->dat.st_size < tmp->dat.st_size) ||
		(a->mask & REVERSE && swap->dat.st_size > tmp->dat.st_size))))
		||
		((a->sort & MTIME) && (
		((!(a->mask & REVERSE) && ((swap->dat.st_mtime < tmp->dat.st_mtime) ||
		(swap->dat.st_mtime == tmp->dat.st_mtime &&
		swap->dat.st_mtimespec.tv_nsec < tmp->dat.st_mtimespec.tv_nsec))) ||
		((a->mask & REVERSE) && ((swap->dat.st_mtime > tmp->dat.st_mtime) ||
		(swap->dat.st_mtime == tmp->dat.st_mtime &&
		swap->dat.st_mtimespec.tv_nsec > tmp->dat.st_mtimespec.tv_nsec))))))));
}

# else

int		test_sort_alph(t_file *swap, t_file *tmp, t_args *a)
{
	return ((((!a->sort) || ((a->sort & SIZE) &&
			(swap->dat.st_size == tmp->dat.st_size)) ||
			((a->sort & MTIME) && (swap->dat.st_mtime == tmp->dat.st_mtime)))
			&&
			((!(a->mask & REVERSE) && ft_strcmp(swap->name, tmp->name) > 0) ||
			(a->mask & REVERSE && ft_strcmp(swap->name, tmp->name) < 0))));
}

int		test_sort_mask(t_file *swap, t_file *tmp, t_args *a)
{
	return (((
		((a->sort & SIZE) && ((!(a->mask & REVERSE) &&
		swap->dat.st_size < tmp->dat.st_size) ||
		(a->mask & REVERSE && swap->dat.st_size > tmp->dat.st_size))))
		||
		((a->sort & MTIME) && (
		((!(a->mask & REVERSE) && ((swap->dat.st_mtime < tmp->dat.st_mtime) ||
		(swap->dat.st_mtime == tmp->dat.st_mtime))) ||
		((a->mask & REVERSE) && ((swap->dat.st_mtime > tmp->dat.st_mtime) ||
		(swap->dat.st_mtime == tmp->dat.st_mtime))))))));
}

#endif
void	sort_files(t_args *a, t_file *root)
{
	t_file	*swap;
	t_file	*tmp;
	t_file	*d;

	while (root)
	{
		tmp = root;
		while (tmp)
		{
			swap = root;
			if (test_sort_mask(swap, tmp, a))
			{
				ft_swapn(&swap->dat, &tmp->dat, sizeof(struct stat));
				ft_swap(&swap->name, &tmp->name);
				ft_swap(&swap->type, &tmp->type);
				d = tmp->dir;
				tmp->dir = swap->dir;
				swap->dir = d;
			}
			sort_files(a, tmp->dir);
			tmp = tmp->next;
		}
		root = root->next;
	}
}

void	sort_filesalph(t_args *a, t_file *root)
{
	t_file	*swap;
	t_file	*tmp;
	t_file	*d;

	while (root)
	{
		tmp = root;
		while (tmp)
		{
			swap = root;
			if (test_sort_alph(swap, tmp, a))
			{
				ft_swapn(&swap->dat, &tmp->dat, sizeof(struct stat));
				ft_swap(&swap->name, &tmp->name);
				ft_swap(&swap->type, &tmp->type);
				d = tmp->dir;
				tmp->dir = swap->dir;
				swap->dir = d;
			}
			sort_filesalph(a, tmp->dir);
			tmp = tmp->next;
		}
		root = root->next;
	}
}
