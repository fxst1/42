 #include "env.h"

void	*julia(t_env *e)
{
	double newRe, newIm, oldRe, oldIm;
	int i;
	int y, x; 

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			newRe = 1.5 * (x - WIDTH / 2) / (0.5 * e->zoom * WIDTH) + e->x;
			newIm = (y - HEIGHT / 2) / (0.5 * e->zoom * HEIGHT) + e->y;
			i = 0;
			while (i < e->nb_iter)
			{
				oldRe = newRe;
				oldIm = newIm;
				newRe = oldRe * oldRe - oldIm * oldIm + e->re;
				newIm = 2 * oldRe * oldIm + e->im;
				if((newRe * newRe + newIm * newIm) > 4)
					break;
				i++;
			}
			put_pixel(e->buffer, x, y,
					wtf(i % (int)e->h, e->s, e->v * (i < e->nb_iter)));	
			x++;
		}
		y++;
	}
	return (0);
}

void	*mandelbrot(t_env *e)
{
	double newRe, newIm, oldRe, oldIm;
	double pi, pr;
	int		x, y;

	for(y = 0; y < HEIGHT; y++)
	for(x = 0; x < WIDTH; x++)
	{
		pr = 1.5 * (x - HEIGHT / 2) / (0.5 * e->zoom * HEIGHT) + e->x;
		pi = (y - WIDTH / 2) / (0.5 * e->zoom * WIDTH) + e->y;
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
		put_pixel(e->buffer, x, y,
			wtf(i % 256, e->s, e->v * (i < e->nb_iter)));	
	}
	return (0);
}

void	*burning_ship(t_env *e)
{
	t_point p0, p;
	t_point c;
	int		k;
	int		x;
	int		y;

	for(y = 0; y < WIDTH; y++)
	for (x = 0; x < HEIGHT; x++)
	{
		p0.x = 0;
		p0.y = 0;
		c.x = e->x + 2 * e->zoom * (x / HEIGHT - 0.5);
		c.y = e->y + 2 * e->zoom * (y / WIDTH - 0.5);
		for (k=0 ; k<e->nb_iter ; k++)
		{
			p.x = p0.x * p0.x - p0.y * p0.y - c.x;
			p.y = 2 * fabs(p0.x * p0.y) - c.y;
			p0 = p;
			if (p.x * p.x + p.y * p.y > 10)
				break;
		}
		put_pixel(e->buffer, x, y,
			wtf(k % 256, e->s, e->v * (k < e->nb_iter)));
	}
	return (0);
}
