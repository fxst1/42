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

#include <stdio.h>
#include "get_next_line.h"

int		parse_fd(int argc, char *argv)
{
	int	fd;

	fd = (argc > 1) ? open(argv, O_RDONLY) : 0;
	if (fd > 0)
		printf("FILE = %s\n", argv);
	else if (fd == 0)
		printf("FILE = stdin\n");
	else
		printf("FILE = bad_fd\n");
	return (fd);
}

#if (BIN_MODE == 1)

void	print_line(char *ptr, int ret)
{
	int	index;

	index = 0;
	printf("%d: <\n", ret);
	while (index < ret)
		printf("%x ", 0xff & ptr[index++]);
	printf(">\n");
}

#else

void	print_line(char *ptr, int ret)
{
	printf("%d :<%s>\n", ret, ptr);
}

#endif

int		main(int argc, char **argv)
{
	int		fd;
	int		ret;
	char	*ptr;

	ptr = NULL;
	printf("BUFF_SIZE = %d\nDELIM = (%c), %d\n\n", BUFF_SIZE, DELIM, DELIM);
	argv++;
	while (*argv || argc == 1)
	{
		fd = parse_fd(argc, *argv);
		while ((ret = get_next_line(fd, &ptr)) > 0)
		{
			printf("%d\t", !!ptr);
			print_line(ptr, ret);
			free(ptr);
			ptr = NULL;
		}
		printf("%d :<%p>\n", ret, ptr);
		close(fd);
		if (fd > 0)
			argv++;
		else
			return (0);
	}
	return (0);
}
