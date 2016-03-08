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

LIBFT = ~/Documents/42/libft
PRINTF = ~/Documents/42/ft_printf

NAME = ft_ls
FLAGS = -Wall -Wextra -Werror

CC = gcc
SRC = ls.c print.c tools.c file.c extension_map.c
OBJ = $(SRC:.c=.o)
LIBFT_A = $(LIBFT)/libft.a
PRINTF_A = $(PRINTF)/libftprintf.a

all: $(NAME)

#$(LIBFT_A):
#		make -C $(LIBFT)
#
#$(PRINTF_A):
#		make -C $(PRINTF)

$(OBJ):
		$(CC) $(FLAGS) -I. -I$(LIBFT) -I$(PRINTF) -c $(SRC) -lft -lftprintf

$(NAME): $(OBJ)
		$(CC) $(FLAGS) -I. -I$(LIBFT) -I$(PRINTF) $(OBJ) -o $(NAME) -lft -lftprintf

clean:
		/bin/rm -f $(OBJ)

dclean:
		make -C $(PRINTF) fclean
		make -C $(LIBFT) fclean

fclean: clean
		/bin/rm -f $(NAME)

re:		fclean all
