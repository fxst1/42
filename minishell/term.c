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

void	initterm(t_term *t)
{
	if (t)
	{
		getcwd(t->dirpath, sizeof(char) * 1024);
		t->pt_back = ft_strdup("48;5;0");
		t->pt_txt = ft_strdup("1;38;5;87");
		t->cmd_back = ft_strdup("48;5;0");
		t->cmd_txt = ft_strdup("38;5;28");
		t->exe_back = ft_strdup("48;5;0");
		t->exe_txt = ft_strdup("38;5;15");
		t->name_back = ft_strdup("48;5;0");
		t->name_txt = ft_strdup("1;38;5;69");
		t->cfg = ft_strdup("minishell.cfg");
		t->prompt = ft_strdup("@minishell");
		t->log = ft_strdup("minishell.log");
		t->env = NULL;
		t->path = NULL;
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
	if (t->env)
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
}
