#include <libft/libft.h>

int	brainfuck(char *array, int *ptr, size_t n)
{
	int i = -1;
	unsigned int size = 0;
	while (++i, array[i] && size < n)
	{
		if (array[i] == '+')
			++(*ptr);
		else if (array[i] == '-')
			--(*ptr);
		else if (array[i] == '>')
		{	++ptr; ++size;		}
		else if (array[i] == '<')
		{	--ptr;	--size;		}
		else if (array[i] == '.')
			write(1, ptr, 1);
		else if (array[i] == ',')
			read(0, ptr, 1);
		else if (array[i] == '[')
			continue;
		else if (array[i] == ']' && *ptr)
		{
			int loop = 1;
			while (loop > 0)
			{
				char c = array[--i];
				if (c == '[')
					loop--;
				else if (c == ']')
					loop++;
			}
		}
		else if (array[i] != ']')
		{
			ft_putstr("Unknow symbol <");
			write(1, &array[i], 1);
			ft_putendl("> ...");
			break;
		}
	}
	return (size < n)?(0):(1);
}

int main(int argc, char **argv)
{
	int ptr[1024] = {0};

	if (argc > 1)
		return (brainfuck(argv[1], ptr, 1024));
	return (1);
}
