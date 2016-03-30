# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/08/11 17:14:40 by fjacquem          #+#    #+#              #
#    Updated: 2015/12/16 00:06:28 by fjacquem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = ../libft
TEST = tests.c
NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror
CC = gcc

SRC = print.c fcts_part1.c fcts_part2.c printer.c
LIBFT_A = $(LIBFT)/libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT_A):
	make -C $(LIBFT) re addbonus

$(OBJ): $(LIBFT_A)
	$(CC) $(FLAGS) -I$(LIBFT) -I. -I.. -c $(SRC)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ) $(LIBFT_A)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f tests

dclean:
	make -C $(LIBFT) fclean

fclean: clean dclean
	/bin/rm -f $(NAME)

re: fclean all

test: $(NAME)
	$(CC) $(FLAGS) $(TEST) $(NAME) $(LIBFT_A) -I. -I.. -o test
	./test

dymlib: $(NAME)
			@echo "May sure to have root permissions"
			sudo cp -f $(NAME) /usr/lib/

dymheader:
			@echo "May sure to have root permissions"
			sudo cp -f print.h /usr/include/libft/
