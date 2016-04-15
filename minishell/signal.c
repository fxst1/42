/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/15 19:48:00 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/15 19:48:02 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniterm.h"
#define BUFF "minishell: segmentation fault: ./minishell (code erreur = "
#define ST "œ∑´®†¥¨ˆøπåß∂ƒ©˙∆˚¬…æΩ≈ç√∫˜µ≤≥÷¡™£¢∞§¶•ªº–≠"
/*
int			test(int mat[100][3])
{
	int i = 0;
	while (i < 30)
	{
		if (mat[i][1] > 0)
			return (0);
		i++;
	}
	return (1);
}

void		loop(int mat[100][3])
{
	int	i;

	i = 0;
	while (i < 30 && !test(mat))
	{
		if (ft_random() > 10000000000000)
		mat[i][1] -= 1;
		if (mat[i][1] > 0 && mat[i][0] > 0 && mat[i][2] != 7 && mat[i][0] != 7 && mat[i][1] != 7)
		{
			ft_putstr("\033[");
			ft_putnbr(mat[i][0]);
			ft_putstr(";");
			ft_putnbr(mat[i][1]);
			ft_putstr("f");
			ft_putchar(mat[i][2]);
		}
		i++;
	}
}

void		matrix_mode()
{
	int				i;
	struct winsize	ws;
	int				mat[100][3];

	ioctl(1, TIOCGWINSZ, &ws);
	ft_putstr("\033[32m");
	while (1)
	{
		i = 0;
		while (i < 30)
		{
			mat[i][0] = ((int)ft_random()) % ws.ws_row;
			mat[i][1] = ((int)ft_random()) % ws.ws_col;
			mat[i][2] = ft_abs(((int)ft_random()) % 43);
			i++;
		}
		loop(mat);
	}
}*/

void		catch_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr("minishell : SIGINT has been catch\n");
	}
	else if (signum == SIGABRT || signum == SIGTERM)
	{
		printf("ERROR\n");
		//matrix_mode();
	}
}
