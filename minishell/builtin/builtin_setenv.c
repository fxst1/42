#include <miniterm.h>

static char	**resetenv(char **env, char *new_dom, char *val)
{
	char	**copy;
	int		index;

	index = 0;
	while (env[index])
		index++;	
	copy = (char**)malloc(sizeof(char*) * (index + 2));
	index = 0;
	while (env[index])
	{
		copy[index] = ft_strdup(env[index]);
		free(env[index]);
		index++;
	}
	copy[index] = ft_strnew(ft_strlen(new_dom) + ft_strlen(val) + 1);
	ft_strcpy(copy[index], new_dom);
	ft_strcat(copy[index], "=");
	ft_strcat(copy[index], val);
	copy[index + 1] = NULL;
	free(env);
	env = NULL;
	return (copy);
}

static char	**process_setenv(char **env, char *domain, char *value, int overwrite)
{
	char	*tmp;
	int		index;

	index = 0;
	while (env[index] && ft_strncmp(env[index], domain, ft_strclen(env[index], '=')))
		index++;
	if (env[index])
	{
		if (!overwrite)
		{
			tmp = ft_strnew(ft_strlen(env[index]) + 1);
			ft_strcpy(tmp, env[index]);
			ft_strcat(tmp, ":");
			free(env[index]);
			env[index] = ft_strjoin(tmp, value);
			free(tmp);
		}
		else
		{
			tmp = ft_strnew(ft_strlen(domain) + 1);
			ft_strcpy(tmp, domain);
			ft_strcat(tmp, "=");
			free(env[index]);
			env[index] = ft_strjoin(tmp, value);
			free(tmp);
		}
	}
	else
		env = resetenv(env, domain, value);
	return (env);
}

static int		init_mask(t_term *t, char *cmd, char **dom, char **value)
{
	char	**args;
	int		index;
	int		mask;

	mask = -1;
	index = 0;
	args = ft_strsplit(cmd, ' ');
	*dom = args[0];
	*value = args[1];
	if (!*dom)
		print_error(t, "setenv", "domain needed");
	else if (!*value)
		print_error(t, "setenv", "value needed");
	else
	{
		*dom = ft_strdup(args[0]);
		*value = ft_strdup(args[1]);
		if (args[2] && !ft_strcmp("-o", args[2]))
			mask = 1;
		else
			mask = 0;
	}
	while (args[index])
		free(args[index++]);
	free(args);
	return (mask);
}

int		setenvt(t_term *t, char *cmd)
{
	char	*domain;
	char	*value;
	int		overwrite;

	if ((overwrite = init_mask(t, cmd, &domain, &value)) >= 0)
	{
		t->env = process_setenv(t->env, domain, value, overwrite);
		free(domain);
		free(value);
		return (0);
	}
	return (1);
}