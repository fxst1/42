#include "print.h"

void	printchar(int c, t_printer *tmp)
{
	tmp->buffer[tmp->len++] = c;
}

void	printstr(char *str, t_printer *tmp)
{
	if (str)
	{
		ft_strcat(tmp->buffer, str);
		tmp->len += ft_strlen(str);
	}
	else
	{
		ft_strcat(tmp->buffer, "(null)");
		tmp->len += 6;
	}
}

void	printnbr(long long int value, char *base_digits, t_printer *tmp)
{
	int		i;
	int		k;
	int		neg;
	int		base;

	base = ft_strlen(base_digits);
	i = 1;
	neg = 0;
	if (value < 0)
	{
		neg = (base == 10);
		value *= -1;
	}
	while (ft_pow(base, i) - 1 < value)
		i++;
	k = i + neg;
	build_spaces(tmp, k);
	tmp->buffer[tmp->len + k] = '\0';
	while (k-- > 0)
	{
		tmp->buffer[tmp->len + k] = base_digits[value % base];
		value = value / base;
	}
	if (neg)
		tmp->buffer[tmp->len] = '-';
	tmp->len += i + neg;
}

void		printdouble(double d, char *base, t_printer *tmp)
{
	int		i;

	i = 0;
	printnbr((int)d, base, tmp);
	printchar('.', tmp);
	d -= (int)d;
	while (i++ < tmp->prec)
	{
		d *= 10;
		if ((int)d == 0)
			printchar('0', tmp);
	}
	if (d - (int)d > 0.5)
		d++;
	printnbr((int)d, BASE_DEC, tmp);
}

void	print(t_printer *ptr)
{
	while (*ptr->str)
	{
		if (*ptr->str == '%')
		{
			ptr->str++;
			build_flag(ptr);
			while (*ptr->str == 'l')
					ptr->str++;
			build_str(ptr);
		}
		else
			ptr->buffer[ptr->len++] = *ptr->str;
		ptr->str++;
	}
}
