/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 22:37:54 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/14 22:37:55 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniterm.h>

static void		print_error_cd(t_term *t, char *cmd, char *ret)
{
	char	*act;

	act = NULL;
	if (ret && !cmd)
		act = ft_strjoin("No such file or directory: ", ret);
	else
		act = ft_strjoin("No such file or directory: ", cmd ? cmd : " ");
	print_error(t, "cd", act);
	free(act);
}

static void		change_env(t_term *t, char *new, char *old)
{
	char	*new_loc[4];
	char	*new_old[4];

	new_loc[0] = NULL;
	new_old[0] = NULL;
	new_loc[1] = "PWD";
	new_loc[2] = new ? new : t->dirpath;
	new_loc[3] = NULL;
	new_old[1] = "OLDPWD";
	new_old[2] = old ? old : "/";
	new_old[3] = NULL;
	setenvt(t, new_old);
	setenvt(t, new_loc);
}

static int		have_arg(t_term *t, char **cmd, char *act)
{
	char	*ret;

	ret = ft_getenv(t->env, "OLDPWD=");
	if (cmd[2])
	{
		print_error(t, "cd", "Too much arguments");
	}
	else if (!ft_strcmp(cmd[1], "-") && chdir(ret ? ret : "/") > -1)
	{
		getcwd(t->dirpath, sizeof(char) * 1024);
		change_env(t, t->dirpath, act);
	}
	else if (chdir(cmd[1]) > -1)
	{
		getcwd(t->dirpath, sizeof(char) * 1024);
		change_env(t, t->dirpath, act);
	}
	else
		return (1);
	return (0);
}

int				cd(t_term *t, char **cmd)
{
	char	*ret;
	char	*act;
	int		ok;

	ok = 1;
	ret = NULL;
	act = ft_strdup(t->dirpath);
	if (cmd[1])
		ok = have_arg(t, cmd, act);
	else if ((ret = ft_getenv(t->env, "HOME")) && chdir(ret) > -1)
	{
		getcwd(t->dirpath, sizeof(char) * 1024);
		change_env(t, t->dirpath, act);
		ok = 0;
	}
	free(act);
	if (ok)
		print_error_cd(t, cmd[1], ret);
	return (ok);
}
