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

void	call_laucher(t_term *t, char **cmd, int *ok)
{
	char	**args_a;
	char	**args_b;
	int		len;

	len = 0;
	t->act = last_index(t->his) + 1;
	while (cmd[len])
	{
		cmd[len] = build_cmd(t->env, cmd[len], t->last_return);
		if (cmd[len + 1] && *cmd[len + 1] == '|')
		{
			args_a = ft_strsplit(cmd[len], ' ');
			args_b = ft_strsplit(cmd[len + 2], ' ');
			if (!call_builtins(t, args_a, ok) && !call_builtins(t, args_b, ok))
				start_prgm_pipe(t, args_a, args_b);
			delete_tab(args_a);
			delete_tab(args_b);
			len += 2;
		}
		if ((*cmd[len] != ';' && *cmd[len] != '>' && *cmd[len] != '<'
			&&  *cmd[len] != '|' && *cmd[len] != '&')
			&& *cmd[len])
		{
			args_a = ft_strsplit(cmd[len], ' ');
			if (!call_builtins(t, args_a, ok))
				start_prgm(t, args_a);
			delete_tab(args_a);
		}
		len++;
	}
	delete_tab(cmd);
}

int		term_main(t_term *t)
{
	int		ok;
	char	**cmd;

	ok = 1;
	cmd = NULL;
	print_prompt(t);
	new_cmdline(t);
	while (ok && get_cmd_line(t, &t->line, 0))
	{
		t->line.buffer = ft_strtrim(t->line.buffer);
		cmd = ft_strsplit_cmd(t->line.buffer);
		call_laucher(t, cmd, &ok);
		if (ok)
		{
			historic(t, HIST_ADD, &t->line.buffer, &ok);
			print_prompt(t);
		}
		new_cmdline(t);
		tcsetattr(0, 0, &t->it);
	}
	free(t->line.buffer);
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
	t.act = 0;
	ret = 0;
	signal(SIGINT, &catch_signal);
	signal(SIGABRT, &catch_signal);
	ioctl(1, TIOCGWINSZ, &t.ws);
	signal(SIGWINCH, &catch_signal);
	if ((ret = 0) == 0)
	{
		reset_shlvl(&t);
		argv[1] = "SHLVL";
		argv[1] = "SHLVL";
		t.argv = argv;
		term_main(&t);
		ft_putstr(RESET);
	}
	stop(&t);
	return (ret);
}
