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
		ft_fprintf(2, "ft_ls: illegal option -- %c\n", argv);
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
			tmp->set |= SHOW_ERR;
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
		tmp->set |= SHOW_ERR;
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
		ft_fprintf(2, "ft_ls: illegal option -- %s\n", argv);
		tmp->ret = 2;
	}
}

void			init_args(t_args *arg, int *n, char **argv, int *l)
{
	first_of_all(arg, *n);
	*n = 0;
	while (argv[*l] && !arg->ret)
	{
		if (argv[*l][0] == '-')
		{
			if (argv[*l][1] == '-')
				set_options_long(arg, argv[*l]);
			else
				set_options_short(arg, argv[*l] + 1);
		}
		else
		{
			arg->path[*n] = ft_strdup(argv[*l]);
			arg->path[++(*n)] = NULL;
		}
		(*l)++;
	}
	if (*n == 0)
		(*n)++;
	ft_strsort(arg->path, !REVERSE_ORDER);
}

int				main(int argc, char **argv)
{
	t_args	tmp;
	int		l;

	l = 1;
	tmp.colormap = NULL;
	init_args(&tmp, &argc, argv, &l);
	if (!tmp.ret)
	{
		if (!tmp.colormap && tmp.mask & COLOR)
			tmp.colormap = init_extension_map();
		file_errors(&tmp, tmp.path);
		ls(&tmp, argc);
	}
	else if (tmp.ret == 2)
		ft_fprintf(2, "Try '%s -h' option for more information.\n", argv[0]);
	else
	{
		usage();
		tmp.ret = 0;
	}
	stop_ls(&tmp, argc);
	return (tmp.ret);
}
