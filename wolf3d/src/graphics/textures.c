#include <graphics.h>

int			**load_textures(t_graphics *g, int ***texture, int w, int h)
{
	int		x;
	int		y;
	int		xorcolor;
	int		xycolor;
	int		ycolor;

	*texture = (int**)malloc(sizeof(int*) * MAX_TEXTURES);
	x = 0;
	while (x < MAX_TEXTURES)
		(*texture)[x++] = malloc(sizeof(int) * w * h);
	g->textures_w = w;
	g->textures_h = h;	
	x = 0;
	while (x < w)
	{
		y = 0;
		while (y < h)
		{
			xorcolor = (x * 256 / w) ^ (y * 256 / h);
			ycolor = y * 256 / h;
 			xycolor = y * 128 / h + x * 128 / w;
		    (*texture)[0][w * y + x] = 65536 * 254 * (x != y && x != w - y); //flat red texture with black cross
 			(*texture)[1][w * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
 			(*texture)[2][w * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
 			(*texture)[3][w * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
 			(*texture)[4][w * y + x] = 256 * xorcolor; //xor green
			(*texture)[5][w * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			(*texture)[6][w * y + x] = 65536 * ycolor; //red gradient
			(*texture)[7][w * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
			(*texture)[8][w * y + x] = x % 16 + y % 16;
			y++;
		}
		x++;
	}
	return (*texture);
}
