#include "implemt.h"

char	*ft_getenv(char **env, char *name)
{
	char	*ret;

	while (*env && ft_strncmp(name, *env, ft_strclen(*env, '=')))
		env++;
	if (!*env)
		return (NULL);
	if ((ret = ft_strchr(*env, '=')))
		return (ret + 1);
	return (*env);
}
