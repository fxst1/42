#include "term.h"

void	initterm(t_term *t, int cb, int ct, char *prompt)
{
	if (t)
	{
		getcwd(t->dirpath, sizeof(char)  * 1024);	
		t->back = cb;
		t->txt = ct;
		t->prompt = prompt;
		if (cb)
			ft_printf("%K", cb);
		if (ct)
			ft_printf("%k", ct);
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

void	print_prompt(t_term *t)
{
	if (t->back)
		ft_printf("%K", t->back);
	if (t->txt)
		ft_printf("%k", t->txt);
	ft_printf("%s, %s $ "RESET, t->prompt, t->dirpath);
}

t_list	*find_file(char *filen, char *cmd)
{
	t_list		*file;
	DIR		*d;
	struct dirent	*entry;

	file = NULL;
	ft_printf("find_file %s", filen);
	d = opendir(filen);
	while ((entry = readdir(d)))
	{
		ft_printf("\tcmp: %s x %s\n", cmd, entry->d_name);
		if (!ft_strncmp(entry->d_name, cmd, ft_strlen(cmd + 1)))
		{
			ft_printf("OK\n");
			ft_lstadd_begin(
				&file,
				ft_lstnew(entry->d_name,
				sizeof(char) * ft_strlen(entry->d_name) + 1)
				);
		}
	}
	closedir(d);
	return (file);
}

t_list	*find_path(char **t, char *cmd)
{
	int		len;
	char	*tmp;
	t_list	*l;
	t_list	*f;


	len = 1025 + ft_strlen(cmd);
	tmp = ft_strnew(len);
	l = NULL;
	while (*t)
	{
		f = NULL;
		ft_strcpy(tmp, *t);
		ft_strcat(tmp, "/");
		if ( (f = find_file(tmp, cmd)) )
			ft_lstadd_begin(&l, f);
		ft_printf("(%d)\n", ft_lstsize(l));
		ft_memset(tmp, 0, len);
		t++;
	}
	free(tmp);
	return (l);
}

char	*do_autocomplet(char *d, char **path, char *cmd, int s)
{
	ft_printf("auto completion %s\n", cmd);
	t_list	*l;
	t_list	*t;

	l = find_path(path, cmd);
	t = l;
	if (l && !l->next)
	{
		ft_strcat(cmd, "/");
		ft_strcat(cmd, l->content);
	}
	ft_printf("(%d) %s\n", ft_lstsize(l), cmd);
	while (l)
	{
		if (l->content)
			printf("%s\n", (char*)l->content);
		l = l->next;
	}
	ft_lstdel(&t, &ft_lstfree);
	return (cmd);
}

int	term_main(t_term *t)
{
	int	ok;
	int	s;
	char	*cmd;

	ok = 1;
	s = 0;
	cmd = ft_strnew(1024);
	print_prompt(t);
	while (ok && read(0, cmd, 1024) > 0)
	{
		if (s)
			print_prompt(t);
		if (!ft_strcmp(cmd, "exit\n"))
			ok = 0;
		else if (1)
			cmd = do_autocomplet(t->dirpath, t->path, cmd, s);
		else
		{

		}
		ft_printf("cmd: %s", cmd);
		s++;
	}
	free(cmd);
	return (0);
}

void	stop(t_term *t)
{
	int	n;

	n = 0;
	while (t->path[n])
		free(t->path[n++]);
	free(t->path);
}

int	main(int argc, char **argv, char **env)
{
	t_term	t;

	initterm(&t, 0, 20, "@term");
	t.env = env;
	t.argc = argc;
	t.argv = argv;
	t.path = init_path(env);
	term_main(&t);
	stop(&t);
	ft_printf(RESET);
	return (0);
}
