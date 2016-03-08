#include "print.h"

void		init_printer(t_printer *ptr, const char *str, va_list l, const int fd)
{
	ptr->str = (char*)str;
	ptr->buffer = ft_strnew(1024);
	ptr->alloc_size = 1024;
	ptr->len = 0;
	ptr->mask = 0;
	ptr->spaces = 0;
	ptr->prec = 6;
	ptr->l = (struct __va_list_tag*)l;
	ptr->fd = (int)fd;
}

void		build_spaces(t_printer *ptr, int expected)
{
	if (ptr->mask & 32 && ptr->mask & 1)
		ptr->mask -= 32;
	if (ptr->mask & 1 && ptr->mask & 4)
	{
		ptr->mask -= 1;
		ptr->mask |= 32;
	}
	if (ptr->mask & 8)
	{
		printchar('+', ptr);
		expected++;
	}
	if (ptr->mask & 32 || ptr->mask & 1)
	{
		if (ptr->spaces >= expected)
			while (ptr->spaces - expected > 0)
			{
				printchar((ptr->mask & 32) ? (' ') : ('0') , ptr);
				ptr->spaces--;
			}
		else
			printchar((ptr->mask & 32) ? (' ') : ('0') , ptr);
	}
	ptr->spaces = 0;
}

void		build_flag(t_printer *ptr)
{
	ptr->mask = 0;
	while ((*ptr->str == ' ' || *ptr->str == '+' || *ptr->str == '-' ||
		*ptr->str == '0' || *ptr->str == '#') && ptr->mask >= 0)
	{
		if (*ptr->str == ' ' && !(ptr->mask & 32))
			ptr->mask |= 32;
		else if (*ptr->str == '-' && !(ptr->mask & 4))
			ptr->mask |= 4;
		else if (*ptr->str == '+' && !(ptr->mask & 8))
			ptr->mask |= 8;
		else if (*ptr->str == '#' && !(ptr->mask & 16))
			ptr->mask |= 16;
		else if (*ptr->str == '0' && !(ptr->mask & 1))
			ptr->mask |= 1;
		else
			ptr->mask = -1;
		ptr->str++;
	}
	if (ptr->mask & 32 && (ptr->mask & 4 || ptr->mask & 8))
		ptr->mask -= 32;
	ptr->spaces = ft_atoi(ptr->str);
	while (ft_isdigit(*ptr->str))
		ptr->str++;
}

void	build_str(t_printer *ptr)
{
	char				*str;
	long int			value;

	value = 0;
	str = ptr->str;
	if (*str == 'd' || *str == 'D' || *str == 'i')
		printnbr(va_arg(*(va_list*)ptr->l, int), BASE_DEC, ptr);
	else if (*str == 'c' || *str == 'C')
		printchar(va_arg(*(va_list*)ptr->l, int), ptr);
	else if (*str == 's' || *str == 'S')
		printstr(va_arg(*(va_list*)ptr->l, char*), ptr);
	else if (*str == 'u' || *str == 'U')
		printnbr(va_arg(*(va_list*)ptr->l, unsigned int), BASE_DEC, ptr);
	else if (*str == 'p' || *str == 'P')
	{
		value = va_arg(*(va_list*)ptr->l, unsigned long int);
		if (value)
		{
			printstr((*str == 'P') ? "0X" : "0x", ptr);
			printnbr(value, (*str == 'P') ? BASE_HEX_MAJ : BASE_HEX_MIN, ptr);
		}
		else
			printstr("(nil)", ptr);
	}
	else if (*str == 'x' || *str == 'X')
	{
		if (ptr->mask & 16)
			printstr((*str == 'X') ? "0X" : "0x", ptr);
		printnbr(va_arg(*(va_list*)ptr->l, unsigned int), (*str == 'X') ? BASE_HEX_MAJ : BASE_HEX_MIN, ptr);
	}
	else if (*str == 'o')
		printnbr(va_arg(*(va_list*)ptr->l, int), BASE_OCT, ptr);
	else if (*str == 'b')
		printnbr(va_arg(*(va_list*)ptr->l, int), BASE_BIN, ptr);
	else if (*str == 'f' || *str == 'F')
		printdouble(va_arg(*(va_list*)ptr->l, double), BASE_DEC, ptr);
	else if (*str == 'v')
		ft_vprintf(va_arg(*(va_list*)ptr->l, char*), *va_arg(*(va_list*)ptr->l, va_list*));
	else if (*str == 'a')
		ft_printf("\x1B[%sm", va_arg(*(va_list*)ptr->l, char*));
	else if (*str == 'k' || *str == 'K')
	{
		value = va_arg(*(va_list*)ptr->l, int);
		if (value == 0)
			ft_printf("\x1B[0m");
		else if (*str == 'K')
			ft_printf("\x1B[48;5;%dm", value);
		else
			ft_printf("\x1B[38;5;%dm", value);
	}
}
