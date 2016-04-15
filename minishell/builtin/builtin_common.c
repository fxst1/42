/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commom.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 22:50:05 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/14 22:50:16 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

int		setenv_error(t_term *t, int index, char **args)
{
	if (!args[index])
	{
		print_error(t, "setenv", "domain needed");
		return (1);
	}
	else if (!args[index + 1])
	{
		print_error(t, "setenv", "value needed");
		return (1);
	}
	else if (args[index + 2])
	{
		print_error(t, "setenv", "bad arguments");
		return (1);
	}
	return (0);
}
