/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 22:38:32 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/14 22:38:36 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniterm.h>

static int		print_environnment(t_term *t)
{
	char	**env;

	env = t->env;
	while (*env)
	{
		ft_putendl_fd(*env, 1);
		env++;
	}
	return (0);
}

static int		start_bis(t_term *t, char **argv)
{
	pid_t	child_pid;
	pid_t	tpid;
	int		child_status;
	char	*empty;

	empty = NULL;
	argv[0] = (*t->env) ? find_in_path(t->env, &argv[0]) : argv[0];
	child_pid = fork();
	tpid = 0;
	ft_putstr_fd("\033[0m", 1);
	if (child_pid == 0)
	{
		execve(argv[0], argv, &empty);
		print_error(t, argv[0], "command not found");
		exit(0);
	}
	else
		while (tpid != child_pid)
		{
			tpid = wait(&child_status);
		}
	t->last_return = WIFEXITED(child_status);
	return (1);
}

int				env(t_term *t, char **args)
{
	int		index;
	int		mask;

	mask = 0;
	index = 1;
	while (args[index])
	{
		if (!ft_strcmp(args[index], "-i") && args[index + 1])
			mask = start_bis(t, &args[index + 1]);
		else if (!ft_strcmp(args[index], "-u"))
		{
			mask = 2;
			unsetenvt(t, &args[index]);
		}
		else if (!mask)
		{
			print_error(t, "env", "bad argument");
			return (1);
		}
		index++;
	}
	if (!mask)
		print_environnment(t);
	return (0);
}
