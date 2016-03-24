LIBFT = ../libft
LIBFT_A = $(LIBFT)/libft.a

SRC = push.c
NAME = inter_push_swap

all: $(NAME)

$(LIBFT_A):
	make -C $(LIBFT) re addbonus

$(NAME): $(LIBFT_A)
	gcc -Wall -Wextra -Werror -I. $(LIBFT_A) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

re: clean all

