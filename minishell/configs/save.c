void		save_his(t_term *t, int fd)
{
	int	i;

	i = 0;
	while (t->his[i])
		i++;
	write(fd, &i, sizeof(int));
	write(fd, &t->n_cmds, sizeof(int));
	//printf("<%d   %d>\n", i, t->n_cmds);
	i = 0;
	while (t->his[i])
	{
		write(fd, t->his[i], ft_strlen(t->his[i]));
		write(fd, "\n", 1);
		i++;
	}
}

void		save_env(t_term *t, int fd)
{
	int	i;

	i = 0;
	while (t->env[i])
		i++;
	write(fd, &i, sizeof(int));
	//write(fd, "\n", 1);
	i = 0;
	while (t->env[i])
	{
		write(fd, t->env[i], ft_strlen(t->env[i]));
		write(fd, "\n", 1);
		i++;
	}
}

void		save_colors(t_term *t, int fd)
{
	write(fd, t->pt_back, ft_strlen(t->pt_back));
	write(fd, "\n", 1);
	write(fd, t->pt_txt, ft_strlen(t->pt_txt));
	write(fd, "\n", 1);
	write(fd, t->cmd_back, ft_strlen(t->cmd_back));
	write(fd, "\n", 1);
	write(fd, t->cmd_txt, ft_strlen(t->cmd_txt));
	write(fd, "\n", 1);
	write(fd, t->exe_back, ft_strlen(t->exe_back));
	write(fd, "\n", 1);
	write(fd, t->exe_txt, ft_strlen(t->exe_txt));
	write(fd, "\n", 1);
	write(fd, t->name_back, ft_strlen(t->name_back));
	write(fd, "\n", 1);
	write(fd, t->name_txt, ft_strlen(t->name_txt));
	write(fd, "\n", 1);
}

void		save_term(t_term *t, char *fn)
{
	int	fd;

	if ((fd = open(fn, O_CREAT | O_RDWR, 0666)) > 0)
	{
		write(fd, "minishell _ cfg\n", 16);
		save_colors(t, fd);
		save_his(t, fd);
		save_env(t, fd);
		write(fd, "\n", 1);
	//	print_data(t);
		printf("???????????????\n");
	}
	else
		print_error(t, "cfg_save", "Cannot open/create save file");
	close(fd);
}