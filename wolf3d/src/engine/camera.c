#include <camera.h>

t_camera	new_camera()
{
	t_camera	c;

	c.pos_x = 22.0;
	c.pos_y = 11.5;
	c.dir_x = -1.0;
	c.dir_y = 0.0;
	c.speed = 0.9;
	c.rspeed = 0.5;
	c.plane_x = 0.0;
	c.plane_y = 0.66;
	return (c);
}

void		init_camera(t_camera *c, int reset)
{
	if (reset)
		*c = new_camera();
	set_speed(c);
}

void		set_speed(t_camera *c)
{
	static int	last_time = 0;
	int		act_time;
	double		frame_time;

	act_time = time(0);
	if (last_time)
		last_time = act_time - 1;
	frame_time = (act_time - last_time) / 1000.0;
	c->speed = frame_time * 5;
	c->rspeed = frame_time * 3;
	last_time = act_time;
}
