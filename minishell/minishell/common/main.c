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

void	reset_shlvl(t_term *t)
{
	char	*ret;
	char	*arg[5];
	int		value;

	value = 0;
	if ((ret = ft_getenv(t->env, "SHLVL=")))
	{
		while (ret[value] && ft_isdigit(ret[value]))
			value++;
		if (!ret[value])
			value = ft_atoi(ret);
	}
	arg[0] = NULL;
	arg[1] = "SHLVL";
	arg[2] = ft_itoa(value + 1);
	arg[3] = NULL;
	setenvt(t, arg);
	free(arg[2]);
}

void	prepare_cmd(char *cpy)
{
	while (*cpy)
	{
		if (*cpy == '>' || *cpy == '<')
		{
			*cpy = 0;
			return ;
		}
		cpy++;
	}
}

void	call_laucher(t_term *t, char **cmd, int *ok)
{
	int		len;
	char	**args;
	char	*cpy;

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
			prepare_cmd(cpy);
			args = ft_strsplit(cpy, ' ');
			if (!call_builtins(t, args, ok))
				start_prgm(t, args);
			delete_tab(args);
			end_redirections(&t->redirs);
		}
		free(cpy);
		len++;
	}
	delete_tab(cmd);
}

int		term_main(t_term *t)
{
	int		ok;
	char	**cmd;
	char	*tmp;

	ok = 1;
	cmd = NULL;
	print_prompt(t);
	new_cmdline(t);
	while (ok && get_cmd_line(t, &t->line, 0))
	{
		tmp = ft_strtrim(t->line.buffer);
		cmd = ft_strsplit(tmp, ';');
		free(tmp);
		call_laucher(t, cmd, &ok);
		if (ok)
		{
			historic(t, HIST_ADD, &t->line.buffer, &ok);
			print_prompt(t);
		}
		free(t->line.buffer);
		new_cmdline(t);
		tcsetattr(0, 0, &t->it);
	}
	free(t->line.buffer);
	t->line.buffer = NULL;
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	t_term	t;
	int		ret;

	(void)argc;
	(void)argv;
	initterm(&t, env);
	get_miniterm(&t);
	t.cfg = 0;
	t.act = 0;
	ret = 0;
	signal(SIGINT, &catch_signal);
	signal(SIGABRT, &catch_signal);
	ioctl(1, TIOCGWINSZ, &t.ws);
	signal(SIGWINCH, &catch_signal);
	if ((ret = 0) == 0)
	{
		reset_shlvl(&t);
		t.argv = argv;
		term_main(&t);
		ft_putstr(RESET);
	}
	stop(&t);
	return (ret);
}
