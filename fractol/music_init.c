#include "env.h"

void	random_animation(t_env *e)
{
	e->s = ((int)ft_random()) % 256;
	e->h = ((int)ft_random()) % 256;
	e->v = ((int)ft_random()) % 256;
	//e->nb_iter = ((int)ft_random) % 200;
	//e->re = ((int)ft_random ) / 1000;
	//e->im = ((int)ft_random) / 1000;
}

static int	get_keycode(int keycode, int *tab, int size, int *end)
{
	int	index;

	index = 0;
	*end = 0;
	while (index < size && tab[index] != keycode)
		index++;
	return (index);
}

char		*mlx_key_str(int keycode, int *end)
{
	static int		n = 0;
	static char		*str = NULL;
	static int		keys[38] = {65, DIVIDE, ZERO, ONE, TWO, THREE, FOUR,
	FIVE, SIX, SEVEN, EIGHT, NINE, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F,
	KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P,
	KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z};
	int				tmp;
	char			*sw;

	tmp = get_keycode(keycode, keys, 38, end);
	if (tmp < 38 && n < 1022)
	{
		str = (!str) ? ft_strnew(1024) : str;
		if (tmp < 2)
			str[n++] = (tmp == 0) ? '.' : '/';
		else
			str[n++] = (tmp < 12) ? (tmp - 2) + '0' : (tmp - 12) + 'a';
	}
	else if (str && (sw = ft_strdup(str)))
	{
		n = 0;
		ft_memdel((void**)&str);
		*end = 1;
	}
	return ((*end) ? sw : str);
}

Mix_Music	*start_music(char *filename)
{
	Mix_Music	*music;

	music = NULL;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != -1)
	{
		printf("start %s\n", filename);
		music = Mix_LoadMUS(filename);
		Mix_PlayMusic(music, -1);
	}
	else
		ft_putstr(Mix_GetError());
	return (music);
}

void	*stop_music(Mix_Music *music)
{
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	return (NULL);
}