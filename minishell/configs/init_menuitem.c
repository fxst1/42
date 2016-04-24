#include <miniterm.h>

t_menuitem	init_menuitem(void (*cb)(), char *name, void *userdata)
{
	t_menuitem	it;

	it.callback = cb;
	it.item = name;
	it.data = userdata;
	return (it);
}

void		set_menuitem(t_menuitem *it, int x, int y, int type)
{
	it->_x = x;
	it->_y = y;
	it->type = type;
}
