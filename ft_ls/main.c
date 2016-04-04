/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 02:00:08 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 02:00:10 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

static void		set_option_short_bis(t_args *tmp, char argv)
{
	if (argv == 'n')
		tmp->set |= NUM_ID;
	else if (argv == 'S')
		tmp->sort |= SIZE;
	else if (argv == 'h')
		tmp->ret = 3;
	else
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putchar_fd(argv, 2);
		ft_putstr_fd("\n", 2);
		tmp->ret = 2;
	}
}

void			set_options_short(t_args *tmp, char *argv)
{
	while (*argv && !tmp->ret)
	{
		if (*argv == 'l')
			tmp->mask |= LIST;
		else if (*argv == 'R')
		{
			tmp->deep = ft_isdigit(*(argv + 1)) ? ft_atoi(++argv) : -1;
			tmp->mask |= RECURSIF;
		}
		else if (*argv == 'r')
			tmp->mask |= REVERSE;
		else if (*argv == 'a')
			tmp->mask |= ALL;
		else if (*argv == 't')
			tmp->sort |= MTIME;
		else if (*argv == 'G')
			tmp->mask |= COLOR;
		else if (*argv == 'e')
			tmp->set |= STOP_ERR;
		else
			set_option_short_bis(tmp, *argv);
		argv++;
	}
}

void			set_options_long(t_args *tmp, char *argv)
{
	if (!(ft_strcmp(argv, "--numerical-id")))
		tmp->set |= NUM_ID;
	else if (!ft_strcmp(argv, "--error"))
		tmp->set |= STOP_ERR;
	else if (!ft_strcmp(argv, "--help"))
		tmp->ret = 3;
	else if (!ft_strncmp("--color=", argv, 8))
	{
		tmp->mask |= COLOR;
		if ((tmp->colormap = init_extension_map_from_file(argv + 8)))
			tmp->set |= INIT_COLOR;
	}
	else
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putendl_fd(argv, 2);
		tmp->ret = 2;
	}
}

void			init_args(t_args *arg, int *n, char **argv, int *l)
{
	first_of_all(arg, *n);
	*n = 0;
	while (argv[*l] && !arg->ret && argv[*l][0] == '-')
	{
		if (argv[*l][1] == '-')
			set_options_long(arg, argv[*l]);
		else
			set_options_short(arg, argv[*l] + 1);
		(*l)++;
	}
	while (!arg->ret && argv[*l])
	{
		arg->path[(*n)++] = ft_strdup(argv[*l]);
		(*l)++;
	}
	if (*n == 0)
		arg->path[(*n)++] = ft_strdup(".");
	arg->path[*n] = NULL;
	ft_strsort(arg->path, !REVERSE_ORDER);
}

int				main(int argc, char **argv, char **env)
{
	t_args	tmp;
	int		l;

	l = 1;
	init_args(&tmp, &argc, argv, &l);
	if (!tmp.ret)
	{
		if (!tmp.colormap && tmp.mask & COLOR)
			tmp.colormap = init_extension_map(env);
		if (tmp.mask & COLOR)
			tmp.typemap = init_typemap(env);
		file_errors(&tmp, tmp.path);
		ls(&tmp, argc);
	}
	else if (tmp.ret == 2)
		print_help(argv[0]);
	else
	{
		usage();
		tmp.ret = 0;
	}
	return (tmp.ret);
}
