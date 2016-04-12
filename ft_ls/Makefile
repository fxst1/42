# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/08/11 17:14:40 by fjacquem          #+#    #+#              #
#    Updated: 2016/04/08 16:19:38 by fjacquem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft

NAME = ft_ls
FLAGS = -Wall -Wextra -Werror -g

CC = gcc
SRC = ls.c print.c tools.c file.c extension_map.c main.c print_bis.c opts.c usage.c add_fcts.c initialize.c prt.c
OBJ = $(SRC:.c=.o)
LIBFT_A = $(LIBFT)/libft.a

all: $(NAME)

$(OBJ):
		make -C $(LIBFT) addbonus
		$(CC) $(FLAGS) -I. -I$(LIBFT) -c $(SRC)

$(NAME): $(OBJ)
		$(CC) $(FLAGS) -I. -I$(LIBFT) $(LIBFT_A) $(OBJ)  -o $(NAME)

clean:
		/bin/rm -f $(OBJ)

dclean:
		make -C $(LIBFT) fclean

fclean: dclean clean
		/bin/rm -f $(NAME)

re:		fclean all

bin: $(NAME)
	sudo cp $(NAME) /usr/bin/
