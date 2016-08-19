#include <graphics.h>
#include <stdio.h>
int				event(int keycode, t_graphics *g)
{
	t_camera	c = g->c;
	t_world		w = g->w;
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = c.dir_x;
	old_plane_x = c.plane_x;
	//printf("%p\n", w.walls);
	//move forward if no wall in front of you
	if (keycode == 65362)
	{
		if(w.walls[(int)(c.pos_y)][(int)(c.pos_x + c.dir_x * c.speed)] == 0)
			c.pos_x += c.dir_x * c.speed;
		if(w.walls[(int)(c.pos_x)][(int)(c.pos_y + c.dir_y * c.speed)] == 0)
			c.pos_y += c.dir_y * c.speed;
	}
	//move backwards if no wall behind you
	if (keycode == 65364)
	{
		if(w.walls[(int)(c.pos_x - c.dir_x * c.speed)][(int)(c.pos_y)] == 0)
			c.pos_x -= c.dir_x * c.speed;
		if(w.walls[(int)(c.pos_x)][(int)(c.pos_y - c.dir_y * c.speed)] == 0)
			c.pos_y -= c.dir_y * c.speed;
	}
	//rotate to the right
	if (keycode == 65361)
	{
		//both camera direction and camera plane must be rotated
		c.dir_x = c.dir_x * cos(-c.rspeed) - c.dir_y * sin(-c.rspeed);
		c.dir_y = old_dir_x * sin(-c.rspeed) + c.dir_y * cos(-c.rspeed);
		c.plane_x = c.plane_x * cos(-c.rspeed) - c.plane_y * sin(-c.rspeed);
		c.plane_x = old_plane_x * sin(-c.rspeed) + c.plane_y * cos(-c.rspeed);
	}

	//rotate to the left
	if (keycode == 65363)
	{
		//both camera direction and camera plane must be rotated
		c.dir_x = c.dir_x * cos(c.rspeed) - c.dir_y * sin(c.rspeed);
		c.dir_y = old_dir_x * sin(c.rspeed) + c.dir_y * cos(c.rspeed);
		c.plane_x = c.plane_x * cos(c.rspeed) - c.plane_y * sin(c.rspeed);
		c.plane_y = old_plane_x * sin(c.rspeed) + c.plane_y * cos(c.rspeed);
	}
	g->c = c;
	g->w = w;
	return (0);
}

