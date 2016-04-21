#ifndef MENU_H
# define MENU_H
# define MENU_IS_STR 1
# define MENU_IS_LIST 2

typedef struct
{
	int			_x;
	int			_y;
	int			type;
	void		(*callback)();
	void		*item;
	void		*data;
}				t_menuitem;

typedef struct		s_menu
{
	int				_x;
	int				_y;

	char			*_name;

	int				_cur_y;

	int				selected;

	t_menuitem		*cnt;
	int				nb_cnt;
}					t_menu;


void		draw_menu(t_menu *m);
t_menuitem	init_menuitem(void (*cb)(), char *name, void *userdata);
void		set_menuitem(t_menuitem *t, int x, int y, int type);
t_menu		init_menu(char *name, int x, int y, int nb_cnt);
int			get_menu_xoffset(t_menuitem *m, int n);
void		put_cursor_at(int x, int y, int offset);
int			read_menu_input(t_menu *m, int in);
void		menu_loop(t_menu *m);

#endif