#include "gnx.h"

/*
**	Exemple:	gnib(fd, &value, "01") avec dans le fd 3: "0110", value = 6
*/
int			get_next_integer_base(int fd, int *addr, char *base)
{
	int		ret;
	int		c;
	int		n_base;
	char	*chr;

	ret = -1;
	*addr = 0;
	n_base = ft_strlen(base);
	while ((ret = read(fd, &c, 1)) > 0)
	{
		if (c <= '9' && c >= '0')
		{
			chr = ft_strchr(base, c);
			*addr *= n_base;
			*addr += chr - base;
		}
		else
			return (ret);
	}
	return (ret);
}