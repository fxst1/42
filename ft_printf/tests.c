#include "print.h"

void	textcolor_format()
{
	int	b;

	b = 0;
	while (b < 255)
	{
		printf("\x1b[38;5;%dm%d\t", b, b);
		if (b % 10 == 0)
			printf(RESET"\n");
		b++;
	}
}

void	backcolor_format()
{
	int	b;

	b = 0;
	while (b < 255)
	{
		ft_printf("\x1b[48;5;%dm%d\t", b, b);
		if (b % 10 == 0)
			printf(RESET"\n");
		b++;
	}
}

void	tests(int max)
{
	int i;

	i = 0;
	printf("len: %zu", ft_strlen(RESET));
	while (i < max)
	{
		printf("\e[%dm%d\t"RESET, i, i);
		if (!(i % 10))
			printf("\n");
		i++;
	}
}

void	ansi_format()
{
	printf("ansi formats compatibilities tests: (char*)\n");
	printf("\033[%smincrease bold (%s)\n%s", INCR_BOLD, INCR_BOLD, RESET);
	printf("\033[%smdecrease bold (%s)\n%s", DECR_BOLD, DECR_BOLD, RESET);
	printf("\033[%smitalic (%s)\n%s", ENABLE_ITALIC, ENABLE_ITALIC, RESET);
	printf("\033[%smcrossed (%s)\n%s", ENABLE_CROSSED, ENABLE_CROSSED, RESET);
	printf("\033[%smfraktur font (%s)\n%s", FRAKTUR_FONT, FRAKTUR_FONT, RESET);
	printf("\033[%smencircled (%s)\n%s", ENABLE_ENCIRCLED, ENABLE_ENCIRCLED, RESET);
	printf("\033[%smunderline (%s) %s\n", ENABLE_UNDERLINE, ENABLE_UNDERLINE, RESET);
	printf("\033[%smframed (%s)%s\n", ENABLE_FRAMED, ENABLE_FRAMED, RESET);
	printf("\033[%smslow blink (%s)%s\n", SLOW_BLINK, SLOW_BLINK, RESET);
	printf("\033[%smrapid blink (%s)%s\n", RAPID_BLINK, RAPID_BLINK, RESET);
	printf("\033[%smreverse back and text (%s)%s\n", ENABLE_REVERSE, ENABLE_REVERSE, RESET);
	printf("\033[%smconceal %s...it 's was conceal :) (%s)\n", ENABLE_CONCEAL, DISABLE_CONCEAL, RESET);
	printf("\033[%smreset\n", "0");
}

void	rgb()
{
	int	r, g, b;

	for(r = 0; r < 6; r++)
	{
		for(g = 0; g < 6; g++)
		{
			for(b = 0; b < 6; b++)
			{
				printf("\033[48;5;%dm  ", r * 36 + g * 6 + b);
			}
			printf(RESET);
		}
		printf("\n");
	}
}

/*
void	test_other(char *str, ...)
{
	char	ret[123];
	va_list	l;

	ft_sprintf(ret, "my ft_sprintf %s\n", "is so great !!!!");
	ft_printf(ret);

	ft_fprintf(1, "i have an fprintf also\n");

	va_start(l, str);
	ft_vprintf(str, l);
	va_end(l);

	ft_printf("and all ft_vXprintf()\n");
}
*/

int main()
{
	printf("Clear screen in 2 seconds ...\n");
	sleep(2);
	printf(CLEAR);
	printf("Is clear ????\n");
	sleep(1);
	printf("\tcolor test\n");
	rgb();
	printf("colors: 0 <= k < 255\nc = red * 36 + green * 6 + blue (color are define between 0 and 7)\n");
	
	printf("text format : 38;5;(integer)\n");
	textcolor_format();
	printf(RESET);
	printf("\n\n");
	
	ft_printf("back format : 48;5;(integer)\n");
	backcolor_format();
	printf(RESET);
	printf("\n\n");

	ansi_format();
	printf("\nTests\n");
	tests(200);
	//printf("\033[%s", ENABLE_REVERSE);
	//test_other("\033[3;38;93m UNICODE : ο Δικαιοπολις εν αγρω εστιν%s\n", RESET);
	return (0);
}
