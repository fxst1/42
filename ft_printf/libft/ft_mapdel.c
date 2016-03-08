#include "map.h"

void	ft_mapdel(t_map **root, int clear, void (*_freek)(), void (*_freev)())
{
	t_map	*n;
	t_map	*l;
	t_map	*tmp;

	n = *root;
	l = (*root) ? (*root)->last : NULL;
	while (n)
	{
		tmp = n->next;
		if (_freev)
			(*_freev)(n->value);
		n->value = NULL;
		if (_freek)
			(*_freek)(n->key);
		n->key = NULL;
		if (clear)
		{
			free(n);
			n = NULL;
		}
		n = tmp;
	}
	while (l)
	{
		tmp = l->last;
		if (_freev)
			(*_freev)(l->value);
		l->value = NULL;
		if (_freek)
			(*_freek)(l->key);
		l->key = NULL;
		if (clear)
		{
			free(l);
			l = NULL;
		}
		l = tmp;
	}
}
