#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
# include <term.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <signal.h>

typedef struct		s_data
{
	struct termios	term_back;
	struct	termios	term;
	char			**strs;
	int				loc;
	int				max;
}					t_data;

void	set_rawmode(struct termios *termios_p)
{
	termios_p->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
		| INLCR | IGNCR | ICRNL | IXON);
	termios_p->c_oflag &= ~OPOST;
	termios_p->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	termios_p->c_cflag &= ~(CSIZE | PARENB);
	termios_p->c_cflag |= CS8;
}

void	my_select(t_data dat)
{
	char	**strs;
	int		index;
	int		nl;

	nl = 0;
	index = 0;
	strs = dat.strs;
	ft_putstr("\033c");
//	printf("<%d>\n", dat.loc);
	while (strs[index])
	{
		nl = 0;
		if (ft_strlen(strs[index]) > 0)
		{
			if (index == dat.loc)
				ft_putstr("\033[7m");
			set_rawmode(&dat.term);
			tcsetattr(0, TCSANOW, &dat.term);
			ft_putstr(strs[index]);
			ft_putstr("\x1B[0m");
			tcsetattr(0, TCSANOW, &dat.term_back);
			if (strs[index + 1] && ft_strlen(strs[index + 1]))
				nl = 1;
		}
		index++;
		if (nl)
			ft_putstr("\n");
	}
	set_rawmode(&dat.term);
	tcsetattr(0, TCSANOW, &dat.term);
}

void	get_inputs(t_data *dat)
{
	char	c;
	int		ok;

	ok = 1;
	c = 0;
	while (ok)
	{
		read(0, &c, 1);
		if (c == 3 || c == 18)
			ok = 0;
		else if (c == 65)
			dat->loc--;
		else if (c == 66)
			dat->loc++;
//		printf("<%d>\n", c);
		if (c == 65 || c == 66 || c == 127)
		{
			if (dat->loc < 0)
				dat->loc = dat->max - 1;
			else if (dat->loc >= dat->max)
				dat->loc = 0;
			if (c == 127)
			{
				dat->strs[dat->loc] = "";
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

	dat.strs = argv + 1;
	dat.loc = 0;
	dat.max = argc - 1;
	//tputs(tgetstr("cl", NULL), 1, ft_putstr);
	tcgetattr(0, &dat.term_back);
	set_rawmode(&dat.term);
	tcsetattr(0, TCSANOW, &dat.term);
	ft_putstr("\033c");
	my_select(dat);
	tcsetattr(0, TCSANOW, &dat.term);
	get_inputs(&dat);
	tcsetattr(0, TCSANOW, &dat.term_back);
	ft_putstr("\n");
	return (0);
}