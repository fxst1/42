#include "implemt.h"
#include <stdio.h>

static int	replace_size_env(char **env, char *cmd)
{
	char	*ret;
	char	*env_r;
	int		index;
	int		size;
	char	t[1024];

	index = 0;
	ret  = cmd;
	size = ft_strlen(cmd);
	while ((ret = ft_strchr(ret, '$')))
	{
		ret++;
		index = 0;
		while (ret[index] && !ft_isspace(ret[index]))
		{
			t[index] = ret[index];
			index++;
		}
		t[index] = 0;
		size -= index;
		if ((env_r = ft_getenv(env, t)))
			size += ft_strlen(env_r);
		ret += index;
	}
	return (size);
}

static char	*replace_env(char **env, char *cmd)
{
	char	*env_r;
	int		index;
	int		size;
	char	*str;
	char	t[1024];

	size = replace_size_env(env, cmd);
	str = (char*)malloc(sizeof(char) * (size + 1));
	ft_memset(str, 0, sizeof(char) * (size + 1));
	size = 0;
	while (*cmd)
	{
		index = 0;
		if (*cmd == '$')
		{
			while (*(cmd + 1) &&
				(*(cmd + 1) != ' ' &&
				*(cmd + 1) != '\n' &&
				*(cmd + 1) != '\t'))
			{
				t[index] = *(cmd + 1);
				index++;
				cmd++;
			}
			t[index] = 0;
			if ((env_r = ft_getenv(env, t)))
			{
				index = ft_strlen(env_r);
				ft_strncpy(&str[size], env_r, index);
			}
			cmd++;
			size += index;
		}
		else
		{
			str[size] = *cmd;
			size++;
			cmd++;
		}
	}
	str[size] = 0;
	return (str);
}

char	**ft_build_cmd(char **env, char *cmd)
{
	char	**tab;
	char	*tmp;
	int		index;

	tab = ft_strsplit_cmd(cmd);
	index = 0;
	while (tab[index])
	{
		tab[index] = ft_strcut(tab[index], ' ');
		tmp = ft_strdup(tab[index]);
		free(tab[index]);
		tab[index] = replace_env(env, tmp);
		free(tmp);
		index++;
	}
	return (tab);
}
