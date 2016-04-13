#include "env.h"

int				expose_hook(t_env *e)
{
	t_arg	args[1024];
	int i = 0;

	init_threads(e, args);
	while (i < (e->w) / TH_SCL)
	{	
		pthread_join(e->th[i], NULL);
		i++;
	}
	mlx_put_image_to_window(e->mlx, e->screen, e->img, 0, 0);
	return (0);
}
/*
int	loop(t_env *e)
{
	int i = 0;

	expose_hook(e);
	while (i < (e->w) / TH_SCL)
	{	
		pthread_join(e->th[i], NULL);
		i++;
	}
	return (0);
}
*/
int				mouse_hook(int btn, int x, int y, t_env *e)
{
	printf("%d, btn\n", btn);
	if (btn != 4)
	{
		printf("WAS: %lf, %lf\n", e->re, e->im);
		e->re += (x < e->w / 2) ? -0.01 : 0.01;
		e->im += (y < e->l / 2) ? -0.01 : 0.01;
		printf("NOW: %lf, %lf\n", e->re, e->im);
	}
	else
	{
		e->zoom =/ 2;
	}
	expose_hook(e);
	return (0);
}

int				key_hook(int keycode, t_env *e)
{
	printf("%d\n", keycode);
	if (keycode == 53)
	{
		free_env(e);
		exit(0);
	}
	else if (keycode == 13 && e->s < 256)
		e->s += 4;
	else if (keycode == 12 && e->s > 0)
		e->s -= 4;
	else if (keycode == 0 && e->s < 256)
		e->v += 4;
	else if (keycode == 1 && e->s > 0)
		e->v -= 4;
	else if (keycode == 7 && e->s < 256)
		e->h += 4;
	else if (keycode == 6 && e->s > 0)
		e->h -= 4;
	else if (keycode == 48)
	{
		if (e->fractal == &mandelbrot)
			e->fractal = &julia;
		else if (e->fractal == &julia)
			e->fractal = &burning_ship;
		else if (e->fractal == &burning_ship)
			e->fractal = &mandelbrot;
	}
	else if (keycode == UP)
		e->y += 0.05;
	else if (keycode == DOWN)
		e->y -= 0.05;
	else if (keycode == LEFT)
		e->x -= 0.05;
	else if (keycode == RIGHT)
		e->x += 0.05;
	else if (keycode == DIVIDE)
		e->zoom /= 2;
	else if (keycode == MULT)
		e->zoom *= 2;
	else if (keycode == 49)
	{
		reset_color(e, ft_random());
		mlx_put_image_to_window(e->mlx, e->screen, e->img, 0, 0);
	}
	else if (keycode == PLUS)
		e->nb_iter += 10;
	else if (keycode == LESS && e->nb_iter - 10 > 0)
		e->nb_iter -= 10;
	if (keycode != 49)
		expose_hook(e);
	return (0);
}

static void		process(t_env *e, int mask)
{
	if ((new_env(e, 600, 600, "fractol")))
	{
		e->mask = mask;
		e->re = -0.7;
		e->im = 0.27015;
		e->nb_iter = 100;
		e->x = 0;
		e->y = 0;
		e->dc = 0;
		e->h = 256;
		e->s = 255;
		e->v = 255;		
		e->zoom = 1;
		mlx_mouse_hook(e->screen, mouse_hook, e);
		mlx_expose_hook(e->screen, expose_hook, e);
		mlx_key_hook(e->screen, key_hook, e);
//		mlx_loop_hook(e->screen, );
//		mlx_do_key_autorepeaton(e->mlx);
//		mlx_do_sync(e->mlx);
		mlx_loop(e->mlx);
	}
}

void			init_threads(t_env *e, t_arg *arguments)
{
	int	i;
	i = 0;
	while (i < e->w / TH_SCL)
	{
		init_arg(&arguments[i], e, e->s, e->v);
		arguments[i].y = i * TH_SCL;
		pthread_create(&e->th[i], NULL, e->fractal, &arguments[i]);
		i++;
	}
}

int				main(int argc, char **argv)
{
	t_env	e;
	int		mask;

	mask = 0;
	if (argc > 1)
	{
		argv++;
		while (*argv)
		{
			if (!ft_strcmp(*argv, "julia"))
			{
				mask |= JULIA;
				e.fractal = &julia;
			}
			else if (!ft_strcmp(*argv, "mandelbrot"))
			{
				mask |= MANDELBROT;
				e.fractal = &mandelbrot;
			}
			else if (!ft_strcmp(*argv, "bship"))
			{
				mask |= BSHIP;
				e.fractal = &burning_ship;
			}
			argv++;
		}
		process(&e, mask);

	}
	return (0);
}