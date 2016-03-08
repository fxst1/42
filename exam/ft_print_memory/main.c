#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void	*ft_print_memory(void *addr, size_t len);
int	main(int argc, char **argv)
{
	char	*str;
	int		fd;
	int		len;
	int		size;

	fd = 0;
	len = 0;
	size = 1024;
	if (argc > 1)
	{
		argv++;
		while (*argv)
		{
			str = (char*)malloc(1024);
			if ((fd = open(*argv, O_RDONLY)) > 0)
			{
				while ((len = read(fd, str + size - 1024, 1024)) > 0)
				{
					size += len;
					str = (char*)realloc(str, size);
				}
				ft_print_memory(str, size - 1024);
			}
			else
				printf("error : %s\n", *argv);
			argv++;
			free(str);
		}
	}
	else
		printf("need filename\n");
	return (0);
}
