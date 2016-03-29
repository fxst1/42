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

#include <term.h>

void	initterm(t_term *t, int cb, int ct, char *prompt)
{
	if (t)
	{
		getcwd(t->dirpath, sizeof(char) * 1024);
		t->back = cb;
		t->txt = ct;
		t->prompt = prompt;
		t->log = "log_minishell.log";
		t->fd = open(t->log, O_RDWR | O_CREAT, 0666);
		if (cb)
		{
			ft_putstr("\x1B[48;5;");
			ft_putnbr(cb);
			ft_putchar('m');
		}
		if (ct)
		{
			ft_putstr("\x1B[38;5;");
			ft_putnbr(ct);
			ft_putchar('m');
		}
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
	if (t->back)
	{
		ft_putstr("\033[48;5;");
		ft_putnbr(t->back);
		ft_putchar('m');
	}
	if (t->txt)
	{
		ft_putstr("\033[38;5;");
		ft_putnbr(t->txt);
		ft_putchar('m');
	}
	ft_putstr(t->prompt);
	ft_putstr(": ");
	ft_putstr(t->dirpath);
	ft_putstr("$>");
	ft_putstr(RESET);
}

void	stop(t_term *t)
{
	int	n;

	n = 0;
	while (t->path[n])
		free(t->path[n++]);
	free(t->path);
}
