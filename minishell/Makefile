NAME = minishell

LIBFT = ../libft

LIBFT_A = $(LIBFT)/libft.a
GNL = ../get_next_line
CFLAGS = -Wall -Wextra -Werror

LIBS = $(LIBFT_A)
SRC = term.c env.c main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ):
	gcc $(CFLAGS) -I. -I.. -c $(SRC) $(GNL)/get_next_line.c

$(LIBS):
	make -C $(LIBFT) addbonus

$(NAME): $(LIBS) $(OBJ)
	gcc $(CFLAGS) -I. -I.. $(OBJ) get_next_line.o $(LIBFT_A) -o $(NAME)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)

re: fclean all