#include <libft/libft.h>

void	ft_lstadd_begin(t_list **l, t_list *new)
{
	if (*l)
	{
		new->next = (*l);
	}
	*l = new;
}
