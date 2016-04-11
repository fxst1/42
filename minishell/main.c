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

t_list				*find(char *dn, char *cmd, t_list **file)
{
	DIR		*d;
	t_dir	*e;
	t_list	*new;

	if ((d = opendir(dn)))
	{
		while ((e = readdir(d)))
		{
			if (!ft_strcmp(cmd, e->d_name))
			{
				new = ft_lstnew(e->d_name, 2 + ft_strlen(e->d_name));
				ft_lstadd(file, new);
			}
		}
		closedir(d);
	}
	return (*file);
}

char	*find_in_path(char **env, char **cmd)
{
	char	**path;
	char	*tmp;
	int		index;
	t_list	*files;

	files = NULL;
	index = 0;
	tmp = ft_getenv(env, "PATH=");
	path = ft_strsplit(tmp, ':');
	tmp = NULL;
	while (path[index])
	{
		if (!tmp && find(path[index], *cmd, &files))
			tmp = path[index];
		index++;
	}
	if (files && !files->next)
	{
		free(*cmd);
		*cmd = ft_strnew(
			ft_strlen(tmp) + files->content_size + 1);
		ft_strcpy(*cmd, tmp);
		ft_strcat(*cmd, "/");
		ft_strncat(*cmd, (char*)files->content, files->content_size);
		free(files->content);
		free(files);
	}
	else
	{
		t_list *sw;
		while (files)
		{
			sw = files->next;
			ft_putnstr(files->content, files->content_size);
			write(1, "\n", 1);
			free(files->content);
			free(files);
			files = sw;
		}
	}
	index = 0;
	while (path[index])
		free(path[index++]);
	free(path);
	return (*cmd);
}

int		start_prgm(t_term *t, char *cmd)
{
	char	**argv;
	pid_t	child_pid;
	pid_t	tpid;
	int		index;
	int		child_status;

	argv = ft_strsplit(cmd, ' ');
	argv[0] = find_in_path(t->env, &argv[0]);
	child_pid = fork();
	tpid = 0;
//	ft_putansi_str(t->exe_txt, 1);
//	ft_putansi_str(t->exe_back, 1);
	ft_putstr_fd("\e[0m", 1);
	if (child_pid == 0)
	{
		execve(argv[0], argv, t->env);
		print_error(t, argv[0], "command not found");
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
		t->last_return = cd(t, cmd);
	else if (!ft_strncmp(cmd, "env ", (*(cmd + 3) ? 4 : 3)))
		t->last_return = env(t, cmd + 3);
	else if (!ft_strncmp(cmd, "setenv ", 7))
		t->last_return = setenvt(t, cmd + 7);
	else if (!ft_strncmp(cmd, "unsetenv ", 9))
		t->env = ft_unsetenv(t, t->env, cmd + 9);
	else if (!ft_strcmp("reset", cmd))
	{
		t->last_return = 0;
		ft_putstr(CLEAR);
	}
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
	int		len;

	ok = 1;
	cmd = NULL;
	print_prompt(t);
	while (ok && get_next_line(0, &line) > 0)
	{
		len = 0;
		cmd = ft_build_cmd(t->env, line);
		while (cmd[len])
		{
			if ((*cmd[len] != ';' && *cmd[len] != '>' && *cmd[len] != '<'
				&& *cmd[len] != '|' && *cmd[len] != '&')
				&& *cmd[len])
			{
				if (!call_builtins(t, cmd[len], &ok))
					start_prgm(t, cmd[len]);
			}
			free(cmd[len]);
			cmd[len] = NULL;
			len++;
		}
		free(cmd);
		free(line);
		line = NULL;
		if (ok)
			print_prompt(t);
	}
	free(line);
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
