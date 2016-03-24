#include "implemt.h"

void	*ft_realloc(void *addr, size_t len)
{
	void	*ptr;

	ptr = NULL;
	if (addr && (ptr = ft_memalloc(len)))
	{
		ft_memcpy(ptr, addr, len);
		free(addr);
	}
	return(ptr);
}
