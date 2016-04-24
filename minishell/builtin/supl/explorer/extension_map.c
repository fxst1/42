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

#include <explorer.h>

t_map	*init_extension_map(char *env, int index)
{
	char	key[32];
	char	value[32];
	t_map	*c_map;

	c_map = NULL;
	while (*env)
	{
		index = 0;
		if (*env == '*')
		{
			env++;
			while (*env && *env != '=')
				key[index++] = *(env++);
			key[index] = 0;
			env += (*env == '=');
			index = 0;
			while (*env && *env != ':')
				value[index++] = *(env++);
			value[index] = 0;
			ft_mapadd_begin(&c_map, ft_mapnew(ft_strdup((char*)key),
				ft_strdup((char*)value)));
		}
		env += !!(*env);
	}
	return (c_map);
}

int		found_clicolor(t_args *a, char **env)
{
	char	*found_clicolor;

	if ((found_clicolor = ft_getenv(env, "CLICOLOR=")) &&
		!ft_strcmp(found_clicolor + 9, "1"))
		a->mask |= COLOR;
	if (a->mask & COLOR)
	{
		found_clicolor = ft_getenv(env, "LS_COLORS=");
		if (found_clicolor)
			a->colormap = init_extension_map(found_clicolor + 10, 0);
	}
	return (0);
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
