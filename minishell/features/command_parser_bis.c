/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 22:24:27 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/14 22:24:30 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniterm.h>

int		size_env(char **env, char *t, int lret)
{
	char	*env_r;
	int		size;

	size = 0;
	env_r = NULL;
	if (!ft_strcmp(t, "?"))
	{
		env_r = ft_itoa(lret);
		size = ft_strlen(env_r);
		free(env_r);
	}
	else if ((env_r = ft_getenv(env, t)))
		size = ft_strlen(env_r);
	return (size);
}

int		str_env(char **env, char *str, char *t, int lret)
{
	char	*env_r;
	int		index;

	env_r = NULL;
	index = 0;
	if (!ft_strcmp("?", t))
	{
		env_r = ft_itoa(lret);
		index = ft_strlen(env_r);
		ft_strcat(str, env_r);
		str[index] = 0;
		free(env_r);
	}
	else if ((env_r = ft_getenv(env, t)))
	{
		index = ft_strlen(env_r);
		ft_strcat(str, env_r);
		str[index] = 0;
	}
	return (index);
}

int		replace_size_tilde(char *cmd, char *home)
{
	char	*ret;
	int		total;
	int		size;

	ret = cmd;
	total = 0;
	if (home)
	{
		size = ft_strlen(home);
		while ((ret = ft_strchr(ret, '~')))
		{
			total += (size - 1);
			ret++;
		}
	}
	return (total);
}

int		replace_size_env(char **env, char *cmd, int lret)
{
	char	*ret;
	int		index;
	int		size;
	char	t[1024];

	ret = cmd;
	size = ft_strlen(cmd);
	while ((ret = ft_strchr(ret, '$')))
	{
		ret++;
		index = 0;
		while (ret[index] && (ft_isalnum(ret[index]) ||
			ret[index] == '_' || ret[index] == '?' || ret[index] == '/'))
		{
			t[index] = ret[index];
			index++;
		}
		t[index] = 0;
		size -= index;
		size += size_env(env, t, lret);
		ret += index;
	}
	return (size);
}

int		sub_replace_env(char **env, char **cmd, char *str, int ret)
{
	int		index;
	char	t[1024];

	index = 0;
	(*cmd)++;
	while (**cmd && (ft_isalnum(**cmd) || (**cmd == '?') ||
		(**cmd == '_') || **cmd == '/'))
	{
		t[index] = **cmd;
		index++;
		(*cmd)++;
	}
	t[index] = 0;
	index = str_env(env, str, t, ret);
	(*cmd)++;
	return (index);
}
