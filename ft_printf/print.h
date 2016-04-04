#ifndef PRINTF
# define PRINTF
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <libft/master.h>

# define ft_vfprintf(fd,str,va_l) ft_fvprintf(fd,str,va_l)
# define ft_vsprintf(buf,str,va_l) ft_svprintf(buf,str,va_l)
# define ft_svfprintf(buf,str,va_l) ft_fsvprintf(buf,str,va_l)  
# define ft_vsfprintf(buf,str,va_l) ft_fsvprintf(buf,str,va_l)
# define ft_sfvprintf(buf,str,va_l) ft_fsvprintf(buf,str,va_l)
# define ft_vfsprintf(buf,str,va_l) ft_fsvprintf(buf,str,va_l)
# define ft_fvsprintf(buf,str,va_l) ft_fsvprintf(buf,str,va_l)

# define INT	1
# define CHAR	2
# define STR	3
# define DOUBLE	4
# define FLOAT	5

# define NORMAL	1
# define LONG	2
# define LLONG	3 

typedef	struct	s_printer
{
	char	*str;
	char	*buffer;
	size_t	alloc_size;
	size_t	len;
	int		type;
	int		cast;
	int		mask;
	int		prec;
	int		spaces;
	struct __va_list_tag *l;
	int		fd;
}				t_printer;

void	init_printer(t_printer *ptr, const char *str, va_list l, const int fd);
void	build_flag(t_printer *ptr);
void	build_str(t_printer *ptr);
void	build_spaces(t_printer *ptr, int expected);
void	printchar(int c, t_printer *tmp);
void	printstr(char *str, t_printer *tmp);
void	printnbr(long long int value, char *base_digits, t_printer *tmp);
void	printdouble(double d, char *base, t_printer *tmp);
void	print(t_printer *ptr);
int		ft_svprintf(char *buffer, const char *str, va_list l);
int		ft_vprintf(const char *str, va_list l);
int		ft_fvprintf(const int fd, const char *str, va_list l);
int		ft_printf(const char *str, ...);
int		ft_fprintf(const int fd, const char *str, ...);
int		ft_sprintf(char *buffer, const char *str, ...);
int		ft_fsvprintf(const int fd, char *buffer, const char *str, va_list l);
int		ft_fsprintf(const int fd, char *buffer, const char *str, ...);
#endif