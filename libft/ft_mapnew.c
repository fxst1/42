#include "map.h"

t_map	*ft_mapnew(void *key, void *value)
{
	t_map *m;

	if ((m = (t_map*)malloc(sizeof(t_map))))
	{
		m->key = key;
		m->value = value;
		m->next = NULL;
		m->last = NULL;
	}
	else
		m = NULL;
	return (m);
}

t_map	ft_mapinit(void *key, void *value)
{
	t_map	m;

	m.key = key;
	m.value = value;
	return (m);
}
