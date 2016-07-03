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


t_list	*prepare_cmd_pipe(char *cpy)
{
	t_list	*lst;
	char	*word;

	lst = NULL;
	while (*cpy)
	{
		if (*cpy == '>' || *cpy == '<')
		{
			*cpy = 0;
			return (lst);
		}
		if (*cpy == '|')
		{
			word = ft_strword(++cpy);

			free(word);
		}
		cpy++;
	}
	return (lst);
}

void	call_laucher_pipe(t_term *t, char **cmd, int *ok)
{
	int		len;
	t_list	*ptr;
	char	*cpy;
	t_list	*lst;

	len = 0;
	t->act = last_index(t->his) + 1;
	while (cmd[len])
	{
		cpy = ft_strdup(cmd[len]);
		t->fd[0] = 0;
		t->fd[1] = 1;
		if ((cpy = build_cmd(t->env, cpy, t->last_return)))
		{
			initialize_redirections(t);
			build_redirection(&t->redirs, cpy);
			lst = prepare_cmd_pipe(cpy);
			while (lst)
			{
				ptr = lst->next;
				args = ft_strsplit(cpy, ' ');
				if (!call_builtins(t, lst->content, ok))
					start_prgm(t, lst->content);
				delete_tab(lst->content);
				free(lst);
				lst = ptr;
			}
			end_redirections(&t->redirs);
		}
		free(cpy);
		len++;
	}
	delete_tab(cmd);
}

int		start_prgm(t_term *t, char **argv)
{
	pid_t	child_pid;
	int		child_status;

	child_status = -1;
	tcsetattr(0, 0, &t->backup);
	argv[0] = (*t->env) ? find_in_path(t->env, &argv[0]) : argv[0];
	ft_putstr_fd("\033[0m", 1);
	if (test_access(t, argv[0]))
		return (0);
	t->reading = 0;
	if ((child_pid = fork()) == 0)
	{
		do_redirections(t);
		execve(argv[0], argv, t->env);
		print_error(t, argv[0], "Command not found");
		exit(1);
	}
	else if (child_pid == -1)
		print_error(t, t->prompt, "Fork error");
	wait(NULL);
	tcsetattr(0, 0, &t->it);
	t->last_return = WIFEXITED(child_status);
	return (child_status);
}

int		call_builtins(t_term *t, char **cmd, int *ok)
{
	if (!*cmd)
		return (1);
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
