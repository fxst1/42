#include "fdf.h"

void	draw_fdf(t_env *e, t_point ***p)
{
	int i;
	int	j;
	t_point	p1;
	t_point	p2;

	e->p = (e->z_dx < 0) ? -1 : 1;
	i = 0;
	while (p[i])
	{
		j = 0;
		while (p[i][j])
		{
			p1 = *p[i][j];
			p1.x = e->x + (p1.x * e->dx) + (p1.z * e->z_dx);
			p1.y = (e->y + (p1.y * e->dy) - (p1.z * e->z_dy));
			if (p[i][j + 1])
			{
				p2 = *p[i][j + 1];
				p2.x = e->x + (p2.x * e->dx) + (p2.z * e->z_dx);
				p2.y = (e->y + (p2.y * e->dy) - (p2.z * e->z_dy));
				draw_line(e, p1, p2, p1.coul + p2.coul);
			}
			if (p[i + 1] && p[i + 1][j])
			{
				p2 = *p[i + 1][j];
				p2.x = e->x + (p2.x * e->dx) + (p2.z * e->z_dx);
				p2.y = (e->y + (p2.y * e->dy) - (p2.z * e->z_dy));
				draw_line(e, p1, p2, p1.coul + p2.coul);
			}
			j++;
		}
		i++;
	}
}

void	free_fdf(t_point ***p)
{
	int	i;
	int	j;

	i = 0;
	while (p[i])
	{
		j = 0;
		while (p[i][j])
		{
			free(p[i][j]);
			j++;
		}
		free(p[i]);
		i++;
	}
	free(p);
}

void	compute_fdf(t_env *e, t_point ***vct)
{
	int	i;
	int	j;

	i = 0;
	while (vct[i])
	{
		j = 0;
		while (vct[i][j])
		{
			vct[i][j]->x = e->x + (vct[i][j]->x * e->dx);
			vct[i][j]->y = e->y + (vct[i][j]->y * e->dy);
			j++;
		}
		i++;
	}
}

static t_point	**init_fdf_line(char *buf)
{
	t_point	**p;
	int		n;

	p = NULL;
	n = 0;
	while (*buf)
	{
		while (*buf == ' ' || *buf == '\t' || *buf == '\n')
			buf++;
		while (*buf && (ft_isalnum(*buf) || *buf == '-'))
			buf++;
		n++;
		buf++;
	}
	n+=3;
	p = (t_point**)malloc(sizeof(t_point*) * (n + 1));
	while (n >= 0)
		p[n--] = NULL;
	return (p);
}

t_point	***init_fdf_points(char *fname)
{
	int		fd;
	int		n;
	t_point	***p;
	char	*ptr;

	fd = open(fname, O_RDONLY);
	n = 0;
	p = NULL;
	ptr = NULL;
	while (get_next_line(fd, &ptr) > 0)
	{
		free(ptr);
		ptr = NULL;
		n++;
	}
	free(ptr);
	close(fd);
	n+=3;
	p = (t_point***)malloc(sizeof(t_point**) * (n + 1));
	while (n >= 0)
		p[n--] = NULL;
	return (p);
}

void	init_color(t_env *e, t_point *p)
{
	if (e->colorfdf == RANDOM)
			p->coul = ft_random();
	else
	{
		if (p->z > 0)
			p->coul = 0xFF0000;
		else if (p->z < 0)
			p->coul = 0x00FF00;
	}
}

t_point	***init_fdf(t_env *e, int const fd, t_point ***p)
{

	int		n;
	int		l;
	char	*ptr;
	char	*c;

	n = 0;
	l = 0;
	ptr = NULL;
	while (get_next_line(fd, &ptr) > 0)
	{
		c = ptr;
		l = 0;
		p[n] = init_fdf_line(ptr);
		while (*ptr)
		{
			while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n')
				ptr++;
			if (*ptr && (*ptr == '-' || ft_isalnum(*ptr)))
			{
				p[n][l] = new_point(l, n, ft_atoi(ptr), 0xff);
				init_color(e, p[n][l]);
				while (*ptr && (ft_isalnum(*ptr) || *ptr == '-'))
					ptr++;
			}
			l++;
		}
		free(c);
		ptr = NULL;
		n++;
	}
	free(ptr);
	return (p);
}

void	reset_color(t_point ***vct)
{
	int	i;
	int	j;
	int	low;
	int	high;

	i = 0;
	low = 0;
	high = 0;
	while (vct[i])
	{
		j = 0;
		while (vct[i][j])
		{
			if (vct[i][j]->z < low)
				low = vct[i][j]->z;
			else if (vct[i][j]->z > high)
				high = vct[i][j]->z;
			j++;
		}
		i++;
	}
	i = 0;
	while (vct[i])
	{
		j = 0;
		while (vct[i][j])
		{
			vct[i][j]->coul = vct[i][j]->z * (int)(0xffffff / ((high != low) ? (high - low) : (high + low)));
			j++;
		}
		i++;
	}
}

void	do_fdf(t_point ***vct, t_point *(*fct)(), t_point *arg)
{
	int	i;
	int	j;

	i = 0;
	while (vct[i])
	{
		j = 0;
		while (vct[i][j])
		{
			vct[i][j] = (*fct)(vct[i][j], arg);
			j++;
		}
		i++;
	}
}

void	print_fdf(t_point ***p)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (p[i])
	{
		j = 0;
		while (p[i][j])
		{
			printf("%d ", (int)p[i][j]->z);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	save_fdf(t_point ***p, char *fname)
{
	int		fd;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	fd = open(fname,  O_CREAT | O_WRONLY | O_TRUNC , 0666);
	str = NULL;
	if (fd > 0)
	{
		while (p[i])
		{
			j = 0;
			while (p[i][j])
			{
				str = ft_itoa(p[i][j]->z);
				write(fd, str, ft_strlen(str));
				if (p[i][j + 1])
					write(fd, " ", 1);
				free(str);
				j++;
			}
			if (p[i + 1])
				write(fd, "\n", 1);
			i++;
		}
	}
	close(fd);
}