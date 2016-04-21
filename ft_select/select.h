/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 12:33:49 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/21 12:33:51 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H
# include <termios.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <term.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct		s_item
{
	char			*name;
	int				selected;
	int				deleted;
}					t_item;

typedef struct		s_data
{
	struct termios	term_back;
	struct termios	term;
	struct winsize	win;
	int				loc;
	int				max;
	t_item			*item;
}					t_data;

int					get_fd(void);
void				catch_signal(int signum);
void				set_rawmode(struct termios *termios_p);
void				delete(t_data *dat);
int					get_inputs(t_data *dat);
t_data				*getdata(t_data *d);
int					get_offset(t_data *dat);
void				my_select(t_data *dat);
int					term_putchar(int c);
int					ft_strlen(const char *str);
void				ft_putstr(const char *str);
void				ft_putendl(const char *str);
#endif
