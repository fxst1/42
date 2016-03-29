NAME = minishell

LIBFT = ../libft
PRINT = ../ft_printf

LIBFT_A = $(LIBFT)/libft.a

CFLAGS = -Wall -Wextra -Werror

LIBS = $(LIBFT_A)
SRC = term.c env.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ):
	gcc $(CFLAGS) -I. -I.. $(LIBFT_A) -c $(SRC)

$(LIBS):
	make -C $(LIBFT) addbonus
	make -C $(PRINT)

$(NAME): $(LIBS) $(OBJ)
	gcc $(CFLAGS) -I. -I.. $(OBJ) -o $(NAME)

clean:
	make -C $(PRINT) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(PRINT) fclean
	rm -f $(NAME)

re: fclean all