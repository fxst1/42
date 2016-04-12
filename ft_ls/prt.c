/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/08 14:20:00 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/08 14:20:04 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ls.h>

void		prt(t_args *a, t_print *f, int last)
{
	int	*offset;

	offset = a->offset;
	print_maps(a, f);
	write(1, f->name, f->len_name);
	write(1, "\033[0m", 4);
	if (offset[2] < offset[1] && last)
	{
		a->offset[2] += f->len_name + offset[0] + 1;
		print_offset(offset[0] - f->len_name + 1, ' ');
	}
	else
	{
		a->offset[2] = 0;
		write(1, "\n", 1);
	}
}

void		prepare_buffer(t_args *a, t_file *f)
{
	int		off;
	int		*offset;

	off = 0;
	offset = a->offset;
	ioctl(1, TIOCGWINSZ, &a->ws);
	offset[0] = 0;
	offset[1] = a->ws.ws_col;
	offset[2] = 0;
	while (f)
	{
		off = f->p.len_name;
		if (offset[0] < off)
			offset[0] = off;
		f = f->next;
	}
}

void		parcours_basic(t_args *a, t_file *f)
{

}

void		parcours_simple(t_args *a, t_file *f)
{
	prepare_buffer(a, f);
	while (f)
	{
		prt(a, &f->p, !!f->next);
		delete_print(&f->p);
		f = f->next;
	}
}
