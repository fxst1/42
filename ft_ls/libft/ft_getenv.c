#include "implemt.h"

char			*ft_getenv(char **env, char *name)
{
	int	size;

	size = ft_strlen(name);
	while (*env && ft_strncmp(name, *env, size))
		env++;
	return (*env);
}