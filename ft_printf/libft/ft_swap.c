#include "implemt.h"

void	ft_swap(void *a, void *b)
{
	long unsigned int	tmp;
	
	tmp = (*(long unsigned int*)a);
	*(long unsigned int*)a = (*(long unsigned int*)b);
	*(long unsigned int*)b = tmp;
}

void	ft_swapn(void *a, void *b, size_t len)
{
	char	tmp;

	while (len)
	{
		tmp = *(char*)b;
		*(char*)(b++) = *(char*)a;
		*(char*)(a++) = tmp;
		len--;
	}
}

void	ft_swaplen(void *a, void *b, size_t len_a, size_t len_b)
{
	char	tmp;

	while (len_a && len_b)
	{
		tmp = *(char*)a;
		*(char*)(a++) = *(char*)b;
		*(char*)(b++) = tmp;
		len_a--;
		len_b--;
	}	
}