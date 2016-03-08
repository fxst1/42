#include "map.h"

void	ft_mapadd_end(t_map **root, t_map *new)
{
	t_map	*m;
	t_map	*l;

	if (*root)
	{
		l = NULL;
		m = *root;
		while (m->next)
		{
			l = m;
			m = m->next;
		}
		m->last = l;
		m = new;
	}
	else
		*root = new;
}

void	ft_mapadd_begin(t_map **root, t_map *new)
{
	if (*root)
	{
		new->next = *root;
		new->next->last = new;
	}
	*root = new;
}

void	ft_mapadd_at(t_map **root, t_map *new, int index)
{
	t_map	*m;
	t_map	*i;

	m = *root;
	if (!*root)
	{
		*root = new;
	}
	else if (index < 0)
	{
		while (m->last && index != 0)
		{
			index++;
			i = m;
			m = m->last;
		}
		m->last = new;
		new->next = i;
	}
	else
	{
		while (m->next && index != 0)
		{
			index--;
			i = m;
			m = m->next;
		}
		m->next = new;
		new->last = i;
	}
}
