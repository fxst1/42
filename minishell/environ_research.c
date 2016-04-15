/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 00:21:13 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/30 00:21:15 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniterm.h>

t_list	*find(char *dn, char *cmd, t_list **file)
{
	DIR		*d;
	t_dir	*e;
	t_list	*new;

	if ((d = opendir(dn)))
	{
		while ((e = readdir(d)))
		{
			if (!ft_strcmp(cmd, e->d_name))
			{
				new = ft_lstnew(e->d_name, 2 + ft_strlen(e->d_name));
				ft_lstadd(file, new);
			}
		}
		closedir(d);
	}
	return (*file);
}

void	print_results(t_list *files)
{
	t_list *sw;

	while (files)
	{
		sw = files->next;
		ft_putnstr(files->content, files->content_size);
		write(1, "\n", 1);
		free(files->content);
		free(files);
		files = sw;
	}
}

void	contat_result(t_list *file, char *path, char **cmd)
{
	free(*cmd);
	*cmd = ft_strnew(
		ft_strlen(path) + file->content_size + 1);
	ft_strcpy(*cmd, path);
	ft_strcat(*cmd, "/");
	ft_strncat(*cmd, (char*)file->content, file->content_size);
	free(file->content);
	free(file);
}

char	*find_in_path(char **env, char **cmd)
{
	char	**path;
	char	*tmp;
	int		index;
	t_list	*files;

	files = NULL;
	index = 0;
	if ((tmp = ft_getenv(env, "PATH=")))
	{
		path = ft_strsplit(tmp, ':');
		tmp = NULL;
		while (path[index])
		{
			if (!tmp && find(path[index], *cmd, &files))
				tmp = path[index];
			index++;
		}
		if (files && !files->next)
			contat_result(files, tmp, cmd);
		else
			print_results(files);
		delete_tab(path);
	}
	return (*cmd);
}
