 #include "env.h"

void	*julia(t_env *e)
{
	static int		truc = -1;

	truc++;
	double newRe, newIm, oldRe, oldIm;
	int i;
	t_arg	*a = &e->arguments[truc];
	//printf("Julia %d\n", e->arguments[truc].y);

	for(int y = a->y; y < a->y + TH_SCL; y++)
	for(int x = 0; x < e->l; x++)
	{
		newRe = 1.5 * (x - e->l / 2) / (0.5 * e->zoom * e->l) + e->x;
		newIm = (y - WEIGTH / 2) / (0.5 * e->zoom * WEIGTH) + e->y;
		for(i = 0; i < e->nb_iter; i++)
		{
			oldRe = newRe;
			oldIm = newIm;
			newRe = oldRe * oldRe - oldIm * oldIm + e->re;
			newIm = 2 * oldRe * oldIm + e->im;
			if((newRe * newRe + newIm * newIm) > 4)
				break;
		}
		put_pixel(e->buffer, x, y,
			e->dc ^ wtf(i % 256, e->s, e->v * (i < e->nb_iter)));	
	}
	if (truc >= e->machin - 1)
		truc = -1;
	return (0);
}

void	*mandelbrot(t_env *e)
{
	static int		truc = -1;
	double newRe, newIm, oldRe, oldIm;
	double pi, pr;
	t_arg	*a = &e->arguments[truc];

	truc++;
	for(int y = a->y; y < a->y + TH_SCL; y++)
	for(int x = 0; x < e->l; x++)
	{
		pr = 1.5 * (x - e->l / 2) / (0.5 * e->zoom * e->l) + e->x;
		pi = (y - WEIGTH/ 2) / (0.5 * e->zoom * WEIGTH) + e->y;
		newRe = newIm = oldRe = oldIm = 0;
		int i;
		for(i = 0; i < e->nb_iter; i++)
		{
			oldRe = newRe;
			oldIm = newIm;
			newRe = oldRe * oldRe - oldIm * oldIm + pr;
			newIm = 2 * oldRe * oldIm + pi;
			if((newRe * newRe + newIm * newIm) > 4)
				break;
		}
		put_pixel(e->buffer, x, a->y,
			e->dc ^ wtf(i % 256, a->s, a->v * (i < e->nb_iter)));	
	}
	if (truc >= e->machin - 1)
		truc = -1;
	return (0);
}

void	*burning_ship(t_arg *a)
{/*
	t_point p0, p;
	t_point c;
	int	k;
	t_env 	*e;

	e = a->e;
	for (int x = 0; x < e->l; x++)
	{
		p0.x = 0;
		p0.y = 0;
		c.x = e->x + 2 * e->zoom * (x / e->l - 0.5);
		c.y = e->y + 2 * e->zoom * (a->y / e->w - 0.5);
		for (k=0;k<e->nb_iter;k++) {
			p.x = p0.x * p0.x - p0.y * p0.y - c.x;
			p.y = 2 * fabs(p0.x * p0.y) - c.y;
			p0 = p;
			if (p.x * p.x + p.y * p.y > 10)
				break;
		}
		put_pixel(e->buffer, x, a->y,
			e->dc ^ wtf(k % 256, a->s, a->v * (k < e->nb_iter)));
	}*/
	return (0);
}
