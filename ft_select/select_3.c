/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 12:33:22 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/21 12:33:24 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <select.h>

void	catch_signal(int signum)
{
	t_data	*d;
	char	s[2];

	d = getdata(NULL);
	if (signum == SIGWINCH)
	{
		ioctl(1, TIOCGWINSZ, &d->win);
		my_select(d);
	}
	else if (signum == SIGTSTP)
	{
		tcsetattr(0, 0, &d->term_back);
		s[0] = d->term.c_cc[VSUSP];
		s[1] = 0;
		tputs(tgetstr("ve", NULL), 1, term_putchar);
		tputs(tgetstr("te", NULL), 1, term_putchar);
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, s);
	}
	else if (signum == SIGCONT)
	{
		tcsetattr(0, 0, &d->term);
		tputs(tgetstr("vi", NULL), 1, term_putchar);
		tputs(tgetstr("ti", NULL), 1, term_putchar);
		signal(SIGTSTP, catch_signal);
		my_select(d);
	}
}

void	set_rawmode(struct termios *termios_p)
{
	termios_p->c_lflag &= ~(ECHO | ICANON);
	termios_p->c_cflag |= CS8;
	termios_p->c_cc[VMIN] = 1;
	termios_p->c_cc[VTIME] = 0;
}

void	delete(t_data *dat)
{
	int	i;

	i = dat->loc;
	while (i + 1 < dat->max)
	{
		dat->item[i] = dat->item[i + 1];
		i++;
	}
	dat->max--;
}

void	reparse(t_data *dat)
{
	if (dat->loc < 0)
		dat->loc = dat->max - 1;
	else if (dat->loc >= dat->max)
		dat->loc = 0;
	if (dat->max)
		my_select(dat);
}

int		get_inputs(t_data *dat)
{
	int		c;
	int		ok;

	ok = 0;
	c = 0;
	while (!ok)
	{
		read(0, &c, 4);
		ok = (c == 3 || c == 18 || c == 27 || c == 10 || dat->max == 0);
		if (c == 4348699)
			dat->loc++;
		else if (c == 4283163)
			dat->loc--;
		else if (c == 127)
			delete(dat);
		else if (c == 32)
			dat->item[dat->loc].selected ^= 1;
		if (c == 4348699 || c == 4283163 || c == 127 || c == 32)
			reparse(dat);
		c = (c != 27) ? 0 : -1;
	}
	return (c);
}
