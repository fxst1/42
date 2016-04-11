#include "fdf.h"

int			mlx_key_number(int keycode)
{
	static int	value = 0;
	int			nums[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
	int			tmp;

	printf("<%d>\n", value);
	tmp = 0;
	while (tmp < 10 && nums[tmp] != keycode)
		tmp++;
	if (tmp < 10)
	{
		value *= 10;
		value += tmp;		
	}
	else
	{
		tmp = value;
		value = 0;
		printf("value = %d\n", value);
		return (tmp);
	}
	return (value);	
}
