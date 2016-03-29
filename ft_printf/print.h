#ifndef PRINTF
# define PRINTF
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <libft/master.h>
# define DEFAULT "0"
# define CLEAR "\033[0;0H"
# define INCR_BOLD "1"
# define DECR_BOLD "2"
# define RESET_BOLD "22"
# define ENABLE_ITALIC "3"
# define DISABLE_ITALIC "23"
# define ENABLE_UNDERLINE "4"
# define DISABLE_UNDERLINE "24"
# define SLOW_BLINK "5"
# define RAPID_BLINK "6"
# define DISABLE_BLINK "25"
# define ENABLE_REVERSE "7"
# define DISABLE_REVERSE "27"
# define ENABLE_CONCEAL "8"
# define DISABLE_CONCEAL "28"
# define ENABLE_CROSSED "9"
# define DISABLE_CROSSED "29"
# define DEFAULT_FONT "10"
# define FRAKTUR_FONT "20"
# define RESET_FONT "23"
# define TEXT_COLOR "38"
# define DEFAULT_TEXT_COLOR "37;0"
# define BACK_COLOR "40"
# define DEFAULT_BACK_COLOR "39;0"
# define ENABLE_FRAMED "51"
# define DISABLE_FRAMED "54"
# define ENABLE_ENCIRCLED "52"
# define DISABLE_ENCIRCLED DISABLE_FRAMED
# define ENABLE_OVERLINE "53"
# define DISABLE_OVERLINE "55"
# define RESET_COLOR "39;37"
# define SYSTEM_COLOR
# define BLACK "30"
# define RED "31"
# define GREEN "32"
# define BROWN "33"
# define BLUE "34"
# define MAGENTA "35"
# define CYAN "36"
# define GREY "37"
# define LIGHT_COLOR "01;"
# define LIGHTBLACK "01;30"
# define LIGHTRED "01;31"
# define LIGHTGREEN "01;32"
# define LIGHTBROWN "01;33"
# define LIGHTBLUE "01;34"
# define LIGHTMAGENTA "01;35"
# define LIGHTCYAN "01;36"
# define LIGHTGREY "01;37"
# define DARK_COLOR "22"
# define DARKBLACK "22;30"
# define DARKRED "22;31"
# define DARKGREEN "22;32"
# define DARKBROWN "22;33"
# define DARKBLUE "22;34"
# define DARKMAGENTA "22;35"
# define DARKCYAN "22;36"
# define DARKGREY "22;37"
# define RESET "\x1B[0m"
//ft_printf("no more printf:\n"str,va_l);}
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