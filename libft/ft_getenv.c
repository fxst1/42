#include "implemt.h"

char	*ft_getenv(char **env, char *name)
{
	int		size;
	char	*ret;

	size = ft_strlen(name);
	while (*env && ft_strncmp(name, *env, size))
		env++;
	if (!*env)
		return (NULL);
	if ((ret = ft_strchr(*env, '=')))
		return (ret + 1);
	return (*env);
}
