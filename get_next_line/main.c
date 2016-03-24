/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:27:45 by fjacquem          #+#    #+#             */
/*   Updated: 2016/03/23 04:28:27 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*ptr;

	ptr = NULL;
	if (argc)
	{
		argv++;
		while (*argv)
		{
			fd = open(*argv, O_RDONLY);
			ft_putendl(*argv);
			while (get_next_line(fd, &ptr) > 0)
			{
				ft_putstr("(out)");
				ft_putendl(ptr);
				free(ptr);
				ptr = NULL;
			}
			close(fd);
			argv++;
		}
	}
	free(ptr);
	return (0);
}
