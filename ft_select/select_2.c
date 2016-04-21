/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 12:33:17 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/21 12:33:19 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <select.h>

t_data	*getdata(t_data *d)
{
	static t_data	*keep = NULL;

	if (d)
		keep = d;
	return (keep);
}

int		get_offset(t_data *dat)
{
	int	i;
	int	offset;
	int	len;

	i = 0;
	offset = 0;
	while (i < dat->max)
	{
		if (!dat->item[i].deleted)
		{
			len = ft_strlen(dat->item[i].name);
			if (len > offset)
				offset = len;
		}
		i++;
	}
	return (offset);
}

void	set_axis(int *x, int *y, int n_row, int offset)
{
	if ((*y) + 1 >= n_row)
	{
		*y = 0;
		*x += offset + 1;
	}
}

void	vsize(int x, int n_col)
{
	if (x + 1 >= n_col)
	{
		tputs(tgetstr("cl", NULL), 1, term_putchar);
		ft_putstr("Window too small");
	}
}

void	my_select(t_data *dat)
{
	int		x;
	int		y;
	int		i;
	int		offset;

	x = 0;
	y = 0;
	i = 0;
	offset = get_offset(dat);
	tputs(tgetstr("cl", NULL), 1, term_putchar);
	while (i < dat->max)
	{
		set_axis(&x, &y, dat->win.ws_row, offset);
		if (dat->item[i].selected)
			tputs(tgetstr("so", NULL), 1, term_putchar);
		if (i == dat->loc)
			tputs(tgetstr("us", NULL), 1, term_putchar);
		tputs(tgoto(tgetstr("cm", 0), x, y), 1, term_putchar);
		ft_putendl(dat->item[i].name);
		tputs(tgetstr("se", NULL), 1, term_putchar);
		tputs(tgetstr("ue", NULL), 1, term_putchar);
		y++;
		i++;
	}
	vsize(x, dat->win.ws_col);
}
