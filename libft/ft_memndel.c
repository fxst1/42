#include "implemt.h"

void	ft_memndel(void **addr, size_t n)
{
	while (n--)
		free(addr[n]);
	free(*addr);
	*addr = NULL;
}
