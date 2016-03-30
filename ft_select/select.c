#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <term.h>
#include <termcap.h>
#include <sys/ioctl.h>
#include <signal.h>
#include "../libft/libft.h"
typedef struct		s_data
{
	struct termios	term_back;
	struct termios	term;
	struct winsize	win;
	char			**strs;
	int				selected;
	int				loc;
	int				max;
}					t_data;

int		term_putchar(int c)
{
	return (write(1, &c, 1));
}

void	set_rawmode(struct termios *termios_p)
{
	termios_p->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
		| INLCR | IGNCR | ICRNL | IXON);
	termios_p->c_oflag &= ~OPOST;
	termios_p->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	termios_p->c_cflag &= ~(CSIZE | PARENB);
	termios_p->c_cflag |= CS8;
	/*termios_p->c_lflag &= ~(ECHO | ICANON);
	termios_p->c_cc[VMIN] = 1;
	termios_p->c_cc[VTIME] = 0;*/
}

void	my_select(t_data dat)
{
	char	**strs;
	int		index;
	int		nl;

	nl = 0;
	index = 0;
	strs = dat.strs;
	tputs(tgetstr("cl", NULL), 1, term_putchar);
	while (strs[index])
	{
		nl = 0;
		if (ft_strlen(strs[index]) > 0)
		{
			//if ((1 << index) & dat.selected)
				tputs(tgetstr("us", NULL), 1, term_putchar);
	tputs(tgetstr("so", NULL), 1, term_putchar);
	ft_putstr_fd("\033[1;36m", 1);
	ft_putendl_fd(strs[index], 1);
	ft_putstr_fd("\033[00m", 1);
	tputs(tgetstr("se", NULL), 1, term_putchar);
	tputs(tgetstr("ue", NULL), 1, term_putchar);
			//if (index == dat.loc)
			//	ft_putstr("\033[7m");
			ft_putendl(strs[index]);
			ft_putstr("\033[0m");
			if (strs[index + 1] && ft_strlen(strs[index + 1]))
				nl = 1;
		}
		index++;
		if (nl)
			ft_putstr("\n");
	}
}

void	get_inputs(t_data *dat)
{
	int		c;
	int		ok;

	ok = 1;
	c = 0;
	while (ok)
	{
		read(0, &c, 4);
		if (c == 3 || c == 18 || c == 27 || c == 10)
			ok = 0;
		else if (c == 4348699)
			dat->loc++;
		else if (c == 4283163)
			dat->loc--;
		else if (c == 32)
			dat->selected |= (1 << dat->loc);
		if (c == 4348699 || c == 4283163 || c == 127)
		{
			if (dat->loc < 0)
				dat->loc = dat->max - 1;
			else if (dat->loc >= dat->max)
				dat->loc = 0;
			if (c == 127)
			{
				dat->strs[dat->loc] = "";
				dat->loc = 0;
				dat->max--;
			}
			if (dat->max)
				my_select(*dat);
		}
		c = 0;
	}
}

int	main(int argc, char **argv)
{
	t_data	dat;
	int		index;

	if (argc == 1)
		return (0);
	index = 0;
	dat.strs = argv + 1;
	dat.loc = 0;
	dat.max = argc - 1;
	dat.selected = 0;
	tputs(tgetstr("ti", NULL), 1, term_putchar);
	tputs(tgetstr("vi", NULL), 1, term_putchar);
	tcgetattr(0, &dat.term_back);
	tcgetattr(0, &dat.term);
	set_rawmode(&dat.term);
	tcsetattr(0, 0, &dat.term);
	my_select(dat);
	tcsetattr(0, 0, &dat.term);
	get_inputs(&dat);
	tputs(tgetstr("te", NULL), 1, term_putchar);
	tputs(tgetstr("ve", NULL), 1, term_putchar);
	tcsetattr(0, 0, &dat.term_back);
	while (index < argc)
	{
		if ((dat.selected >> index) & 1 && ft_strlen(dat.strs[index]))
			ft_putendl(dat.strs[index]);
		index++;
	}
	ft_putstr("\n");
	return (0);
}