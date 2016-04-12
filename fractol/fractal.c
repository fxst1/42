#include "env.h"


int	julia(t_env *e)
{
	double newRe, newIm, oldRe, oldIm;
	int i;

	for(int y = 0; y < e->h; y++)
	for(int x = 0; x < e->l; x++)
	{
		newRe = 1.5 * (x - e->l / 2) / (0.5 * e->zoom * e->l) + e->x;
		newIm = (y - e->h / 2) / (0.5 * e->zoom * e->h) + e->y;
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
			e->dc ^ wtf(i % 256, 255, 255 * (i < e->nb_iter)));	
	}
	return (0);
}

int	mandelbrot(t_env *e)
{
	double newRe, newIm, oldRe, oldIm;
	double pi, pr;

	for(int y = 0; y < e->h; y++)
	for(int x = 0; x < e->l; x++)
	{
		pr = 1.5 * (x - e->l / 2) / (0.5 * e->zoom * e->l) + e->x;
		pi = (y - e->h / 2) / (0.5 * e->zoom * e->h) + e->y;
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
			e->dc ^ wtf(i % 256, 255, 255 * (i < e->nb_iter)));	
	}
	return (0);
}

int burning_ship(t_env *e)
{
	t_point p0, p;
	t_point c;
	int	k;

	for (int i=0;i<e->l;i++) {
		for (int j=0;j<e->h;j++) {
			p0.x = 0;
			p0.y = 0;
			c.x = e->x + 2 * e->zoom * (i / (double)e->l - 0.5);
			c.y = e->y + 2 * e->zoom * (j / (double)e->h - 0.5);
			for (k=0;k<e->nb_iter;k++) {
				p.x = p0.x * p0.x - p0.y * p0.y - c.x;
				p.y = 2 * fabs(p0.x * p0.y) - c.y;
				p0 = p;
				if (p.x * p.x + p.y * p.y > 10)
					break;
			}
			put_pixel(e->buffer, i, j,
				e->dc ^ wtf(k % 256, 255, 255 * (k < e->nb_iter)));
		}
	}
	return (0);
}
