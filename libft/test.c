#include "libft/gc.h"

int	main(void)
{
	//add a new pointer to gc
	char *tab1 = ft_gcdym("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", 90 - 27, 0);
	void *tab3 = ft_gcref(main, sizeof(main), 0);
	int *tab2 = ft_gcdym((int[]){1, 2, 4, 8, 16}, sizeof(int) * 5, 0);
	t_longest *tab4 = ft_gcdym((t_longest[]){ft_random()}, sizeof(t_longest), 0);
	ft_gcprint();

	tab1 = ft_gcdym("test", 5, 0);
	int  i = 0;
	while (i < 5)
	{
		tab2[i] = ft_random();
		i++;
	}
	ft_gcprint();
	ft_gcstop();
	ft_gcprint();
	return (0);
}