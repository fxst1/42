#include "print.h"

void	textcolor_format()
{
	int	b;

	b = 0;
	while (b < 255)
	{
		ft_printf("%k%d\t", b, b);
		if (b % 10 == 0)
			ft_printf("%s\n%a%a", RESET, ENABLE_ITALIC, ENABLE_UNDERLINE);
		b++;
	}
}

void	backcolor_format()
{
	int	b;

	b = 0;
	while (b < 255)
	{
		ft_printf("%K%d\t", b, b);
		if (b % 10 == 0)
			ft_printf("%s\n%a%a", RESET, ENABLE_ITALIC, ENABLE_UNDERLINE);
		b++;
	}
}


void	ansi_format()
{
	ft_printf("ansi format (some test can fail): %%a(char*)\n");
	ft_printf("%aincrease bold\n%s", INCR_BOLD, RESET);
	ft_printf("%adecrease bold\n%s", DECR_BOLD, RESET);
	ft_printf("%aitalic\n%s", ENABLE_ITALIC, RESET);
	ft_printf("%acrossed\n%s", ENABLE_CROSSED, RESET);
	ft_printf("%afraktur font\n%s", FRAKTUR_FONT, RESET);
	ft_printf("%aencircled\n%s", ENABLE_ENCIRCLED, RESET);
	ft_printf("%aunderline%s\n", ENABLE_UNDERLINE, RESET);
	ft_printf("%aframed%s\n", ENABLE_FRAMED, RESET);
	ft_printf("%aslow blink%s\n", SLOW_BLINK, RESET);
	ft_printf("%arapid blink%s\n", RAPID_BLINK, RESET);
	ft_printf("%areverse back and text%s\n", ENABLE_REVERSE, RESET);
	ft_printf("%aconceal%s...it 's was conceal :)\n", ENABLE_CONCEAL, RESET);
	ft_printf("%areset\n", "0");
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
				ft_printf("%K  ", r * 36 + g * 6 + b);
			}
			ft_printf(RESET);
		}
		ft_printf("\n");
	}
}

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

int main()
{
	ft_printf("\tcolor test\n");
	rgb();
	ft_printf("colors: 0 <= k < 255\nc = red * 36 + green * 6 + blue (color are define between 0 and 7)\n");
	
	ft_printf("text format : %%k(integer)\n");
	textcolor_format();
	ft_printf(RESET);
	ft_printf("\n\n");
	
	ft_printf("back format : %%K(integer)\n");
	backcolor_format();
	ft_printf(RESET);
	ft_printf("\n\n");

	ansi_format();
	ft_printf("\nclear screen in 2 seconds...");
	sleep(2);
	ft_printf("%a", ENABLE_REVERSE);
	test_other("%K%a UNICODE : ο Δικαιοπολις εν αγρω εστιν%s\n", 93, ENABLE_ITALIC, RESET);
	return (0);
}