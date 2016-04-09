NAME = minishell

LIBFT = ../libft

LIBFT_A = $(LIBFT)/libft.a
GNL = ../get_next_line
CFLAGS = -Wall -Wextra -Werror

LIBS = $(LIBFT_A)
BUILTIN = builtin/builtin_cd.c builtin/builtin_env.c builtin/builtin_setenv.c
SRC = term.c env.c main.c config.c $(BUILTIN)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ):
	gcc $(CFLAGS) -I. -I.. -c $(SRC) $(GNL)/get_next_line.c

$(LIBS):
	make -C $(LIBFT) addbonus

$(NAME): $(LIBS) $(OBJ)
	gcc $(CFLAGS) -I. -I.. $(OBJ) get_next_line.o $(LIBFT_A) -o $(NAME)

clean:
	rm -f $(OBJ) get_next_line.o
#	make -C $(LIBFT) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all