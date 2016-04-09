#include "miniterm.h"

char	**process_setenv(char **env, char *domain, char *value, int overwrite)
{
	char	*tmp;
	int		len;

	len = ft_strlen(domain);
	while (*env && ft_strncmp(*env, domain, len))
		env++;
	if (*env)
	{
		if (!overwrite)
		{
			tmp = ft_strdup(*env);
			free(*env);
			*env = ft_strjoin(tmp, value);
			free(tmp);
		}
		else
		{
			tmp = ft_strjoin(domain, value);
			free(*env);
			*env = tmp;
		}
	}
	return (env);
}

int		setenvt(t_term *t, char *cmd)
{
	char	*domain;
	char	*value;
	int		overwrite;
	char	**args;

	args = ft_strsplit(cmd, ' ');
	overwrite = 0;
	domain = args[0];
	value = args[1];
	if (!domain)
		print_error(t, "setenv", "domain needed");
	else if (!value)
		print_error(t, "setenv", "value needed");
	else
	{
		if (args[3] && !ft_strcmp(args[3], "-o"))
			overwrite = 1;
		else
		{
			print_error(t, "setenv", "bad argument");
			return (1);
		}
		t->env = process_setenv(t->env, domain, value, overwrite);
	}
	overwrite = 0;
	while (args[overwrite])
		free(args[overwrite++]);
	free(args);
	return (1);
}