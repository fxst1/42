#include <miniterm.h>

t_menu		init_menu(char *name, int x, int y, int nb_cnt)
{
	t_menu	m;

	m._x = x;
	m._y = y;
	m._name = name;
	m.cnt = (t_menuitem*)malloc(sizeof(t_menuitem) * nb_cnt);
	m.nb_cnt = nb_cnt;
	return (m);
}
