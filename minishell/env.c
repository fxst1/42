#include <term.h>

void	print_env(char **env)
{
	int	index;

	index = 0;
	while (env[index])
	{
		ft_putendl(env[index]);
		index++;
	}
}

char	**ft_unsetenv(char	**env, char *name)
{
	int		index;
	char	*str;

	index = 0;
	while (env[index] &&
		ft_strncmp(env[index], name, ft_strlen(name)))	
		index++;
	if (env[index])
	{
		free(env[index]);
		env[index] = NULL;
		while (env[index + 1])
		{
			str = ft_strdup(env[index + 1]);
			env[index] = str;
			index++;
		}
		env[index] = NULL;
	}
	else
		ft_printf("Cannot unset %s\n", name);
	return (env);
}

char	**ft_resetenv(char **env, char *name, char *args, int size)
{
	char	**copy;
	int		index;

	copy = (char**)malloc(sizeof(char*) * (size + 2));
	index = 0;
	while (env[index])
	{
		copy[index] = ft_strdup(env[index]); 
		free(env[index]);
		index++;
	}
	copy[index] = ft_strnew(ft_strlen(args) + ft_strlen(name) + 1);
	ft_strcat(copy[index], name);
	ft_strcat(copy[index], args);
	copy[index + 1] = NULL;
	free(env);
	env = NULL;
	return (copy);
}

char	**ft_setenv(char **env, char *args)
{
	char	**tmp;
	char	name[256];
	char	*cpy;
	int		index;
	int		size;

	index = 0;
	size = 0;
	tmp = env;
	while (*args != ' ')
	{
		name[index] = *args;
		args++;
		index++;
	}
	name[index] = '=';	
	name[index + 1] = 0;
	index = ft_strlen(name);
	while (env[size] && ft_strncmp(env[size], name, ft_strlen(name)))
		size++;
	if (env[size])
	{
		env += size;
		index = ft_strlen(*env);
		if (!(size = ft_strlen(args)))
			ft_printf("cannot add an empty string\n");
		else
		{
			cpy = ft_strnew(index + size + 1);
			ft_strcpy(cpy, *env);
			ft_strcat(cpy, ENV_SEPARATOR);
			ft_strcat(cpy, args + 1);
			*env = cpy;
		}
		return (tmp);
	}
	else
		env = ft_resetenv(env, name, args + 1, size);
	return (env);
}
