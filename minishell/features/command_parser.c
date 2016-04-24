/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 22:09:07 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/14 22:09:09 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniterm.h>

char	*skip_quotes(char *cmd, int *skip_len)
{
	int	is_quote;

	is_quote = 0;
	if (*cmd == 39 || *cmd == 34)
	{
		is_quote = *cmd;
		while (*cmd && *cmd != is_quote)
		{
			(*skip_len)++;
			cmd++;
		}
		cmd++;
	}
	return (cmd);
}

int		replace_tilde(char *home, char *str)
{
	int	size;

	size = 0;
	if (home)
	{
		size = ft_strlen(home);
		ft_strcat(str, home);
	}
	return (size);
}

char	*replace_env(char **env, char *cmd, int lret)
{
	int		size;
	char	*str;

	size = replace_size_env(env, cmd, lret);
	size += replace_size_tilde(cmd, ft_getenv(env, "HOME"));
	str = ft_strnew(size + 1);
	size = 0;
	while (*cmd)
	{
		cmd = skip_quotes(cmd, &size);
		if (*cmd == '$')
			size += sub_replace_env(env, &cmd, &str[size], lret);
		else if (*cmd == '~')
		{
			size += replace_tilde(ft_getenv(env, "HOME"), &str[size]);
			cmd++;
		}
		else
		{
			str[size++] = *cmd;
			cmd++;
		}
	}
	str[size] = 0;
	return (str);
}

char	*sup_replace(char *line)
{
	char	*ptr;
	int		is_quote;

	is_quote = 0;
	ptr = line;
	while (*line)
	{
		if (*line == 34 || *line == 39)
		{
			is_quote = *line;
			line++;
			while (*line && *line != is_quote)
				line++;
			if (*line)
				line++;
		}
		else if (*line == '\t')
			*line = ' ';
		line++;
	}
	return (ptr);
}

char	*build_cmd(char **env, char *cmd, int lret)
{
	char	*tmp;

	cmd = sup_replace(cmd);
	cmd = ft_strcut(cmd, ' ');
	if (env && *env)
	{
		tmp = ft_strdup(cmd);
		free(cmd);
		cmd = replace_env(env, tmp, lret);
		free(tmp);
	}
	return (cmd);
}
