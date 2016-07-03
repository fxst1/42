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

#include <miniterm.h>
# define BUFF "minishell: segmentation fault: ./minishell (code erreur = "
# define ST "œ∑´®†¥¨ˆøπåß∂ƒ©˙∆˚¬…æΩ≈ç√∫˜µ≤≥÷¡™£¢∞§¶•ªº–≠"

void		catch_signal(int signum)
{
	t_term	*t;

	t = get_miniterm(NULL);
	write(1, "\033[m", 3);
	if (t->reading && signum != SIGWINCH)
		write(1, "\n", 1);
	if (signum == SIGINT)
		print_error(t, "extern signal", "sigint");
	else if (signum == SIGABRT)
		print_error(t, "extern signal ABORT", "... et merde ...");
	else if (signum == SIGTERM)
		print_error(t, "extern signal", "sigterm");
	else if (signum == SIGWINCH)
	{
		ioctl(1, TIOCGWINSZ, &t->ws);
	}
	if (t->reading && signum != SIGWINCH)
	{
		print_prompt(t);
		ft_putstr(t->line.buffer);
	}
}
