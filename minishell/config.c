/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 00:21:35 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 00:21:37 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniterm.h>

void	usage()
{
	ft_putstr("\033[1;38;5;1m<==================================== \033[4mMINISHELL\033[24m ====================================>\033[0m\n");
	ft_putstr("\n     \033[38;5;189m<-------------------------  c o m m a n d s  ------------------------->\033[0m\n");
	ft_putstr("\n --name=<str>\n\tset minishell name (\x1b[1;4;38;5;69m@minishell\x1b[0m by def)\n");
	ft_putstr(" --color-<text/back>-<cmd/prt/exe>=<ansi str format>\n\t");
	ft_putstr("text / back : set foreground / background color\n\t");
	ft_putstr("cmd / prt / exe : command input / prompt / execution (except builtins...)\n");
	ft_putstr(" --log=<filename> choose an command log (minishell.log by def)\n");
	ft_putstr(" --config=<filename> choose a configuration file (minishell.cfg by def)\n");
	ft_putstr(" --help print this \"helpful...\" help\n");
	ft_putstr("\n     \033[38;5;189m<-------------------------  b u l l t i n s  ------------------------->\033[0m\n\n");
	ft_putstr("\n cd <- / path>\tchange directory (-: switch PWD and OLDPWD)\n");
	ft_putstr(" env\t\tprint environement\n");
	ft_putstr(" setenv\t\tadd a new value to environnment\n");
	ft_putstr(" unsetenv\tdel a value from environnment\n");
	ft_putstr("\n\033[1;38;5;1m<===================================================================================>\033[0m\n\n");
}

int		init_args(t_term *t, char **argv)
{
	while (*argv)
	{
		if (!ft_strncmp(*argv, "--name=", 7))
		{
			free(t->prompt);
			t->prompt = ft_strdup((*argv) + 7);
		}
		else if (!ft_strncmp(*argv, "--color-back-cmd=", 13))
		{
			free(t->cmd_back);
			t->cmd_back = ft_strdup((*argv) + 13);
		}
		else if (!ft_strncmp(*argv, "--color-back-exe=", 13))
		{
			free(t->exe_back);
			t->exe_back = ft_strdup((*argv) + 13);
		}
		else if (!ft_strncmp(*argv, "--color-back-prt=", 13))
		{
			free(t->pt_back);
			t->pt_back = ft_strdup((*argv) + 13);
		}
		else if (!ft_strncmp(*argv, "--color-text-cmd=", 13))
		{
			free(t->cmd_txt);
			t->cmd_txt = ft_strdup((*argv) + 13);
		}
		else if (!ft_strncmp(*argv, "--color-text-exe=", 13))
		{
			free(t->exe_txt);
			t->exe_txt = ft_strdup((*argv) + 13);
		}
		else if (!ft_strncmp(*argv, "--color-text-prt=", 13))
		{
			free(t->pt_txt);
			t->pt_txt = ft_strdup((*argv) + 13);
		}
		else if (!ft_strncmp(*argv, "--log=", 6))
		{
			free(t->log);
			t->log = ft_strdup((*argv) + 6);
		}
		else if (!ft_strncmp(*argv, "--config=", 9))
		{
			free(t->cfg);
			t->cfg = ft_strdup((*argv) + 9);
		}
		else if (!ft_strcmp(*argv, "--help"))
		{
			usage();
			return (2);
		}
		else
			return (1);
		argv++;
	}
	return (0);
}

void	save_cfg(t_term *t)
{
	int	fd;
	int	index;

	if ((fd = open(t->cfg, O_RDWR | O_CREAT, 0666)) >= 0)
	{
		ft_putendl_fd(t->prompt, fd);
		ft_putendl_fd(t->cmd_txt, fd);
		ft_putendl_fd(t->cmd_back, fd);
		ft_putendl_fd(t->exe_txt, fd);
		ft_putendl_fd(t->exe_back, fd);
		ft_putendl_fd(t->pt_txt, fd);
		ft_putendl_fd(t->pt_back, fd);
		ft_putendl_fd(t->log, fd);
		index = 0;
		while (t->env[index])
			ft_putendl_fd(t->env[index++], fd);
	}
	close(fd);
}

void	load_cfg(t_term *t)
{
	int		fd;
	int		index;

	if ((fd = open(t->cfg, O_WRONLY)) >= 0)
	{
		stop(t);
		get_next_line(fd, &t->prompt);
		get_next_line(fd, &t->cmd_txt);
		get_next_line(fd, &t->cmd_back);
		get_next_line(fd, &t->exe_txt);
		get_next_line(fd, &t->exe_back);
		get_next_line(fd, &t->pt_txt);
		get_next_line(fd, &t->pt_back);
		get_next_line(fd, &t->log);
		t->env = (char**)malloc(sizeof(char*) * 32);
		index = 0;
		while (get_next_line(fd, &t->env[index]) > 0)
			index++;
		t->env[index] = NULL;
	}
	close(fd);
}