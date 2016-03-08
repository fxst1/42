#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd = 0;
	char *ptr = NULL;

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