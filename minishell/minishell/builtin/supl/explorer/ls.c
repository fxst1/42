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

int			navig_input(int *page, int *y, int n)
{
	int	in;

	in = 0;
	read(0, &in, 4);
	//printf("%d\n", in);
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
	else if (in == MSHELL_KEYLEFT)
		(*page)--;
	else if (in == MSHELL_KEYRIGHT)
		(*page)++;
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

void		print_choose(int cur, int mode)
{
	write(1, "\033[u", 3);
	if (S_IFDIR == (mode & S_IFMT) || S_IFLNK == (mode & S_IFMT))
	{
		if (cur % 2)
			write(1, "\033[7m[list]\033[0m [out]", 20);
		else
			write(1, "[list] \033[7m[out]\033[0m", 20);
	}
	else
	{
		if (cur % 2)
			write(1, "\033[7m[read]\033[0m [out]", 20);
		else
			write(1, "[read] \033[7m[out]\033[0m", 20);
	}
}

int			setoutput(int x_max, char *path, t_file *f)
{
	int			in;
	int			cur;

	cur = 1;
	in = 0;
	write(1, "\033[u", 3);
	print_at(x_max);
	write(1, "\033[s", 3);
	print_choose(1, f->s.st_mode);
	while (in != '\n' && in != '\e')
	{
		read(0, &in, 4);
		if (in == MSHELL_KEYRIGHT || in == MSHELL_KEYLEFT)
			cur++;
		print_choose(cur, f->s.st_mode);
		if (in != '\n' && in != '\e')
			in = 0;
	}
	if (in == '\n')
	{
		write(1, "\033c", 2);
		write(1, path, ft_strlen(path));
		write(1, f->p.name, f->p.len_name);
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

void			navigation(t_term *t, char **path, t_args *arg, t_file *f, int n)
{
	int		in;
	int		y;
	int		new_page;
	char	*n_path;

	y = 0;
	write(1, "\033c", 2);
	write(1, "\033[s", 3);
	arg->page = 0;
	arg->pages = get_nbfile(f) / (t->ws.ws_row - 2);
	parcours(&t->ws, arg, f);
	write(1, "\033[u", 3);
	print_at(1);
	new_page = 0;
	while ((in = navig_input(&arg->page, &y, n)) != '\e')
	{
		if (y >= (t->ws.ws_row - 2))
		{
			arg->page++;
			y = 0;
		}
		if (arg->page >= arg->pages)
			arg->page = 0;
		else if (arg->page < 0)
			arg->page = arg->pages - 1;
		if (in == '\n' || in == 127)
		{
			if (in == '\n' && (S_IFDIR == (get_file(f, y)->s.st_mode & S_IFMT) || S_IFLNK == (get_file(f, y)->s.st_mode & S_IFMT)))
				n_path = set_filename(*path, get_file(f, y)->p.name , 1);
			else if (in == 127)
				n_path = set_filename(*path, ".." , 1);
			del(&f);
			f = ft_open(arg, n_path);
			arg->page = 0;
			arg->pages = get_nbfile(f) / (t->ws.ws_row - 2);
			new_page = 0;
			write(1, "\033c", 2);
			write(1, "\033[s", 3);
			parcours(&t->ws, arg, f);
			n = get_nbfile(f);
			y = 0;
			free(*path);
			*path = n_path;
		}
		else if (in == ' ')
		{
			if (setoutput(t->ws.ws_row - 1, *path, get_file(f, y)))
			{
				del(&f);
				ft_memdel((void**)path);
				return ;
			}
			new_page = -1;
		}
		if (new_page != arg->page)
		{
			new_page = arg->page;
			write(1, "\033c", 2);
			write(1, "\033[s", 3);
			parcours(&t->ws, arg, f);
		}
		write(1, "\033[u", 3);
		print_at(y + 1);
	}
	//if (in == ' ')
		//setoutput()
	del(&f);
	ft_memdel((void**)path);
	write(1, "\033c", 2);
}

int				ls(t_term *t, t_args *arg)
{
	char	*path;
	char	*new_path;
	t_file	*root;

	path = arg->path;
	new_path = set_filename("\0", path, 1);
	root = ft_open(arg, new_path);
	navigation(t, &new_path, arg, root, get_nbfile(root));
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

	free(arg->colormap);
	return (arg->ret);
}
