#include "libft.h"

int		ft_strcasecmp(const char *s1, const char *s2)
{
	while (s1 && s2 && ft_tolower(*s1) == ft_tolower(*s2) && *s1)
	{
		s1++;
		s2++;
	}
	return (ft_tolower(*s1) - ft_tolower(*s2));
}