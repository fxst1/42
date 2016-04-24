#include <miniterm.h>

void		mycallback(t_term *t);

void		color_bgselect(t_menuitem *m, int n)
{
	free(*(char**)m->data);
	*(char**)m->data = NULL;
	*(char**)m->data = ft_itoa(30 + n);}

void		color_fgselect(t_menuitem *m, int n)
{
	free(*(char**)m->data);
	*(char**)m->data = NULL;
	*(char**)m->data = ft_itoa(30 + n);
}

void		mybgcolor_callback(char** str)
{
	t_menu		m;
	t_menuitem	*items;

	m = init_menu("<===========>  BACKGROUND COLORS <===========>", 0, 0, 8);
	items = m.cnt;
	items[0] = init_menuitem(color_bgselect, "|\033[40m _ \033[0m|", str);
	set_menuitem(&items[0], 0, 1, MENU_IS_LIST);
	items[1] = init_menuitem(color_bgselect, "|\033[41m _ \033[0m|", str);
	set_menuitem(&items[1],0, 2, MENU_IS_LIST);
	items[2] = init_menuitem(color_bgselect, "|\033[42m _ \033[0m|", str);
	set_menuitem(&items[2],0, 3, MENU_IS_LIST);
	items[3] = init_menuitem(color_bgselect, "|\033[43m _ \033[0m|", str);
	set_menuitem(&items[3],0, 4, MENU_IS_LIST);
	items[4] = init_menuitem(color_bgselect, "|\033[44m _ \033[0m|", str);
	set_menuitem(&items[4],0, 5, MENU_IS_LIST);	
	items[5] = init_menuitem(color_bgselect, "|\033[45m _ \033[0m|", str);
	set_menuitem(&items[5],0, 6, MENU_IS_LIST);
	items[6] = init_menuitem(color_bgselect, "|\033[46m _ \033[0m|", str);
	set_menuitem(&items[6],0, 7, MENU_IS_LIST);
	items[7] = init_menuitem(color_bgselect, "|\033[47m _ \033[0m|", str);
	set_menuitem(&items[7],0, 8, MENU_IS_LIST);
	menu_loop(&m);
	free(m.cnt);
}

void		myfgcolor_callback(char** str)
{
	t_menu		m;
	t_menuitem	*items;

	m = init_menu("<===========>  FOREGROUND COLORS <===========>", 0, 0, 8);
	items = m.cnt;
	items[0] = init_menuitem(color_fgselect, "|\033[30m _ \033[0m|", str);
	set_menuitem(&items[0], 0, 1, MENU_IS_LIST);
	items[1] = init_menuitem(color_fgselect, "|\033[31m _ \033[0m|", str);
	set_menuitem(&items[1], 0, 2, MENU_IS_LIST);
	items[2] = init_menuitem(color_fgselect, "|\033[32m _ \033[0m|", str);
	set_menuitem(&items[2], 0, 3, MENU_IS_LIST);
	items[3] = init_menuitem(color_fgselect, "|\033[33m _ \033[0m|", str);
	set_menuitem(&items[3], 0, 4, MENU_IS_LIST);
	items[4] = init_menuitem(color_fgselect, "|\033[34m _ \033[0m|", str);
	set_menuitem(&items[4], 0, 5, MENU_IS_LIST);
	items[5] = init_menuitem(color_fgselect, "|\033[35m _ \033[0m|", str);
	set_menuitem(&items[5], 0, 6, MENU_IS_LIST);
	items[6] = init_menuitem(color_fgselect, "|\033[36m _ \033[0m|", str);
	set_menuitem(&items[6], 0, 7, MENU_IS_LIST);
	items[7] = init_menuitem(color_fgselect, "|\033[37m _ \033[0m|", str);
	set_menuitem(&items[7], 0, 8, MENU_IS_LIST);
	menu_loop(&m);
	free(m.cnt);
}

void		mycolor_callback(t_term *t)
{
	t_menu		m;
	t_menuitem	*items;

	m = init_menu("<===========>  COLORS <===========>", 0, 0, 6);
	items = m.cnt;
	items[0] = init_menuitem(myfgcolor_callback, "name fg", &t->name_txt);
	set_menuitem(&items[0], 0, 1, MENU_IS_STR);
	items[1] = init_menuitem(mybgcolor_callback, "name bg", &t->name_back);
	set_menuitem(&items[1], 0, 2, MENU_IS_STR);
	items[2] = init_menuitem(myfgcolor_callback, "cmd fg", &t->cmd_txt);
	set_menuitem(&items[2], 0, 3, MENU_IS_STR);
	items[3] = init_menuitem(mybgcolor_callback, "cmd bg", &t->cmd_back);
	set_menuitem(&items[3], 0, 4, MENU_IS_STR);
	items[4] = init_menuitem(myfgcolor_callback, "promt fg", &t->pt_txt);
	set_menuitem(&items[4], 0, 5, MENU_IS_STR);
	items[5] = init_menuitem(mybgcolor_callback, "promt bg", &t->pt_back);
	set_menuitem(&items[5], 0, 6, MENU_IS_STR);
	menu_loop(&m);
	free(m.cnt);
}

void		myname_callback(t_term *t)
{
		(void)t;
	free(t->prompt);
	t->prompt = NULL;
	write(1, "Enter a new name:", 17);
	t->prompt = ft_strnew(1024);
	t->prompt = get_cmd_line(t, new_cmdline(t), 0);
}

void		profiles_menu(t_term *t, t_menu *m)
{
	t_menuitem	*items;

	*m = init_menu("<===========>  PROFILES <===========>", 0, 0, 3);
	items = m->cnt;
	items[0] = init_menuitem(mycolor_callback, "colors", t);
	set_menuitem(&items[0], 0, 1, MENU_IS_STR);
	items[1] = init_menuitem(myname_callback, "name", t);
	set_menuitem(&items[1], 0, 2, MENU_IS_STR);
	items[2] = init_menuitem(mycallback, "def path", t);
	set_menuitem(&items[2], 0, 3, MENU_IS_STR);
}

void		myprofiles_callback(t_term *t)
{
	t_menu	m;

	profiles_menu(t, &m);
	menu_loop(&m);
	free(m.cnt);
}

void		mycallback(t_term *t)
{
	(void)t;
	sleep(1);
}

void		mysave_callback(t_term *t)
{
//	char	*name;

	(void)t;
	write(1, "Enter your save name:", 21);
//	name = ft_strnew(1024);
	//name = get_cmd_line(t, &name, 0);
	write(1, "saved !\n", 1);
	//save_term(t, ft_strcat(name, ".mshell"));
//	free(name);
}

void		myload_callback(t_term *t)
{
//	char	*name;
	(void)t;
	write(1, "Enter filename to load:", 23);
	//name = ft_strnew(1024);
	//name = get_cmd_line(t, &name, 0);
	//load_term(t, ft_strcat(name, ".mshell"), MSHELL_MASK_ALL);
//	free(name);
}

void		mymain_menu(t_term *t, t_menu *m)
{
	t_menuitem	*items;

	*m = init_menu("<===========>  MINISHELL _ CONFIGS <===========>", 0, 0, 6);
	items = m->cnt;
	items[0] = init_menuitem(myprofiles_callback, "profiles", t);
	set_menuitem(&items[0], 0, 1, MENU_IS_STR);
	items[1] = init_menuitem(mycallback, "completion", t);
	set_menuitem(&items[1], 0, 2, MENU_IS_STR);
	items[2] = init_menuitem(mycallback, "historic", t);
	set_menuitem(&items[2], 0, 3, MENU_IS_STR);
	items[3] = init_menuitem(mysave_callback, "save", t);
	set_menuitem(&items[3], 0, 4, MENU_IS_STR);
	items[4] = init_menuitem(myload_callback, "load", t);
	set_menuitem(&items[4], 0, 5, MENU_IS_STR);
	items[5] = init_menuitem(mycallback, "reset as default", t);
	set_menuitem(&items[5], 0, 6, MENU_IS_STR);
}

int			builtin_cfg(t_term *t, char **args)
{
	t_menu	main_menu;

	(void)args;
	mymain_menu(t, &main_menu);
	menu_loop(&main_menu);
	free(main_menu.cnt);
	return (0);
}