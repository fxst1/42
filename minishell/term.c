#include <term.h>

void	initterm(t_term *t, int cb, int ct, char *prompt)
{
	if (t)
	{
		getcwd(t->dirpath, sizeof(char)  * 1024);	
		t->back = cb;
		t->txt = ct;
		t->prompt = prompt;
		t->log = "log_minishell.log";
		t->fd = open(t->log, O_RDWR | O_CREAT, 0666);
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
		ft_printf("%K", t->back);
	if (t->txt)
		ft_printf("%k", t->txt);
	ft_printf("%s, %s $>"RESET, t->prompt, t->dirpath);
}

void	stop(t_term *t)
{
	int	n;

	n = 0;
	while (t->path[n])
		free(t->path[n++]);
	free(t->path);
}


