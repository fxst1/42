/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 22:38:07 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/14 22:38:08 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniterm.h>

static char		**resetenv(char **env, char *del_dom)
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

int				unsetenvt(t_term *t, char **args)
{
	if (args[1])
	{
		while (*args)
		{
			t->env = resetenv(t->env, *args);
			args++;
		}
	}
	else
	{
		print_error(t, "unsetenv", "domain needed");
		return (1);
	}
	return (0);
}
