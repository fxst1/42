#include <miniterm.h>

int			get_menu_xoffset(t_menuitem *m, int n)
{
	int	i;
	int	offset;
	int	len;

	i = 0;
	offset = 0;
	while (i < n)
	{
		len = ft_strlen((m + i)->item);
		if (len > offset)
			offset = len;
		i++;
	}
	return (offset);
}

void		put_cursor_at(int x, int y, int offset)
{
	int	delt;

	delt = x * offset;
	write(1, "\033[u", 3);
	while (y--)
		write(1, "\033[B", 3);
	while (delt--)
		write(1, "\033[C", 3);
}
