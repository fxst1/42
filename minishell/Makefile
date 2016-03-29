NAME = minishell

LIBFT = ../libft
PRINT = ../ft_printf

LIBFT_A = $(LIBFT)/libft.a
PRINT_A = $(PRINT)/libftprintf.a

CFLAGS = -Wall -Wextra -Werror

LIBS = $(LIBFT_A) $(PRINT_A)
SRC = term.c env.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ):
	gcc $(CFLAGS) -I. -c $(SRC) -lft

$(LIBS):
	make -C $(LIBFT) addbonus
	make -C $(PRINT)

$(NAME): $(LIBS) $(OBJ)
	gcc $(CFLAGS) -I. $(OBJ) -o $(NAME) -lgnl -lft -lftprintf 

clean:
	make -C $(PRINT) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(PRINT) fclean
	rm -f $(NAME)

re: fclean all