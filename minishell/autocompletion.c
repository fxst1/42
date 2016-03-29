
t_list	*find_file(char *filen, char *cmd)
{
	t_list		*file;
	DIR		*d;
	struct dirent	*entry;

	file = NULL;
	d = opendir(filen);
	while ((entry = readdir(d)))
	{
		if (!ft_strncmp(entry->d_name, cmd, ft_strlen(cmd)))
		{
			ft_lstadd(
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
		if ((f = find_file(tmp, cmd)))
			ft_lstadd(&l, f);
		ft_memset(tmp, 0, len);
		t++;
	}
	free(tmp);
	return (l);
}

char	*do_autocomplet(char *d, char **path, char *cmd, int *ok)
{
	t_list	*l;
	t_list	*t;
	int		prnt;

	l = find_path(path, cmd);
	t = l;
	prnt = 1;
	if (l && !l->next)
	{
		prnt = 0;
		if (!ft_strcmp(cmd, l->content))
			*ok = 1;
		else
			*ok = 2;
		free(cmd);
		cmd = ft_strdup(l->content);
	}
	//ft_printf("(%d) %s\n", ft_lstsize(l), cmd);
	while (l)
	{
		if (prnt)
			printf("%s\n", (char*)l->content);
		l = l->next;
	}
	ft_lstdel(&t, &ft_lstfree);
	return (cmd);
}