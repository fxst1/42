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

/*
Mix_Music	*start_music(char *filename)
{
	Mix_Music	*music;

	music = NULL;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != -1)
	{
		printf("start %s\n", filename);
		music = Mix_LoadMUS(filename);
		ft_print_memory(music, sizeof(music));
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
}*/

void	audioCallback()
{
	printf("callback\n");
}
/*
typedef struct			s_sound
{
	double				stream_len;
	double				rate;
	double				frame_rate;
	int					spf;	//sample per frame
	double				mspf;	//ms per frame
	SDL_AudioSpec		spec;
	SDL_AudioSpec		want;
	SDL_AudioDeviceID	device;
	SDL_atomic_t		audioCallbackLeftOff;
	int32_t				audioMainLeftOff;
	float				*buffer;
	size_t				buffer_len;
}						t_sound;

void	common_sound_init(t_env *e, t_sound *s)
{
	s->spec.freq = 22050;
	s->spec.format = 2;
	s->spec.samples = 4096;
	s->spec.callback = audioCallback;
	s->spec.userdata = e;
}

int	init_music(t_sound *s)
{
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_TIMER);
    SDL_zero(s->want);

	s->want.freq = s->rate;
	s->want.format = AUDIO_F32;
	s->want.channels = 2;
	s->want.samples = s->stream_len;
	s->want.callback = audioCallback;
	s->device = SDL_OpenAudioDevice(NULL, 0, &s->want, &s->spec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
	if (!s->device)
	{
        printf("\nFailed to open audio: %s\n", SDL_GetError());
		return 1;
    }
    if (s->spec.format != s->want.format) {
        printf("\nCouldn't get Float32 audio format.\n");
        return 2;
    }
    s->rate = s->spec.freq;
    s->stream_len = s->spec.size / 4;
    s->spf = s->rate / s->frame_rate;
    s->mspf = 1000 / s->frame_rate;
    s->audioMainLeftOff = s->spf * 8;
    SDL_AtomicSet(&s->audioCallbackLeftOff, 0);

    if (s->buffer_len % s->spf)
        s->buffer_len += s->spf - (s->buffer_len % s->spf);
    s->buffer = malloc(sizeof(float) * s->buffer_len);
}

void	test(t_sound *s)
{

}
*/









