CC = gcc
CFLAGS = -Wall -Wextra
NAME = fillit

LIBFT = ~/Documents/42/libft
SRC = start.c fillit.c solv.c aff.c algorithms.c init.c move_item.c
INC = head.h
LIB = 

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) $(LIBFT)/ft_strlen.c $(LIBFT)/ft_memset.c $(LIBFT)/ft_putchar.c $(LIBFT)/ft_putchar_fd.c $(LIBFT)/ft_putendl_fd.c $(LIBFT)/ft_memcpy.c $(LIBFT)/ft_putnbr.c $(LIBFT)/ft_putnbr_fd.c $(LIBFT)/ft_putstr.c $(LIBFT)/ft_putstr_fd.c -o $(NAME) $(LIB)

clean:
	rm -f $(NAME)

re: clean all