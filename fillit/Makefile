CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = fillit

SRC = start.c fillit.c solv.c aff.c algorithms.c init.c move_item.c libft.c
OBJ = $(SRC:.c=.o)
INC = head.h

all: $(NAME)

$(OBJ):
	$(CC) $(CFLAGS) -I. -c $(SRC)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all