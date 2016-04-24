/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 01:46:07 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/08 16:20:11 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <explorer.h>

void			print_maps(t_args *a, t_print *f)
{
	char	*ret;

	if (a->mask & COLOR)
		print_color(a->typemap, f->mode);
	if (a->colormap)
	{
		ret = ft_strrchr(f->name, '.');
		ret = ft_mapget(a->colormap, ret ? ret : f->name, &ft_strcmp);
		if (ret)
			ft_putansi_str(ret, 1);
	}
}

int			navig_input(int *y, int n)
{
	int	in;

	in = 0;
	read(0, &in, 4);
	if (in == MSHELL_KEYUP)
	{
		write(1, "\033[2D  \033[2D", 10);
		(*y)--;
	}
	else if (in == MSHELL_KEYDOWN)
	{
		write(1, "\033[2D  \033[2D", 10);
		(*y)++;
	}
	if (*y >= n)
		*y = 0;
	else if (*y < 0)
		*y = n - 1;
	return (in);
}

int				get_nbfile(t_file *root)
{
	int	n;

	n = 0;
	while (root)
	{
		n++;
		root = root->next;
	}
	return (n);
}

t_file			*get_file(t_file *root, int n)
{
	while (root && n--)
	{
		root = root->next;
	}
	return (root);
}

void			print_at(int n)
{
	while (n--)
		write(1, "\033[B", 3);
	write(1, "|>", 2);
}

void			navigation(char *path, t_args *arg, t_file *f, int n)
{
	int		in;
	int		y;
	char	*n_path;

	y = 0;
	write(1, "\033c", 2);
	write(1, "\033[s", 6);
	parcours(arg, f);
	write(1, "\033[u", 3);
	print_at(1);
	while ((in = navig_input(&y, n))!= '\e')
	{
		if (in == '\n')
		{
			n_path = set_filename(path, get_file(f, y)->p.name, 1);
			del(&f);
			f = ft_open(arg, n_path);
			write(1, "\033c", 2);
			parcours(arg, f);
			n = get_nbfile(f);
			y = 0;
			free(path);
			path = n_path;
		}
		else if (in == 127)
		{
			n_path = set_filename(path, "..", 1);
			del(&f);
			f = ft_open(arg, n_path);
			write(1, "\033c", 2);
			parcours(arg, f);
			n = get_nbfile(f);
			y = 0;
			free(path);
			path = n_path;
		}
		write(1, "\033[u", 3);
		print_at(y + 1);
	}
	write(1, "\033c", 2);
}

int				ls(t_args *arg)
{
	char	*path;
	char	*new_path;
	t_file	*root;

	path = arg->path;
	new_path = set_filename("\0", path, 1);
	root = ft_open(arg, new_path);
	navigation(new_path, arg, root, get_nbfile(root));
	return (0);
}

int				stop_ls(t_args *arg)
{
	int	n;

	n = 0;
	if (arg->typemap)
		while (arg->typemap[n])
			free(arg->typemap[n++]);
	free(arg->typemap);
	if (arg->colormap)
		ft_mapdel(&arg->colormap, 1, &free, &free);
	return (arg->ret);
}
