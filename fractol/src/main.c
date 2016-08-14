#include "env.h"

int				expose_hook(t_env *e)
{
//	ft_putstr("expose\n");
	(*e->fractal)(e);
	mlx_put_image_to_window(e->mlx, e->screen, e->img, 0, 0);
	print_info(e);
	return (0);
}

void			wtf_bis(t_env *e)
{
	printf("wtf\n");
	printf("%lf, %lf\n", e->im, e->re);
	e->im = (double)(ft_random() % 1000)/ (double)1000;
	e->re = (double)(ft_random() % 1000)/ (double)1000;
	expose_hook(e);
	printf("end wtf\n");
}

int				motion_hook(int x, int y, t_env *e)
{
//	ft_putstr("motion\n");
	if (!(e->mask & PAUSE_MODE) && x >= 0 && x < WIDTH && y >= 0 && y <= HEIGHT)
	{
		e->re = (double)x / (double)WIDTH * 2;
		e->im = (double)x / (double)WIDTH * 2;
		expose_hook(e);
	}
	return (0);
}

int				mouse_hook(int btn, int x, int y, t_env *e)
{
//	ft_putstr("mouse\n");
	if (!(e->mask & PAUSE_MODE))
		return (0);
	if (btn == 1)
	{
		e->zoom *= ZOOM_SCALE;
	}
	else if (btn == 3)
		e->zoom /= ZOOM_SCALE;
	else
		return (1);
	expose_hook(e);
	return (0);
	(void)x;
	(void)y;
	(void)e;
}

void			load_fd(t_env *e, int fd)
{
	int		useless;

	printf("loading\n");
	useless = read(fd, &e->im, sizeof(e->im));
	useless += read(fd, &e->re, sizeof(e->re));
	useless += read(fd, &e->h, sizeof(e->h));
	useless += read(fd, &e->s, sizeof(e->s));
	useless += read(fd, &e->v, sizeof(e->v));
	useless += read(fd, &e->nb_iter, sizeof(e->nb_iter));
	close(fd);
	if (!useless)
		return ;
}

void			save_fd(t_env *e, int fd)
{
	int		useless;

	printf("saving\n");
	useless = write(fd, &e->im, sizeof(e->im));
	useless += write(fd, &e->re, sizeof(e->re));
	useless += write(fd, &e->h, sizeof(e->h));
	useless += write(fd, &e->s, sizeof(e->s));
	useless += write(fd, &e->v, sizeof(e->v));
	useless += write(fd, &e->nb_iter, sizeof(e->nb_iter));
	close(fd);
	if (!useless)
		return ;
}

int				key_hook(int keycode, t_env *e)
{
//	printf("%d\n", keycode);
	if (keycode == ECH)
	{
		free_env(e);
		exit(0);
	}
	else if (keycode == KEY_L)
		wtf_bis(e);
	else if (keycode == KEY_Q && e->s < 256)
		e->s += 4;
	else if (keycode == KEY_W && e->s > 0)
		e->s -= 4;
	else if (keycode == KEY_A && e->s < 256)
		e->v += 4;
	else if (keycode == KEY_S && e->s > 0)
		e->v -= 4;
	else if (keycode == KEY_Z && e->s < 256)
		e->h += 4;
	else if (keycode == KEY_X && e->s > 0)
		e->h -= 4;
	else if (keycode == TABULATION)
	{
		if (e->fractal == &mandelbrot)
			e->fractal = &julia;
		else if (e->fractal == &julia)
			e->fractal = &burning_ship;
		else if (e->fractal == &burning_ship)
			e->fractal = &mandelbrot;
	}
	else if (keycode == KEY_R)
		random_animation(e);
	else if (keycode == UP)
		e->im += 0.05;
	else if (keycode == DOWN)
		e->im -= 0.05;
	else if (keycode == LEFT)
		e->re -= 0.05;
	else if (keycode == RIGHT)
		e->re += 0.05;
	else if (keycode == DIVIDE)
		e->zoom /= 2;
	else if (keycode == MULT)
		e->zoom *= 2;
	else if (keycode == PLUS)
		e->nb_iter += 10;
	else if (keycode == LESS && e->nb_iter - 10 > 0)
		e->nb_iter -= 10;
	else if (keycode == 32)
		e->mask ^= PAUSE_MODE;
	else if (keycode == KEY_M)
		save_fd(e, open("save.fractal", O_CREAT | O_WRONLY, 0644));
	else
		return (1);
	expose_hook(e);
	return (0);
}

static void		process(t_env *e, int mask, char *filename)
{
	if ((new_env(e, WIDTH, HEIGHT, "fractol")))
	{
		e->mask = mask | PAUSE_MODE;
		e->re = -0.7;
		e->im = 0.27015;
		e->nb_iter = 10;
		if (filename)
		{
			load_fd(e, open(filename, O_RDONLY, 0644));
		}
		e->x = 0;
		e->y = 0;
		e->dc = 0;
		random_animation(e);	
		e->zoom = 1;
		mlx_mouse_hook(e->screen, mouse_hook, e);
		//mlx_expose_hook(e->screen, expose_hook, e);
		//mlx_key_hook(e->screen, key_hook, e);
		mlx_hook(e->screen, KEY_PRESS, KEY_PRESS_MASK, key_hook, e);
		mlx_hook(e->screen, MOTION_NOTIFY, PTR_MOTION_MASK, motion_hook, e);
		expose_hook(e);
		mlx_loop(e->mlx);
	}
}

int				main(int argc, char **argv)
{
	t_env	*e = (t_env*)malloc(sizeof(t_env));
	int		mask;
	char	*filename = NULL;
	mask = 0;
	if (argc > 1)
	{
		argv++;
		printf("%p\n", &julia);
		while (*argv)
		{
			if (!ft_strcmp(*argv, "julia"))
			{
				mask |= JULIA;
				e->fractal = &julia;
			}
			else if (!ft_strcmp(*argv, "mandelbrot"))
			{
				mask |= MANDELBROT;
				e->fractal = &mandelbrot;
			}
			else if (!ft_strcmp(*argv, "bship"))
			{
				mask |= BSHIP;
				e->fractal = &burning_ship;
			}
			else if (!ft_strcmp(*argv, "--anim"))
				mask |= ANIM_MODE;
			else if (!ft_strncmp(*argv, "--load=", 7))
				filename = (*argv) + 7;
			else
				return (0);
			argv++;
		}
		process(e, mask, filename);
	}
	return (0);
}