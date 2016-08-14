#include "implemt.h"

void		*ft_keep(const void *ptr)
{
	static void	*keep = NULL;

	if (ptr)
		keep = (void*)ptr;
	return (keep);
};