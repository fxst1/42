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

NAME = ft_select

FLAGS = -Wall -Wextra -Werror

CC = gcc

SRC = select.c libft.c select_2.c select_3.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(OBJ):
	$(CC) -I. $(FLAGS) -c $(SRC)

$(NAME): $(OBJ)
	$(CC) -I. $(FLAGS) $(OBJ) -o $(NAME) -ltermcap

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:		fclean all
