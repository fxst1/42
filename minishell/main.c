/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 00:21:21 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 00:21:22 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>

char	*get_home(t_term *t, char **env)
{
	while (*env && ft_strncmp(*env, "HOME=", 5))
		env++;
	if (*env)
	{
		*env += 5;
		return (*env);
	}
	return (t->dirpath);
}

int		start_prgm(t_term *t, char *cmd)
{
	char	**argv;
	pid_t	child_pid;
	pid_t	tpid;
	int		index;
	int		child_status;

	argv = ft_strsplit(cmd, ' ');
	child_pid = fork();
	tpid = 0;
	if (child_pid == 0)
	{
		execve(argv[0], argv, t->env);
		ft_putstr_fd("@term: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(0);
	}
	else
		while (tpid != child_pid)
			tpid = wait(&child_status);
	index = 0;
	while (argv[index])
		free(argv[index++]);
	free(argv);
	return (child_status);
}

int		call_builtins(t_term *t, char *cmd, int *ok)
{
	if (!ft_strcmp(cmd, "exit"))
		*ok = 0;
	else if (!ft_strncmp(cmd, "cd ", (*(cmd + 2) ? 3 : 2)))
	{
		if (chdir(ft_strnword(cmd) == 1 ? get_home(t, t->env) : cmd + 3))
			ft_putstr_fd("@term: cd: No such file or directory\n", 2);
		else
			getcwd(t->dirpath, sizeof(char) * 1024);
	}
	else if (!ft_strcmp(cmd, "env"))
		print_env(t->env);
	else if (!ft_strncmp(cmd, "setenv ", 7))
		t->env = ft_setenv(t->env, cmd + 7);
	else if (!ft_strncmp(cmd, "unsetenv ", 9))
		t->env = ft_unsetenv(t->env, cmd + 9);
	else if (!ft_strcmp("reset", cmd))
		ft_putstr("\033c");
	else
		return (0);
	return (1);
}

int		term_main(t_term *t)
{
	int		ok;
	char	*cmd;

	ok = 1;
	cmd = NULL;
	print_prompt(t);
	while (ok && get_next_line(0, &cmd) > 0)
	{
		if (!call_builtins(t, cmd, &ok))
			start_prgm(t, cmd);
		if (ok)
			print_prompt(t);
		free(cmd);
		cmd = NULL;
	}
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	t_term	t;

	ft_putstr("\033c");
	initterm(&t, 0, 20, "@term");
	t.env = init_env(env);
	t.argc = argc;
	t.argv = argv;
	t.path = init_path(env);
	term_main(&t);
	stop(&t);
	ft_putstr(RESET);
	return (0);
}
