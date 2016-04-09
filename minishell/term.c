/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 00:21:27 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 00:21:29 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniterm.h>

void	set_rawmode(struct termios *termios_p)
{
	termios_p->c_iflag |= 0;
	termios_p->c_oflag |= 0;
	termios_p->c_lflag &= ~(ICANON | ECHO);
	termios_p->c_cc[VMIN] = 1;
	termios_p->c_cc[VTIME] = 0;
}

void	initterm(t_term *t)
{
	if (t)
	{
		getcwd(t->dirpath, sizeof(char) * 1024);
		t->pt_back = ft_strdup("48;5");
		t->pt_txt = ft_strdup("1;38;5;87");
		t->cmd_back = ft_strdup("48;5");
		t->cmd_txt = ft_strdup("38;5;15");
		t->exe_back = ft_strdup("48;5");
		t->exe_txt = ft_strdup("38;5;15");
		t->name_back = ft_strdup("48;5");
		t->name_txt = ft_strdup("1;38;5;69");
		t->cfg = ft_strdup("minishell.cfg");
		t->prompt = ft_strdup("@minishell");
		t->log = ft_strdup("minishell.log");
		t->env = NULL;
		t->path = NULL;
//		tcgetattr(0, &t->backup);
//		tcgetattr(0, &t->it);
//		set_rawmode(&t->it);
//		tcsetattr(0, TCSANOW, &t->it);
	}
}

char	**init_path(char **env)
{
	char	**t;

	while (*env && ft_strncmp(*env, "PATH=", 5))
		env++;
	*env += 5;
	t = ft_strsplit(*env, ':');
	return (t);
}

char	**init_env(char **env)
{
	int		index;
	char	**copy;

	index = 0;
	while (env[index])
		index++;
	copy = (char**)malloc(sizeof(char*) * (index + 1));
	index = 0;
	while (env[index])
	{
		copy[index] = ft_strdup(env[index]);
		index++;
	}
	copy[index] = NULL;
	return (copy);
}

void	print_error(t_term *t, char *it, char *error)
{
	ft_putansi_str(t->name_txt, 2);
	ft_putansi_str(t->name_back, 2);
	ft_putstr_fd(t->prompt, 2);
	ft_putstr_fd(": \033[0m\033[38;5;196m", 2);
	ft_putstr_fd(it, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\033[0m\n", 2);
}

void	print_prompt(t_term *t)
{
	ft_putstr(RESET);
	ft_putansi_str(t->name_back, 1);
	ft_putansi_str(t->name_txt, 1);
	ft_putstr(t->prompt);
	ft_putstr(": ");
	ft_putansi_str(t->pt_back, 1);
	ft_putansi_str(t->pt_txt, 1);
	ft_putstr(t->dirpath);
	ft_putstr("$>");
	ft_putansi_str(t->cmd_back, 1);
	ft_putansi_str(t->cmd_txt, 1);
}

void	stop(t_term *t)
{
	int	n;

	n = 0;
	free(t->prompt);
	free(t->log);
	free(t->cmd_txt);
	free(t->cmd_back);
	free(t->pt_txt);
	free(t->pt_back);
	free(t->exe_txt);
	free(t->exe_back);
	free(t->name_txt);
	free(t->name_back);
	if (t->path)
	{
		while (t->path[n])
			free(t->path[n++]);
		free(t->path);
	}
	if (t->env)
	{
		n = 0;
		while (t->env[n])
			free(t->env[n++]);
		free(t->env);
	}
//	tcsetattr(0, TCSANOW, &t->backup);
}
