#include "gnx.h"

int		get_next_integer(int fd, int *addr)
{
	int	ret;
	int	c;

	ret = -1;
	*addr = 0;
	while ((ret = read(fd, &c, 1)) > 0)
	{
		if (c <= '9' && c >= '0')
		{
			*addr *= 10;
			*addr += c - '0';
		}
		else
			return (ret);
	}
	return (ret);
}
