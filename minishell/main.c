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
	char	**args;
	int		len;

	len = 0;
	t->act = last_index(t->his) + 1;
	while (cmd[len])
	{
		cmd[len] = build_cmd(t->env, cmd[len], t->last_return);
		if ((*cmd[len] != ';' && *cmd[len] != '>' && *cmd[len] != '<'
			&& *cmd[len] != '|' && *cmd[len] != '&')
			&& *cmd[len])
		{
			args = ft_strsplit(cmd[len], ' ');
			if (!call_builtins(t, args, ok))
				start_prgm(t, args);
			delete_tab(args);
		}
		free(cmd[len]);
		cmd[len] = NULL;
		len++;
	}
}

int		term_main(t_term *t)
{
	int		ok;
	char	*line;
	char	**cmd;

	ok = 1;
	cmd = NULL;
	print_prompt(t);
	line = ft_strnew(1024);
	while (ok && get_cmd_line(t, &line, 0))
	{
		line = ft_strreplace(line, '\n', 0);
		cmd = ft_strsplit_cmd(line);
		call_laucher(t, cmd, &ok);
		free(cmd);
		if (ok)
		{
			historic(t, HIST_ADD, &line, &ok);
			print_prompt(t);
		}
		free(line);
		line = ft_strnew(1024);
		tcsetattr(0, 0, &t->it);
	}
	free(line);
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
//	signal(SIGINT, &catch_signal);
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
