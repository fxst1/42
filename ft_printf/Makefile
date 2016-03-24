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

LIBFT = libft
TEST = tests.c
NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror
CC = gcc

SRC = print.c fcts_part1.c fcts_part2.c printer.c
LIBFT_S = $(LIBFT)/ft_atoi.c $(LIBFT)/ft_isdigit.c $(LIBFT)/ft_strcat.c $(LIBFT)/ft_strlen.c $(LIBFT)/ft_strnew.c $(LIBFT)/ft_pow.c $(LIBFT)/ft_memalloc.c $(LIBFT)/ft_bzero.c 
LIBFT_O = ft_atoi.o ft_isdigit.o ft_strcat.o ft_strlen.o ft_strnew.o ft_pow.o ft_memalloc.o ft_bzero.o
LIBFT_A = $(LIBFT)/libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ):
	$(CC) $(FLAGS) -I$(LIBFT) -I. -c $(LIBFT_S)
	$(CC) $(FLAGS) -I$(LIBFT) -I. -c $(SRC)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ) $(LIBFT_O)
	ranlib $(NAME)

clean:
	/bin/rm -f $(LIBFT_O)
	/bin/rm -f $(OBJ)
	/bin/rm -f tests

dclean:
	make -C $(LIBFT) fclean

fclean: clean dclean
	/bin/rm -f $(NAME)

re: fclean all

test: $(NAME)
	$(CC) $(FLAGS) $(TEST) $(NAME) -I. -o test
	./test

dymlib: $(NAME)
			@echo "May sure to have root permissions"
			sudo cp -f $(NAME) /usr/lib/

dymheader:
			@echo "May sure to have root permissions"
			sudo cp -f print.h /usr/include/libft/
