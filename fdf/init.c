#include "fdf.h"

t_point	*new_point(int x, int y, int z, int c)
{
	t_point	*pt;

	if ((pt = (t_point*)malloc(sizeof(t_point))))
	{
		pt->x = x;
		pt->y = y;
		pt->z = z;
		pt->coul = c;
	}
	return (pt);
}

t_point	init_point(t_coord x, t_coord y, t_coord z, t_color c)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = z;
	p.coul = c;
	return (p);
}

void	set_point(t_point *pt, int x, int y, int z)
{
	pt->x = x;
	pt->y = y;
	pt->z = z;
	pt->coul = 0;
}

t_env	*new_env(int h, int l)
{
	t_env *e;
	
	if ((e = (t_env*)malloc(sizeof(t_env))) &&
		((e->mlx = mlx_init())))
	{
		e->mask = 0;
		e->h = h;
		e->l = l;
		e->x = 10;
		e->y = 10;
		e->dx = 1;
		e->dy = 1;
		e->z_dx = 1;
		e->z_dy = 1;
		e->colorfdf = 0;
		e->buf = (t_buffer*)malloc(sizeof(t_buffer));
		e->screen = mlx_new_window(e->mlx, l, h, "win");
		e->img = mlx_new_image(e->mlx, l, h);
		e->buf->data = mlx_get_data_addr(e->img, &e->buf->bpp,
			&e->buf->size_line, &e->buf->endian);
		e->fdf = NULL;
		e->save = NULL;
	}
	else
		ft_putstr_fd("<env.c> malloc error\n", 2);
	return (e);
}

void		nb_pts(t_point ***pts, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (pts[i])
	{
		j = 0;
		while (pts[i][j])
			j++;
		if (*y < j)
			*y = j;
		i++;
	}
	*x = i;
}

void	set_scales(t_env *e, t_point ***pt)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	nb_pts(pt, &x, &y);
	if (x)
		e->dx = e->l / x;
	if (y)
		e->dy = e->h / y;
}

void	free_env(t_env *e)
{
	if (e)
	{
		if (e->save)
		{
			save_fdf(e->fdf, e->save);
			free(e->save);
		}
		free_fdf(e->fdf);
		mlx_destroy_window(e->mlx, e->screen);
		mlx_destroy_image(e->mlx, e->img);
		ft_memdel((void**)&e->buf);
		ft_memdel((void**)&e->mlx);
		ft_memdel((void**)&e);
	}
}
