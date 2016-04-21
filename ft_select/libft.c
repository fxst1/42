/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 12:33:39 by fjacquem          #+#    #+#             */
/*   Updated: 2016/04/21 12:33:40 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <select.h>

int		get_fd(void)
{
	static int	fd = -1;

	if (fd == -1)
	{
		fd = open("/dev/tty", O_RDWR);
		if (fd < 0 || !isatty(fd))
			fd = 1;
	}
	return (fd);
}

int		term_putchar(int c)
{
	return (write(get_fd(), &c, 1));
}

void	ft_putstr(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(get_fd(), str, i);
}

void	ft_putendl(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(get_fd(), str, i);
	write(get_fd(), "\n", 1);
}

int		ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
