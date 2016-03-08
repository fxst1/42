#include "map.h"

void	*ft_mapget(t_map *root, void *key, int (*cmp)())
{
	t_map	*m;

	if (key)
	{
		m = root->last;
		while (root)
		{
			if (!(*cmp)(key, root->key))
				return (root->value);
			root = root->next;
		}
		while (m)
		{
			if (!(*cmp)(key, m->key))
				return (m->value);
			m = m->last;
		}
	}
	return (NULL);
}