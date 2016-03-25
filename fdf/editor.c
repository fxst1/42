#include "fdf.h"

int			editor_key_hook(int keycode, t_env *e)
{
	if (keycode == 53)
	{
		e->mask = e->mask & ~(EDITOR);
		mlx_destroy_window(e->mlx, e->editor);
		e->editor = NULL;
	}
	return (0);
}

int			editor_expose_hook(t_env *e)
{
	return (e != NULL);
}

int			editor_mouse_hook(int btn, int x, int y, t_env *e)
{
	printf("%d <%d %d>\n", btn, x, y);
	return (e != NULL);
}

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

void		draw_rectfill(t_env *e, int x, int y, int h, int l, t_color c)
{
	int	i;
	int	j;

	i = x;
	while (i < x + l)
	{
		j = y;
		while (j < y + h)
			mlx_pixel_put(e->mlx, e->editor, i, j++, c);
		i++;
	}
}

void		draw_rect(t_env *e, int x, int y, int h, int l, t_color c)
{
	int	i;

	i = x;
	while (i < x + l)
	{
		mlx_pixel_put(e->mlx, e->editor, i, y, c);
		mlx_pixel_put(e->mlx, e->editor, i++, y + h, c);
	}
	i = y;
	while (i < y + h)
	{
		mlx_pixel_put(e->mlx, e->editor, x, i, c);
		mlx_pixel_put(e->mlx, e->editor, x + h, i++, c);
	}
}

void		draw_editor(t_env *e, int h, int l)
{
	int		x;
	int		y;
	int		len_x;
	int		len_y;
	char	*str;
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
			str = ft_itoa((int)p[x][y]->z);
			mlx_string_put(e->mlx, e->editor, 0,  0, 0xff00ff, "test");
			draw_rectfill(e, y * (h / len_y), x * (l / len_x), (h / len_y), (l / len_x), p[x][y]->coul);
			draw_rect(e, y * (h / len_y), x * (l / len_x), (h / len_y), (l / len_x), 0xffffff);
			free(str);
			y++;
		}
		x++;
	}
}

void		active_editor(t_env *e)
{
	if (!e->editor)
	{
		e->editor = mlx_new_window(e->mlx, 300, 300, "editor");
		mlx_hook(e->editor, 3, 3, editor_key_hook, e);
		mlx_expose_hook(e->editor, editor_expose_hook, e);
		mlx_mouse_hook(e->editor, editor_mouse_hook, e);
		e->mask |= EDITOR;
	}
	draw_editor(e, 300, 300);
}