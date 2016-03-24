#include "fdf.h"
/*
t_line		*new_line(t_point a, t_point b, t_color color)
{
	t_line	*new;

	if ((new = (t_line*)malloc(sizeof(t_line))))
	{
		*new = init_line(a, b , color);
	}
	else
		new = NULL;
	return (new);
}

t_line		init_line(t_point a, t_point b, t_color color)
{
	t_line	line;

	line.delt = init_point(ft_abs(b.x - a.x), ft_abs(b.y - a.y), ft_abs(b.z - a.z), color);
	line.alpha = a;
	line.beta = b;
	line.err = (line.delt.x > line.delt.y ? line.delt.x : -line.delt.y) / 2;
	line.color = color;
	return (line);
}

t_rgb			decompose_color(t_color	c, int alpha)
{
	t_rgb	color;

	if (!alpha)
	{
		color.r = (c & 0xFF0000) >> 16;
		color.g = (c & 0X00FF00) >> 8;
		color.b = (c & 0xFF);
		//color.a = 0;
	}
	else
	{
		color.r = (c & 0xFF000000) >> 24;
		color.g = (c & 0XFF0000) >> 16;
		color.b = (c & 0xFF00) >> 8;
		//color.alpha = (c & 0XFF);
	}
	return (color);
}

t_color_grad	init_color_gradian(t_color c1, t_color c2, int nb_values)
{
	t_color_grad	c;
	t_rgb			color1;
	t_rgb			color2;
	t_rgb			delt;
	int				n;

	n = 0;
	color1 = decompose_color(c1, 0);
	color2 = decompose_color(c2, 0);
	if (nb_values > 0)
	{
		c.colors = (t_color*)malloc(sizeof(t_color) * nb_values);
		c.nb_values = nb_values;
		delt.r = (color2.r - color1.r) / nb_values;
		delt.g = (color2.g - color1.g) / nb_values;
		delt.b = (color2.b - color1.b) / nb_values;
		while (n < nb_values)
		{
			c.colors[n] =	((color2.r & 0xff) << 16) |
							((color2.g & 0xff) << 8) |
							(color2.b & 0xff);
			color2.r -= delt.r;
			color2.g -= delt.g;
			color2.b -= delt.b;
			n++;
		} 
	}
	else
		c.colors = NULL;
	return (c);
}

void		print_line(t_line line)
{
	printf("======== LINE ========\n");
	printf("=> Alpha(%lf, %lf)\n", (double)line.alpha.x, (double)line.alpha.y);
	printf("=> Beta(%lf, %lf)\n", (double)line.beta.x, (double)line.beta.y);
	printf("=> Color %d\n", line.color);
}

static int	get_nonull_coord(t_point p)
{
	if (p.x > 0)
		return (p.x);
	else if (p.y > 0)
		return (p.y);
	else if (p.z > 0)
		return (p.z);
	return (0);
}

static t_color_grad correct_color_initialisation(t_line *line)
{
	t_color_grad	c;

	c.nb_values = 0;
	c.colors = NULL;
	if (line->color < 0)
	{
		if (line->color == LINE_DEPTH)
			c = init_color_gradian(line->beta.coul, line->alpha.coul,
			line->delt.z);
		else if (line->color == LINE_GRADIENT)
			c = init_color_gradian(line->beta.coul, line->alpha.coul,
			get_nonull_coord(line->delt));
		else
			line->color = 0xff00ff;
	}
	return (c);
}

void		draw_line(t_env *e, t_point p1, t_point p2, int color)
{
	t_coord			x;
	t_coord			y;
	t_coord			error;
	t_color_grad	c;
	t_line			l;
	int				n;

	l = init_line(p1, p2, color);
	x = l.alpha.x < l.beta.x ? 1 : -1;
	y = l.alpha.y < l.beta.y ? 1 : -1;
	c = correct_color_initialisation(&l);
	n = 0;
	while (l.alpha.x != l.beta.x ||
		l.alpha.y != l.beta.y)
	{
		mlx_pixel_put(e->mlx, e->screen, (int)l.alpha.x ,
			(int)l.alpha.y , (c.nb_values > 0 && n < c.nb_values ?
				c.colors[n++] : (t_color)0xffffff));
		error = l.err;
		if (error > -l.delt.x)
		{
			l.err -= l.delt.y;
			l.alpha.x += x;
		}
		if (error < l.delt.y)
		{
			l.err += l.delt.x;
			l.alpha.y += y;
		}
	}
	if (c.colors)
		free(c.colors);
}
*/