/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 19:49:04 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/15 19:49:06 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniterm.h"

t_list	*find_file(char *filen, char *cmd)
{
	t_list			*file;
	t_list			*new;
	DIR				*d;
	struct dirent	*entry;

	file = NULL;
	if ((d = opendir(filen)))
	{
		while ((entry = readdir(d)))
		{
			if (!ft_strncmp(entry->d_name, cmd, ft_strlen(cmd)) &&
				ft_strcmp("..", entry->d_name) && ft_strcmp(".", entry->d_name))
			{
				new = ft_lstnew(entry->d_name,
					sizeof(char) * ft_strlen(entry->d_name) + 1);
				((char*)new->content)[new->content_size] = 0;
				suppr_unprintable(new->content);
				ft_lstadd(&file, new);
				new = NULL;
			}
		}
		closedir(d);
	}
	return (file);
}

t_list	*find_path(char *t, char *cmd)
{
	char	*tmp;
	t_list	*l;
	t_list	*f;
	char	**tabs;
	int		index;

	l = NULL;
	index = 0;
	if (t && (tabs = ft_strsplit(t, ':')))
	{
		tmp = ft_strnew((1025 + ft_strlen(cmd)));
		while (tabs[index])
		{
			ft_strcpy(tmp, tabs[index]);
			ft_strcat(tmp, "/");
			if ((f = find_file(tmp, cmd)))
				ft_lstadd(&l, f);
			index++;
		}
		free(tmp);
		delete_tab(tabs);
	}
	if (l && !l->next)
		*cmd = 0;
	return (l);
}

t_list	*find_rest(char *loc_dir, char *cmd, int index)
{
	int		i;
	char	t[1024];
	char	*ret;
	t_list	*l;

	i = index;
	while (i > 0 && cmd[i] != ' ')
		i--;
	ft_strncpy(t, &cmd[i + 1], index - i);
	if (t[0] == '/')
	{
		if ((ret = ft_strrchr(t, '/')))
			*(ret + 1) = 0;
		ret = t;
		if ((l = find_file(ret, &cmd[i + 2])))
		{
			cmd[i + 2] = 0;
		}
		return (l);
	}
	printf("act_dir\n");
	return (find_file(loc_dir, &cmd[i + 1]));
}

char	*do_autocomplet(t_term *t, char *cmd, int *ok, int index)
{
	t_list	*l;
	t_list	*m;
	int		prnt;
	char	*ret;

	if (!(ret = ft_strrchr(cmd, ' ')))
		l = find_path(ft_getenv(t->env, "PATH"), cmd);
	else
		l = find_rest(t->dirpath, cmd, index);
	m = l;
	prnt = 0;
	if (l && !l->next)
	{
		prnt = ft_strlen(cmd);
		if (!ft_strcmp(cmd, l->content))
			*ok = 1;
		else
			*ok = 2;
		cmd = realloc_buffer(cmd, l->content_size + prnt);
		cmd = ft_strcat(cmd, l->content);
		ft_putstr(cmd);
		//prnt = 0;
	}
	else
		print_it(t, l, cmd);
	free_list(l);
	return (cmd);
}
