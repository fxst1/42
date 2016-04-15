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
	DIR				*d;
	struct dirent	*entry;

	file = NULL;
	d = opendir(filen);
	while ((entry = readdir(d)))
	{
		if (!ft_strncmp(entry->d_name, cmd, ft_strlen(cmd)))
		{
			ft_lstadd(
				&file,
				ft_lstnew(entry->d_name,
				sizeof(char) * ft_strlen(entry->d_name) + 1));
		}
	}
	closedir(d);
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
			f = NULL;
			ft_strcpy(tmp, tabs[index]);
			ft_strcat(tmp, "/");
			if ((f = find_file(tmp, cmd)))
				ft_lstadd(&l, f);
			ft_memset(tmp, 0, 1025 + ft_strlen(cmd));
			index++;
		}
		free(tmp);
		delete_tab(tabs);
	}
	return (l);
}

void	print_it(t_term *t, t_list *l, int prnt, char *cmd)
{
	if (l && l->next)
	{
		ft_putstr("\nDisplay all results ? [y/n]\n");
		read(0, &prnt, 4);
		if (prnt == 'n')
		{
			prnt = 0;
			print_prompt(t);
		}
	}
	if (prnt)
	{
		while (l)
		{
			ft_putendl((char*)l->content);
			l = l->next;
		}
		print_prompt(t);
		ft_putstr_fd(cmd, 0);
	}
}

char	*do_autocomplet(t_term *t, char *cmd, int *ok)
{
	t_list	*l;
	t_list	*m;
	int		prnt;

	if (*cmd != '.')
		l = find_path(ft_getenv(t->env, "PATH"), cmd);
	else
		l = find_file(t->dirpath, cmd);
	m = l;
	prnt = 0;
	if (l && !l->next)
	{
		prnt = ft_strlen(cmd);
		if (!ft_strcmp(cmd, l->content))
			*ok = 1;
		else
			*ok = 2;
		free(cmd);
		cmd = ft_strdup(l->content);
		ft_putstr(cmd + prnt);
		prnt = 0;
	}
	print_it(t, l, prnt, cmd);
	ft_lstdel(&m, &ft_lstfree);
	return (cmd);
}
