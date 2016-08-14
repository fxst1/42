#ifndef CAMERA_H
# define CAMERA_H
# include <time.h>
typedef struct	s_camera
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		speed;
	double		rspeed;
	double		plane_x;
	double		plane_y;
}				t_camera;

/*
**	Camera
*/
t_camera		new_camera();
void			init_camera(t_camera *c, int reset);
void			set_speed(t_camera *c);

#endif
