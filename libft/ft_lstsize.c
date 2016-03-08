#include <libft/libft.h>

int	ft_lstsize(t_list *t)
{
	int	n;

	n = 0;
	while (t)
	{
		n++;
		t = t->next;
	}
	return (n);
}
