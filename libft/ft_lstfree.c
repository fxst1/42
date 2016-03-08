#include <libft/libft.h>

void	ft_lstfree(void *ptr, size_t len)
{
	if (ptr && len)
		free(ptr);
	ptr = NULL;
}
