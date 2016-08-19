#include <graphics.h>

void			draw_vline(t_graphics *g, int x, int drawStart, int drawEnd, int c)
{
	put_pixel(g->buf, x, drawStart, c);
	while (drawStart < drawEnd)
	{
		put_pixel(g->buf, x, drawStart, c);
		drawStart++;
	}
	while (drawStart > drawEnd)
	{
		put_pixel(g->buf, x, drawStart, c);
		drawStart--;
	}
}

static void		ray__init(t_graphics *g, t_camera c, t_ray *r, int x)
{
	r->cam_x = 2 * x / (double)g->buf->l - 1;
	r->pos_x = c.pos_x;
	r->pos_y = c.pos_y;
	r->dir_x = c.dir_x + c.plane_x * r->cam_x;
	r->dir_y = c.dir_y + c.plane_y * r->cam_x;
	r->map_x = (int)r->pos_x;
	r->map_y = (int)r->pos_y;
	r->delta_dist_x = sqrt(1 + (r->dir_y * r->dir_y) / (r->dir_x * r->dir_x));
	r->delta_dist_y = sqrt(1 + (r->dir_x * r->dir_x) / (r->dir_y * r->dir_y));
}

static void		ray__step_and_side(int *step_x, int *step_y, t_ray *r)
{
	if (r->dir_x < 0)
	{
		*step_x = -1;
		r->side_dist_x = (r->pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		*step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - r->pos_x) * r->delta_dist_x;
	}
	if (r->dir_y < 0)
	{
		*step_y = -1;
		r->side_dist_y = (r->pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		*step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - r->pos_y) * r->delta_dist_y;
	}
}

static void		ray__dda(t_graphics *g, t_ray *r, int step_x, int step_y)
{
	int			hit;

	hit = 0;
	while (!hit)
	{
		if (r->side_dist_x < r->side_dist_y)
   		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += step_y;
			r->side = 1;
		}
		if (g->w.walls[r->map_x][r->map_y] > 0)
			hit = 1;
	}
	if (r->side == 0)
		r->wall_dist = (r->map_x - r->pos_x + (1 - step_x) / 2) / r->dir_x;
	else
		r->wall_dist = (r->map_y - r->pos_y + (1 - step_y) / 2) / r->dir_y;

}

void			draw_floor_and_roof(t_buffer *buf)
{
	int x;
	int	y;

	x = 0;
	y = 0;
	while (x < buf->l)
	{
		y = 0;
		while (y < buf->h / 2)
		{
			put_pixel(buf, x, y, 0x111199);
			y++;
		}
		while (y < buf->h)
		{
			put_pixel(buf, x, y, 0x888888);
			y++;
		}
		x++;
	}
}

/*void			draw_texture(t_graphics *g, t_ray *r, int start, int end)
{
	int			tex_num;
	int			tex;
	int			y;

	tex_num = g->w.walls[r->map_x][r->map_y] - 1;
	tex = (int)(wall * g->texture_w);
	if (r->side && r->dir_y < 0)
		tex = g->texture_w - tex - 1;
	if (!r->side && r->dir_x > 0)
		tex = g->texture_w - tex - 1;
	(void)start;
	(void)end;
	(void)tex_num;
}*/

static void		ray__draw(t_graphics *g, t_ray *r, int x)
{
	int 		lineHeight;
	int 		drawStart;
	int 		drawEnd;
	int			wall;
	int			color;

	lineHeight = (int)(g->buf->h / r->wall_dist);
	drawStart = -lineHeight / 2 + g->buf->h / 2;
	drawEnd = lineHeight / 2 + g->buf->h / 2;
	if(drawStart < 0)
		drawStart = 0;
	if(drawEnd >= g->buf->h)
	drawEnd = g->buf->h - 1;
	wall = g->w.walls[r->map_x][r->map_y];
	if (wall == 1)
		color = 0xff0000;
	else if (wall == 2)
		color = 0x00ff00;
	else if (wall == 3)
		color = 0x0000ff;
	else if (wall == 4)
		color = 0xffffff;
	else if (wall == 5)
		color = 0xff1155;
	else if (wall == 6)
		color = 0xdeffef;
	else if (wall == 7)
		color = 0xaaa;
	else
		color = 0x00ffff;
	if (r->side == 1)
		color = color / 2;
	draw_vline(g, x, drawStart, drawEnd, color);
}

static void		ray__draw_texture(t_graphics *g, t_ray *r, int x)
{
	int 		lineHeight;
	int 		drawStart;
	int 		drawEnd;
	int			color;
	int			y;
	int			texNum;
	int			texX;
	double		wallX;

	texNum = g->w.walls[r->map_x][r->map_y] - 1;
	lineHeight = (int)(g->buf->h / r->wall_dist);
	drawStart = -lineHeight / 2 + g->buf->h / 2;
	drawEnd = lineHeight / 2 + g->buf->h / 2;
	if (drawStart < 0)
		drawStart = 0;
	if (drawEnd >= g->buf->h)
	drawEnd = g->buf->h - 1;
	if (r->side == 0)
		wallX = r->pos_y + r->wall_dist * r->dir_y;
	else
		wallX = r->pos_x + r->wall_dist * r->dir_x;
	wallX -= floor(wallX);
	texX = wallX * g->textures_w;
	if (r->side == 0 && r->dir_x > 0)
		texX = g->textures_w - texX - 1;
	if (r->side == 1 && r->dir_y < 0)
		texX = g->textures_w - texX - 1;
	y = drawStart;
	while(y < drawEnd)
	{
		int d = y * 256 - g->buf->h * 128 + lineHeight * 128;
		int texY = ((d * g->textures_h) / lineHeight) / 256;
		if (texNum < MAX_TEXTURES)
	 		color = g->textures[texNum][g->textures_h * texY + texX];
		else
			color = ft_random();
		if (r->side == 1) color = (color >> 1) & 0x7f7f7f;
			put_pixel(g->buf, x, y, color);
		y++;
	}
	(void)x;
}

void			raycasting(t_graphics *g)
{
	int			x;
	int			step_x;
	int 		step_y;
	t_ray		r;
	t_camera	c;

	c = g->c;
	x = 0;
	draw_floor_and_roof(g->buf);
	while (x < g->buf->l)
	{
		ray__init(g, c, &r, x);
		ray__step_and_side(&step_x, &step_y, &r);
		ray__dda(g, &r, step_x, step_y);
		if (!g->textures)
			ray__draw(g, &r, x);
		else
			ray__draw_texture(g, &r, x);
		x++;
	}
	mlx_put_image_to_window(g->mlx, g->screen, g->img, 0, 0);
}
