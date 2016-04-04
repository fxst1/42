/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 01:54:53 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 01:54:54 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_map	*init_extension_map(void)
{
	return (NULL);
}

char	*init_type(char *colors, char ret, int is_pair)
{
	int		n;
	char	*s;

	if (ret != 'x' && ((ret >= 'a' && ret <= 'g') ||
		(ret >= 'A' && ret <= 'g')))
	{
		n = (ret >= 'a' && ret <= 'g') ? ret - 'a' : ret - 'A';
		if (ret >= 'a' && ret <= 'g')
			colors = ft_strdup(&C_COLORS[n * 3 + n]);
		else
			colors = ft_strdup(&C_B_COLORS[n * 3 + n]);
	}
	else
		colors = ft_strdup("38");
	if (is_pair)
	{
		if ((s = ft_strchr(colors, '3')))
			*s = '4';
		else if ((s = ft_strchr(colors, '9')))
		{
			*(s - 1) = '0';
			*(s - 2) = '1';
		}
	}
	return (colors);
}

char	**init_typemap(char **env)
{
	char	**colors;
	char	*ret;
	int		i;

	i = 0;
	colors = NULL;
	while (*env && !(ret = ft_strstr(*env, "LSCOLORS=")))
		env++;
	if (ret)
	{
		ret = ft_strchr(ret, '=');
		ret++;
	}
	else
		ret = C_DEF;
	colors = (char**)malloc(sizeof(char*) * 23);
	while (ret[i] && i < 22)
	{
		colors[i] = init_type(colors[i], ret[i], i % 2);
		i++;
	}
	colors[i] = NULL;
	return (colors);
}
