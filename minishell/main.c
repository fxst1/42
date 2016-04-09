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

#include <miniterm.h>

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
	ft_putansi_str(t->exe_txt, 1);
	ft_putansi_str(t->exe_back, 1);
	if (child_pid == 0)
	{
		execve(argv[0], argv, t->env);
		ft_putansi_str(t->name_txt, 2);
		ft_putansi_str(t->name_back, 2);
		ft_putstr_fd(t->prompt, 2);
		ft_putstr(": \033[0m\033[38;5;196m");
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(": command not found\033[0m\n", 2);
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
		cd(t, cmd);
	else if (!ft_strcmp(cmd, "env "))
		env(t, cmd + 3);
	else if (!ft_strncmp(cmd, "setenv ", 7))
		setenv(t, cmd + 7);
	else if (!ft_strncmp(cmd, "unsetenv ", 9))
		t->env = ft_unsetenv(t, t->env, cmd + 9);
	else if (!ft_strcmp("reset", cmd))
		ft_putstr(CLEAR);
	else if (!ft_strcmp(cmd, "setenv") || !ft_strcmp(cmd, "unsetenv"))
	{
		ft_putansi_str(t->name_back, 2);
		ft_putansi_str(t->name_txt, 2);
		ft_putstr_fd(t->prompt, 2);
		ft_putstr_fd(": \033[38;5;196m", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": bad arguments\033[0m\n", 2);
	}
	else
		return (0);
	return (1);
}

int		term_main(t_term *t)
{
	int		ok;
	char	*line;
	char	**cmd;

	ok = 1;
	cmd = NULL;
	print_prompt(t);
	while (ok && get_next_line(0, &line) > 0)
	{
		cmd = ft_build_cmd(t->env, line);
		while (*cmd)
		{
			if ((**cmd != ';' && **cmd != '>' && **cmd != '<'
				&& **cmd != '|' && **cmd != '&')
				&& **cmd)
			{
				if (!call_builtins(t, *cmd, &ok))
					start_prgm(t, *cmd);
			}
			free(*cmd);
			*cmd = NULL;
			cmd++;
		}
		free(line);
		line = NULL;
		if (ok)
			print_prompt(t);
	}
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	t_term	t;
	int		ret;

	//ft_putstr(CLEAR);
	initterm(&t);
	if ((ret = init_args(&t, argv + 1)) == 0)
	{
		t.env = init_env(env);
		t.argc = argc;
		t.argv = argv;
		if (*env)
			t.path = init_path(env);
		else
			t.path = NULL;
		term_main(&t);
		ft_putstr(RESET);
	}
	stop(&t);
	return (ret);
}
