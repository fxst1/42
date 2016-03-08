#include <libft/implemt.h>

long int	ft_random()
{
	static long int r = 0xACDC;
	static int	n = 1;
	char		*ptr;
	
	ptr = (char*)malloc(sizeof(char*));
	r |= (long int)ptr;
	r = (r * n) + 0xACDC;
	n++;
	free(ptr);
	return (r);
}

