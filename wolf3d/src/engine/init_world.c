#include <graphics.h>

int		get_next_integer(const int fd, int *addr)
{
	int	ret;
	int	c;

	*addr = 0;
	c = 0;
	while ((ret = read(fd, &c, 1)) > 0)
	{
		if (!ft_isdigit(c))
			break ;
		else
		{
			*addr *= 10;
			*addr += c - '0';
		}
	}
	return (ret);
}

int		load_walls(t_world *w, int **walls, int fd)
{
	int		x;
	int		y;

	if (walls)
	{
		y = 0;
		while (y < w->y_max)
		{
			x = 0;
			walls[y] = (int*)malloc(sizeof(int) * w->x_max);
			ft_bzero(walls[y], sizeof(int) * w->x_max);
			while (x < w->x_max)
			{
				get_next_integer(fd, &walls[y][x]);
				x++;
			}
			y++;
		}
		printf("\n");
	}
	else
	{
		write(2, "Out of memory\n", 14);
		return (0);
	}
	return (1);
}

int		read_file(t_world *w, char *filename, int fd)
{
	int		ret;

	ret = 0;
	ft_memset(w, 0, sizeof(t_world));
	w->name = filename;
	if ((ret = get_next_integer(fd, &w->x_max)) > 0)
	{
		get_next_integer(fd, &w->y_max);
		printf("(%d, %d)\n", w->x_max, w->y_max);
		w->walls = (int**)malloc(sizeof(int*) * (w->y_max + 1));
		if (!load_walls(w, w->walls, fd))
				ret = -1;
	}
	if (ret == -1)
	{
		write(2, "Cannot read file: ", 18);
		ft_putendl_fd(filename, 2);
	}
	return (ret);
}

t_world	load_wolf_3d(char *filename)
{
	int		fd;
	t_world	w;
	int		x, y;

	if ((fd = open(filename, O_RDONLY)) != -1)
	{
		write(1, "load map\n", 9);
		if ((read_file(&w, filename, fd)) < 0)
			return (w);
		y = 0;
		while (y < w.y_max)
		{
			x = 0;
			while (x < w.x_max)
			{
				if (w.walls[y][x])
					ft_putnbr(w.walls[y][x]);
				else
					write(1, " ", 1);
				x++;
			}
			y++;
			write(1, "\n", 1);
		}
	}
	else
	{
		write(2, "Cannot open file: ", 18);
		ft_putendl_fd(filename, 2);
	}
	close(fd);
	return (w);
}

