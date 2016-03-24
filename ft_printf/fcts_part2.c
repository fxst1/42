#include "print.h"

int		ft_vprintf(const char *str, va_list l)
{
	t_printer	tmp;

	init_printer(&tmp, str, l, 1);
	print(&tmp);
	write(tmp.fd, tmp.buffer, tmp.len);
	free(tmp.buffer);
	return (tmp.len);
}

int		ft_vfprintf(const int fd, const char *str, va_list l)
{
	t_printer	tmp;

	init_printer(&tmp, str, l, fd);
	print(&tmp);
	write(tmp.fd, tmp.buffer, tmp.len);
	free(tmp.buffer);
	return (tmp.len);
}

int		ft_svprintf(char *buffer, const char *str, va_list l)
{
	t_printer	tmp;

	init_printer(&tmp, str, l, -1);
	free(tmp.buffer);
	tmp.buffer = buffer;
	tmp.alloc_size = 0;
	print(&tmp);
	va_end(l);
	return (tmp.len);
}

int		ft_fsvprintf(const int fd, char *buffer, const char *str, va_list l)
{
	t_printer	tmp;

	init_printer(&tmp, str, l, fd);
	free(tmp.buffer);
	tmp.buffer = buffer;
	tmp.alloc_size = 0;
	print(&tmp);
	va_end(l);
	return (tmp.len);
}