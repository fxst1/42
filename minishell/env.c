/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 00:21:13 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 00:21:15 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniterm.h>

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

char	**ft_unsetenv(t_term *t, char **env, char *name)
{
	int		index;
	char	*str;

	index = 0;
	while (env[index] && ft_strncmp(env[index], name, ft_strlen(name)))
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
	{
		ft_putstr_fd(t->prompt, 2);
		ft_putstr_fd("\033[38;5;196m: ", 2);
		ft_putstr_fd(": unsetenv: cannot unset ", 2);
		ft_putendl_fd(name, 2);
		ft_putstr_fd(RESET, 2);
	}
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

char	**reparse_env(char **env, int size, char *args, int index)
{
	char	*cpy;
	char	**tmp;

	tmp = env;
	env += size;
	index = ft_strlen(*env);
	if (!(size = ft_strlen(args)))
		ft_putstr_fd("cannot add an empty string\n", 2);
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

char	**ft_setenv(char **env, char *args)
{
	char	name[256];
	int		index;
	int		size;

	index = 0;
	size = 0;
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
		return (reparse_env(env, size, args, index));
	else
		env = ft_resetenv(env, name, args + 1, size);
	return (env);
}
