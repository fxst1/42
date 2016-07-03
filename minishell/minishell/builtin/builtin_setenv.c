/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 22:38:01 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/14 22:38:02 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

static char		**resetenv(char **env, char *new_dom, char *val)
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

static char		**overwrite_env(char **env, char *domain, char *value)
{
	char	*tmp;
	int		index;

	index = 0;
	while (env[index] &&
		ft_strncmp(env[index], domain, ft_strclen(env[index], '=')))
		index++;
	if (env[index])
	{
		tmp = ft_strnew(ft_strlen(domain) + 1);
		ft_strcpy(tmp, domain);
		ft_strcat(tmp, "=");
		free(env[index]);
		env[index] = ft_strjoin(tmp, value);
		free(tmp);
	}
	else
		env = resetenv(env, domain, value);
	return (env);
}

static char		**not_overwrite(char **env, char *domain, char *value)
{
	char	*tmp;
	int		index;

	index = 0;
	while (env[index] &&
		ft_strncmp(env[index], domain, ft_strclen(env[index], '=')))
		index++;
	if (env[index])
	{
		tmp = ft_strnew(ft_strlen(env[index]) + 1);
		ft_strcpy(tmp, env[index]);
		ft_strcat(tmp, ":");
		free(env[index]);
		env[index] = ft_strjoin(tmp, value);
		free(tmp);
	}
	else
		env = resetenv(env, domain, value);
	return (env);
}

static int		init_mask(t_term *t, char **args, char **dom, char **value)
{
	int		index;
	int		mask;

	mask = -1;
	index = 0;
	if (args[index] && !ft_strcmp(args[index], "-o"))
	{
		index = 1;
		mask = 1;
	}
	if (!setenv_error(t, index, args))
	{
		*dom = ft_strdup(args[index]);
		*value = ft_strdup(args[index + 1]);
	}
	else
		mask = 0;
	return (mask);
}

int				setenvt(t_term *t, char **cmd)
{
	char	*domain;
	char	*value;
	int		overwrite;

	if ((overwrite = init_mask(t, cmd + 1, &domain, &value)))
	{
		t->env = (overwrite == -1) ? overwrite_env(t->env, domain, value) :
									not_overwrite(t->env, domain, value);
		free(domain);
		free(value);
		return (0);
	}
	return (1);
}
