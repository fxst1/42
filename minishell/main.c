#include <term.h>

int	start_prgm(t_term *t, char *cmd)
{
	char	**argv;
	pid_t	child_pid;
	pid_t	tpid;
	int		index;
	int		child_status;

	argv = ft_strsplit(cmd, ' ');
	child_pid = fork();
	tpid = 0;
	if(child_pid == 0)
	{
		execve(argv[0], argv, t->env);
		ft_printf("@term: %s: command not found\n", argv[0]);
		exit(0);
	}
	else
	{
		while(tpid != child_pid)
		{
			tpid = wait(&child_status);
			if(tpid != child_pid)
				ft_printf("%d\n", tpid);
		}
	}
	index = 0;
	while (argv[index])
		free(argv[index++]);
	free(argv);
	return (child_status);
}

int	term_main(t_term *t)
{
	int		ok;
	char	*cmd;

	ok = 1;
	cmd = NULL;
	print_prompt(t);
	while (ok && get_next_line(0, &cmd) > 0)
	{
		if (!ft_strcmp(cmd, "exit"))
			ok = 0;
		else if (!ft_strncmp(cmd, "cd ", (*(cmd + 2) ? 3 : 2)))
		{
			if (chdir((*(cmd + 3) ? cmd + 3 : DEF_PATH)))
				ft_printf("@term: cd: No such file or directory\n", cmd + 3);
			else
				getcwd(t->dirpath, sizeof(char)  * 1024);
		}
		else if (!ft_strcmp(cmd, "env"))
			print_env(t->env);
		else if (!ft_strncmp(cmd, "setenv ", 7))
			t->env = ft_setenv(t->env, cmd + 7);
		else if (!ft_strncmp(cmd, "unsetenv ", 9))
			t->env = ft_unsetenv(t->env, cmd + 9);
		else
			start_prgm(t, cmd);
		if (ok)
			print_prompt(t);
		free(cmd);
		cmd = NULL;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_term	t;

	initterm(&t, 240, 20, "@term");
	t.env = init_env(env);
	t.argc = argc;
	t.argv = argv;
	t.path = init_path(env);
	term_main(&t);
	stop(&t);
	ft_printf(RESET);
	return (0);
}