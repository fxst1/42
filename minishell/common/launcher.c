/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 22:00:39 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/14 22:00:43 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniterm.h>

int		test_access(t_term *t, char *name)
{
	DIR	*d;
	int	value;

	value = 0;
	if (!(d = opendir(name)))
	{
		if (!access(name, F_OK) && access(name, X_OK))
		{
			print_error(t, name, "Permission denied");
			value = 1;
		}
	}
	else
		closedir(d);
	return (value);
}

int		start_prgm_redirect(t_term *t, char **argv, char *filename)
{
	int		fd;
	pid_t	pid;

	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		return (-1);
	tcsetattr(0, 0, &t->backup);
	ft_putstr_fd("\033[0m", 1);
	argv[0] = (*t->env) ? find_in_path(t->env, &argv[0]) : argv[0];
	if ((pid = fork()) == -1)
	{
		close(fd);
	}
	else if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		execve(argv[0], argv, t->env);
	}
	close(fd);
	wait(NULL);
	tcsetattr(0, 0, &t->it);
	return (0);
}


int		start_prgm_pipe(t_term *t, char **argv_a, char **argv_b)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (-1);
	tcsetattr(0, 0, &t->backup);
	ft_putstr_fd("\033[0m", 1);
	argv_b[0] = (*t->env) ? find_in_path(t->env, &argv_b[0]) : argv_b[0];
	argv_a[0] = (*t->env) ? find_in_path(t->env, &argv_a[0]) : argv_a[0];
	if ((pid = fork()) == -1)
	{
		close(pipefd[1]);
		close(pipefd[0]);
	}
	else if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		execve(argv_a[0], argv_a, t->env);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	wait(NULL);
	execve(argv_b[0], argv_b, t->env);
	tcsetattr(0, 0, &t->it);
	}
	return (0);
}

int		start_prgm(t_term *t, char **argv)
{
	pid_t	child_pid;
	pid_t	tpid;
	int		child_status;

	tcsetattr(0, 0, &t->backup);
	argv[0] = (*t->env) ? find_in_path(t->env, &argv[0]) : argv[0];
	ft_putstr_fd("\033[0m", 1);
	if (test_access(t, argv[0]))
		return (0);
	child_pid = fork();
	tpid = 0;
	t->reading = 0;
	if (child_pid == 0)
	{
		execve(argv[0], argv, t->env);
		print_error(t, argv[0], "Command not found");
		//exit(1);
	}
	else
		while (tpid != child_pid)
		{
			tpid = wait(&child_status);
		}
	tcsetattr(0, 0, &t->it);
	t->last_return = WIFEXITED(child_status);
	return (child_status);
}

int		call_builtins(t_term *t, char **cmd, int *ok)
{
	t->last_return = 0;
	if (!ft_strcmp(*cmd, "exit"))
		*ok = 0;
	else if (!ft_strcmp(*cmd, "cd"))
		t->last_return = cd(t, cmd);
	else if (!ft_strcmp(*cmd, "env"))
		t->last_return = env(t, cmd);
	else if (!ft_strcmp(*cmd, "setenv"))
		t->last_return = setenvt(t, cmd);
	else if (!ft_strcmp(*cmd, "unsetenv"))
		t->last_return = unsetenvt(t, cmd);
	else if (!ft_strcmp(*cmd, "echo"))
		ft_putendl(*(cmd + 1) ? *(cmd + 1) : " ");
	else if (!ft_strcmp("reset", *cmd))
		ft_putstr(CLEAR);
	else if (!ft_strcmp(*cmd, "cfg"))
		builtin_cfg(t, cmd);
	else if (!ft_strcmp(*cmd, "explorer"))
		explorer(t, cmd);
	else
		return (0);
	return (1);
}
