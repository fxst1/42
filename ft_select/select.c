/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 12:04:46 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/21 12:04:48 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <select.h>

t_data		init_data(int argc, char **argv)
{
	t_data	dat;
	int		i;

	dat.item = (t_item*)malloc(sizeof(t_item) * (argc));
	dat.loc = 0;
	dat.max = argc - 1;
	i = 0;
	while (i < dat.max)
	{
		dat.item[i].name = argv[i + 1];
		dat.item[i].selected = 0;
		dat.item[i].deleted = 0;
		i++;
	}
	return (dat);
}

int			process(t_data *dat)
{
	int	ret;

	signal(SIGWINCH, catch_signal);
	signal(SIGTSTP, catch_signal);
	signal(SIGCONT, catch_signal);
	ioctl(get_fd(), TIOCGWINSZ, &dat->win);
	tcgetattr(0, &dat->term_back);
	tcgetattr(0, &dat->term);
	set_rawmode(&dat->term);
	tputs(tgetstr("cl", NULL), 1, term_putchar);
	tputs(tgetstr("ti", NULL), 1, term_putchar);
	tputs(tgetstr("vi", NULL), 1, term_putchar);
	tcsetattr(0, 0, &dat->term);
	my_select(dat);
	ret = get_inputs(dat);
	tputs(tgetstr("te", NULL), 1, term_putchar);
	tputs(tgetstr("ve", NULL), 1, term_putchar);
	tcsetattr(0, 0, &dat->term_back);
	return (ret);
}

void		print_results(t_data dat)
{
	int	index;

	index = 0;
	while (index < dat.max)
	{
		if ((dat.item[index].selected))
		{
			write(1, dat.item[index].name, ft_strlen(dat.item[index].name));
			write(1, " ", 1);
		}
		index++;
	}
}

int			main(int argc, char **argv)
{
	t_data	dat;

	if (argc == 1)
		return (0);
	dat = init_data(argc, argv);
	getdata(&dat);
	if (tgetent(NULL, getenv("TERM")) < 1)
	{
		write(2, "Cannot find TERM environnement variable\n", 40);
		return (1);
	}
	if (process(&dat) != -1)
		print_results(dat);
	free(dat.item);
	write(1, "\n", 1);
	return (0);
}
