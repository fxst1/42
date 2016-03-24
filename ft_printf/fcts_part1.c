#include "print.h"

int		ft_printf(const char *str, ...)
{
	va_list		l;
	t_printer	tmp;

	if (str)
	{
		va_start(l, str);
		init_printer(&tmp, str, l, 1);
		print(&tmp);
		va_end(l);
		write(tmp.fd, tmp.buffer, tmp.len);
		free(tmp.buffer);
	}
	return (tmp.len);
}

int		ft_fprintf(const int fd, const char *str, ...)
{
	va_list		l;
	t_printer	tmp;

	if (str)
	{
		va_start(l, str);
		init_printer(&tmp, str, l, fd);
		print(&tmp);
		va_end(l);
		write(tmp.fd, tmp.buffer, tmp.len);
		free(tmp.buffer);
	}
	return (tmp.len);
}

int		ft_sprintf(char *buffer, const char *str, ...)
{
	va_list		l;
	t_printer	tmp;

	if (str)
	{
		va_start(l, str);
		init_printer(&tmp, str, l, -1);
		if (buffer)
		{
			free(tmp.buffer);
			tmp.buffer = buffer;
			tmp.alloc_size = 0;
		}
		print(&tmp);
		va_end(l);
	}
	return (tmp.len);
}

int		ft_fsprintf(int	fd, char *buffer, const char *str, ...)
{
	va_list		l;
	t_printer	tmp;

	if (str)
	{
		va_start(l, str);
		init_printer(&tmp, str, l, fd);
		if (buffer)
		{
			free(tmp.buffer);
			tmp.buffer = buffer;
			tmp.alloc_size = 0;
		}
		print(&tmp);
		va_end(l);
	}
	return (tmp.len);
}

int		ft_sfprintf(int	fd, char *buffer, const char *str, ...)
{
	va_list		l;
	t_printer	tmp;

	if (str)
	{
		va_start(l, str);
		init_printer(&tmp, str, l, fd);
		if (buffer)
		{
			free(tmp.buffer);
			tmp.buffer = buffer;
			tmp.alloc_size = 0;
		}
		print(&tmp);
		va_end(l);
	}
	return (tmp.len);
}
