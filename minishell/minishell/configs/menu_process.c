#include <miniterm.h>

void		draw_menu(t_menu *m)
{
	int				i;
	int				offset;

	i = 0;
	offset = get_menu_xoffset(m->cnt, m->nb_cnt);
	write(1, "\033[u", 3);
	while (m->nb_cnt > i)
	{
		put_cursor_at(m->cnt[i]._x,  m->cnt[i]._y, offset + 1);
		if (m->_cur_y == i)
			write(1, "\033[7m", 4);
		write(1, m->cnt[i].item, ft_strlen(m->cnt[i].item));
		write(1, "\033[0m", 4);
		write(1, "\033[u", 3);
		i++;
	}
}

int		read_menu_input(t_menu *m, int in)
{
	if (in == 4348699)
		m->_cur_y++;
	else if (in == 4283163)
		m->_cur_y--;
	else if (in == MSHELL_KEYRIGHT)
	{
		;//m->cur_x++;
	}
	else if (in == MSHELL_KEYLEFT)
	{
	;//m->cur_x++;
	}if (m->_cur_y > m->nb_cnt)
		m->_cur_y = 0;
	else if (m->_cur_y < 0)
		m->_cur_y = m->nb_cnt - 1;
	if (in == '\n')
	{
		if (m->cnt[m->_cur_y].type == MENU_IS_STR)
			m->cnt[m->_cur_y].callback(m->cnt[m->_cur_y].data);
		else
		{
			m->cnt[m->_cur_y].callback(&m->cnt[m->_cur_y], m->_cur_y);
			return (-1);
		}
	}
	return (in);
}

void		menu_loop(t_menu *m)
{
	int	in;

	in = 0;
	m->_cur_y = 0;
	write(1, "\033c", 2);
	write(1, "\033[s", 3);
	write(1, m->_name, ft_strlen(m->_name));
	draw_menu(m);
	m->selected = 0;
	while (read(0, &in, sizeof(int)) && in != '\e')
	{
		if(read_menu_input(m, in) == -1)
			break ;
		draw_menu(m);
		write(1, "\n", 1);
		in = 0;
	}
	write(1, "\033c", 2);
}
