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

void	initterm(t_term *t, char **env)
{
	int index;

	index = 0;
	getcwd(t->dirpath, sizeof(char) * 1024);
	t->pt_back = ft_strdup("48;5");
	t->pt_txt = ft_strdup("1;38;5;87");
	t->cmd_back = ft_strdup("48;5");
	t->cmd_txt = ft_strdup("38;5;15");
	t->exe_back = ft_strdup("48;5");
	t->exe_txt = ft_strdup("38;5;15");
	t->name_back = ft_strdup("48;5");
	t->name_txt = ft_strdup("1;38;5;69");
	t->prompt = ft_strdup("@minishell");
	t->n_cmds = 100;
	t->his = (char**)malloc(sizeof(char*) * t->n_cmds);
	t->env = init_env(env);
	t->last_return = 0;
	t->fds[0] = 1;
	t->fds[1] = 0;
	tcgetattr(0, &t->it);
	tcgetattr(0, &t->backup);
	set_rawmode(&t->it);
	tcsetattr(0, 0, &t->it);
	while (index < 100)
		t->his[index++] = NULL;
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
#include <time.h>

void	print_atime()
{
	time_t	act;
	char	*s;

	act = time(0);
	s = ctime(&act);
	s += 11;
	*(s + 5) = 0;
	write(1, "\033[31m[", 6);
	ft_putstr(s);
	write(1, "]\033[0m", 5);
}

void	print_error(t_term *t, char *it, char *error)
{
	ft_putansi_str(t->name_txt, 2);
	ft_putansi_str(t->name_back, 2);
	ft_putstr_fd(t->prompt, 2);
	ft_putstr_fd(": \033[0m\033[1;38;5;196m", 2);
	ft_putstr_fd(it, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\033[0m\n", 2);
}

void	print_prompt(t_term *t)
{
	ft_putstr(RESET);
	print_atime();
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
	free(t->prompt);
	free(t->cmd_txt);
	free(t->cmd_back);
	free(t->pt_txt);
	free(t->pt_back);
	free(t->exe_txt);
	free(t->exe_back);
	free(t->name_txt);
	free(t->name_back);
	delete_tab(t->env);
	delete_tab(t->his);
	tcsetattr(0, 0, &t->backup);
}
