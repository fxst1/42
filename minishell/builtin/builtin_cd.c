#include <miniterm.h>

static char	**change_env(t_term *t, char *new, char *old)
{
	char	*new_loc;
	char	*new_old;

	new_old = ft_strjoin("OLDPWD ", old ? old : t->dirpath);
	new_loc = ft_strjoin("PWD ", new ? new : t->dirpath);		
	if (ft_getenv(t->env, "PWD="))
		t->env = ft_unsetenv(t, t->env, "PWD");
	if (ft_getenv(t->env, "OLDPWD="))
		t->env = ft_unsetenv(t, t->env, "OLDPWD");
	t->env = ft_setenv(t->env, new_old);
	t->env = ft_setenv(t->env, new_loc);
	free(new_loc);
	free(new_old);
	return (t->env);
}

int		cd(t_term *t, char *cmd)
{
	char	*ret;

	if (!ft_strcmp(cmd, "cd -"))
	{
		if ((ret = ft_getenv(t->env, "OLDPWD=")))
		{
			chdir(ret);
			t->env = change_env(t, ft_getenv(t->env, "OLDPWD="), ft_getenv(t->env, "PWD="));
			getcwd(t->dirpath, sizeof(char) * 1024);
		}
	}
	else if (!chdir(!*(cmd + 2) ? ft_getenv(t->env, "HOME=") : cmd + 3))
	{
		t->env = change_env(t, cmd + 3, ft_getenv(t->env, "OLDPWD="));
		getcwd(t->dirpath, sizeof(char) * 1024);
	}
	else
	{
		print_error(t, "cd", "No such file or directory");
		return (1);
	}
	return (0);
}