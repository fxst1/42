#include <miniterm.h>

static char	**resetenv(char **env, char *del_dom)
{
	char	**copy;
	int		index;
	int		n;

	index = 0;
	n = 0;
	while (env[index])
		index++;	
	copy = (char**)malloc(sizeof(char*) * (index + 1));
	index = 0;
	while (env[index])
	{
		if (ft_strncmp(env[index], del_dom, ft_strlen(del_dom)))
			copy[n++] = ft_strdup(env[index]);
		free(env[index]);
		index++;
	}
	copy[n] = NULL;
	free(env);
	env = NULL;
	return (copy);
}

static int		init_mask(t_term *t, char *cmd, char **dom)
{
	char	**args;
	int		index;

	index = 0;
	args = ft_strsplit(cmd, ' ');
	*dom = args[0];
	if (!*dom)
		print_error(t, "unsetenv", "domain needed");
	else
		*dom = ft_strdup(args[0]);
	while (args[index])
		free(args[index++]);
	free(args);
	return (1);
}

int		unsetenvt(t_term *t, char *cmd)
{
	char	*domain;

	if (init_mask(t, cmd, &domain) >= 0)
	{
		t->env = resetenv(t->env, domain);
		free(domain);
		return (0);
	}
	return (1);
}