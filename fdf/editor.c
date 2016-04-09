#include "fdf.h"

void		compt_size_fdf(t_point ***p, int *x, int *y)
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
			if (j > *y)
				*y = j;
			j++;
		}
		if (i > *x)
			*x = i;
		i++;
	}
}

t_point		*get_point_at(t_env *e, int x, int y)
{
	int		i;
	int		j;
	int		len_x;
	int		len_y;
	t_point	***fdf;

	i = 0;
	j = 0;
	len_x = 0;
	len_y = 0;
	fdf = e->fdf;
	compt_size_fdf(fdf, &len_x, &len_y);
	while (i < len_x)
	{
		j = 0;
		while (j < len_y)
		{
			if ((j * (300 / len_y) <= y && y <= (j + 1) * (300 / len_y)) && (i * (300 / len_y) <= x && x <= (i + 1) * (300 / len_y)))
			{
				return (fdf[i][j]);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

void			get_input(int btn, t_point *p)
{
	char	value[4] = {0};

	printf("Point: <%d, %d, %d>\n", (int)p->x, (int)p->y, (int)p->z);
	if (btn == 1)
	{
		ft_putstr_fd("Set z:\n", 1);
	//	read(0, value, 4);
		p->z = ft_atoi(value);
	}
	else if (btn == 2)
	{
		ft_putstr_fd("Set color:\n", 1);
	//	read(0, value, 4);
		p->coul = ft_atoi(value);
	}
	printf("<%d, %d, %d>\n", (int)p->x, (int)p->y, (int)p->z);
}

void	pixel_put_edit(t_env *e, int x, int y, int c)
{
	t_buffer	*buf;

	buf = e->edit;
	if (x > 0 && x < e->l && y > 0 && y < e->h)
	{
		buf->data[(y * buf->size_line + x * buf->bpp / 8) + 3] =  (c >> 24) & 0xff;
		buf->data[(y * buf->size_line + x * buf->bpp / 8) + 2] =
			(c >> 16) & 0xff;
		buf->data[(y * buf->size_line + x * buf->bpp / 8) + 1] =
			(c >> 8) & 0xff;
		buf->data[(y * buf->size_line + x * buf->bpp / 8)] =
			(c & 0xff);
	}
}


int			editor_key_hook(int keycode, t_env *e)
{
	static	int value = 0;
	int			permut;

	if (keycode == 53)
	{
		e->mask = e->mask & ~(EDITOR);
		mlx_destroy_window(e->mlx, e->editor);
		e->editor = NULL;
	}
	else if (keycode != 76 && keycode != 36)
	{
		value *= 10;
		if (keycode >= 83 && keycode <= 89)
			value += keycode - 82;
		else if (keycode >= 91 && keycode <= 92)
			value += keycode - 90;
	}
	else
	{
		printf("value = %d\n", value);
		permut = value;
		value = 0;
		return (permut);
	}
	return (-1);
}

int			editor_expose_hook(t_env *e)
{
	return (e != NULL);
}

int			editor_mouse_hook(int btn, int x, int y, t_env *e)
{
	t_point	*pt;

	pt = get_point_at(e, x, y);
	printf("%p\n", pt);
	if (pt)
		get_input(btn, pt);
	printf("%d <%d %d>\n", btn, x, y);
	return (e != NULL);
}



void		draw_rectfill(t_env *e, int x, int y, int h, int l, t_color c)
{
	int	i;
	int	j;

	i = x;
	while (i < x + l)
	{
		j = y;
		while (j < y + h)
			pixel_put_edit(e, i, j++, c);
		i++;
	}
}

void		draw_rect(t_env *e, int x, int y, int h, int l, t_color c)
{
	int	i;

	i = x;
	while (i < x + l)
	{
		pixel_put_edit(e, i, y, c);
		pixel_put_edit(e, i++, y + h, c);
	}
	i = y;
	while (i < y + h)
	{
		pixel_put_edit(e, x, i, c);
		pixel_put_edit(e, x + h, i++, c);
	}
}

void		draw_editor(t_env *e, int h, int l)
{
	int		x;
	int		y;
	int		len_x;
	int		len_y;
	t_point	***p;

	x = 0;
	y = 0;
	len_x = 0;
	len_y = 0;
	compt_size_fdf(e->fdf, &len_x, &len_y);
	draw_rectfill(e, 0, 0, h, l, 0xAAAAAA);
	p = e->fdf;
	mlx_clear_window(e->mlx, e->editor);
	printf("(<%d %d>)\n", len_x, len_y);
	while (x < len_x)
	{
		y = 0;
		while (y < len_y)
		{
			draw_rectfill(e, y * (h / len_y), x * (l / len_x), (h / len_y), (l / len_x), p[x][y]->coul);
			draw_rect(e, y * (h / len_y), x * (l / len_x), (h / len_y), (l / len_x), 0xffffff);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(e->mlx, e->editor, e->img_e, 0, 0);
}

void		active_editor(t_env *e)
{
	if (!e->editor)
	{
		e->editor = mlx_new_window(e->mlx, 300, 300, "editor");
		e->img_e = mlx_new_image(e->mlx, 300, 300);
		e->edit = (t_buffer*)malloc(sizeof(t_buffer));
		e->edit->data = mlx_get_data_addr(e->img_e, &e->edit->bpp,
			&e->edit->size_line, &e->edit->endian);
		mlx_hook(e->editor, 3, 3, editor_key_hook, e);
		mlx_expose_hook(e->editor, editor_expose_hook, e);
		mlx_mouse_hook(e->editor, editor_mouse_hook, e);
		e->mask |= EDITOR;
	}
	draw_editor(e, 300, 300);
}