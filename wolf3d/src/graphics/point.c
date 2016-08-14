#include <graphics.h>

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

t_rgb	init_rgb(t_color coul)
{
	t_rgb	c;

	c.r = (coul & 0xff0000) >> 16;
	c.g = (coul & 0xff00) >> 8;
	c.b = coul & 0xff;
	return (c);
}

t_line	init_line(t_point p1, t_point p2)
{
	t_line	l;
	t_point	p;
	t_point	abs;
	t_point	sd;

	abs.x = ft_abs(p2.x - p1.x);
	abs.y = ft_abs(p2.y - p1.y);
	p.x = ((int)abs.x) >> 1;
	p.y = ((int)abs.y) >> 1;
	sd.x = (p2.x > p1.x) ? 1 : -1;
	sd.y = (p2.y > p1.y) ? 1 : -1;
	l.abs = abs;
	l.p = p;
	l.sd = sd;
	return (l);
}
