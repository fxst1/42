#include "fdf.h"

t_point	*found_pt(t_point ***vct, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (vct[i])
	{
		j = 0;
		while (vct[i][j])
		{
			if (vct[i][j]->x == x && vct[i][j]->y == y)
				return (vct[i][j]);	
			j++;
		}
		i++;
	}
	return (0);
}

int	mouse_hook(int btn, int x, int y, t_env *e)
{
	t_point *p;

	if (bnt == 1 && (p = found_pt(e->fdf, x, y)))
	{
		printf("%p\t", p);
		printf("%x\n", p->coul);
//select edit p
	}
	return (0);
}