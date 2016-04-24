#include <miniterm.h>

void		load_his(t_term *t, int fd)
{
	int		i;
	int		n;

	n = 0;
	//delete_tab(t->his);
	read(fd, &n, sizeof(int));
	//write(fd, "\n", 1);
	read(fd, &t->n_cmds, sizeof(int));
	//write(fd, "\n", 1);
	n++;
	t->his = (char**)malloc(sizeof(char*) * t->n_cmds);
	i = 0;
	while (i < n && get_next_line(fd, &t->his[i]))
	{
		printf("(%d)<%s)\n", i, t->his[i]);
		i++;
		t->his[i] = NULL;
	}
	while (i < n)
		t->his[i++] = NULL;
}

void		load_env(t_term *t, int fd)
{
	int		i;
	int		n;

	n = 0;
	//delete_tab(t->env);
	read(fd, &n, sizeof(int));
	//write(fd, "\n", 1);
	n++;
	t->env = (char**)malloc(sizeof(char*) * n);
	i = 0;
	while (i < n && get_next_line(fd, &t->env[i]))
		i++;
	while (i < n)
		t->env[i++] = NULL;
}

void		load_colors(t_term *t, int fd, int mask)
{
	(void)mask;
//	if (mask & MSHELL_MASK_COLOR_BGPROMT)
	{
//		ft_memdel((void**)&t->pt_back);
		//t->pt_back = read_line(fd);
		get_next_line(fd, &t->pt_back);
//		printf("%s\n", t->pt_back);
	}
//	if (mask & MSHELL_MASK_COLOR_FGPROMT)
	{
//		ft_memdel((void**)&t->pt_txt);
		get_next_line(fd, &t->pt_txt);
	}
//	if (mask & MSHELL_MASK_COLOR_BGCMD)
	{
//		ft_memdel((void**)&t->cmd_back);
		get_next_line(fd, &t->cmd_back);
	}
//	if (mask & MSHELL_MASK_COLOR_FGCMD)
	{
//		ft_memdel((void**)&t->cmd_txt);
		get_next_line(fd, &t->cmd_txt);
	}
//	if (mask & MSHELL_MASK_COLOR_BGEXE)
	{
//		ft_memdel((void**)&t->exe_back);
		get_next_line(fd, &t->exe_back);
	}
//	if (mask & MSHELL_MASK_COLOR_FGEXE)
	{
//		ft_memdel((void**)&t->exe_txt);
		get_next_line(fd, &t->exe_txt);
	}
//	if (mask & MSHELL_MASK_COLOR_BGNAME)
	{
//		ft_memdel((void**)&t->name_back);
		get_next_line(fd, &t->name_back);
	}
//	if (mask & MSHELL_MASK_COLOR_FGNAME)
	{
//		ft_memdel((void**)&t->name_txt);
		get_next_line(fd, &t->name_txt);
	}
}

void		load_term(t_term *t, char *fn, int mask)
{
	int	fd;
	char	useless[16];

	if ((fd = open(fn, O_WRONLY)) >= 0)
	{
		read(fd, (char*)useless, 16);
		load_colors(t, fd, mask);
		load_his(t, fd);
		load_env(t, fd);
		write(1, "load !\n", 1);
	}
	else
		print_error(t, "cfg_load", "Cannot open save file");
	close(fd);
}