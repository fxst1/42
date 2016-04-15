/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 22:38:32 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/14 22:38:36 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniterm.h>

static int		print_environnment(t_term *t)
{
	char	**env;

	env = t->env;
	while (*env)
	{
		ft_putendl_fd(*env, 1);
		env++;
	}
	return (0);
}

int				env(t_term *t, char **args)
{
	int		index;
	int		mask;

	mask = 0;
	index = 1;
	while (args[index])
	{
		if (!ft_strcmp(args[index], "-i"))
			mask = 1;
		else if (!ft_strcmp(args[index], "-u"))
		{
			mask = 2;
			unsetenvt(t, &args[index]);
		}
		else if (!mask)
		{
			print_error(t, "env", "bad argument");
			return (1);
		}
		index++;
	}
	if (!mask)
		print_environnment(t);
	return (0);
}
