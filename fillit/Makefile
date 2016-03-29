CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = fillit

LIBFT = libft
LIB_S = $(LIBFT)/ft_strlen.c $(LIBFT)/ft_memset.c $(LIBFT)/ft_putchar.c $(LIBFT)/ft_putchar_fd.c $(LIBFT)/ft_putendl_fd.c $(LIBFT)/ft_memcpy.c $(LIBFT)/ft_putnbr.c $(LIBFT)/ft_putnbr_fd.c $(LIBFT)/ft_putstr.c $(LIBFT)/ft_putstr_fd.c
LIB_O = ft_strlen.o ft_memset.o ft_putchar.o ft_putchar_fd.o ft_putendl_fd.o ft_memcpy.o ft_putnbr.o ft_putnbr_fd.o ft_putstr.o ft_putstr_fd.o
SRC = start.c fillit.c solv.c aff.c algorithms.c init.c move_item.c
OBJ = start.o fillit.o solv.o aff.o algorithms.o init.o move_item.o
INC = head.h

all: $(NAME)

$(OBJ):
	$(CC) $(CFLAGS) -I. -c $(SRC)
	$(CC) $(CFLAGS) -I. -c $(LIB_S)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB_O) -o $(NAME)

clean:
	rm -f $(OBJ) $(LIB_O)

fclean: clean
	rm -f $(NAME)

re: fclean all