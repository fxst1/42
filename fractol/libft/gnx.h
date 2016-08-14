#ifndef GNX_H
# define GNX_H
# include "get_next_line.h"
# define gnl(fd,l) get_next_line(fd,line)
# define gni(fd,i) get_next_integer(fd,i)
# define gnib(fd,i,b) get_next_integer(fd,i,b)

int		get_next_integer(const int fd, int *addr);
int		get_next_integer_base(const int fd, int *addr, char *base);

#endif