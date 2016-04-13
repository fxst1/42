# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/08/11 17:14:40 by fjacquem          #+#    #+#              #
#    Updated: 2016/04/11 20:15:37 by fjacquem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

LIBFT = ../libft
GNL = ../get_next_line
MLX = /usr/x11/lib

FLAGS = -Wall -Wextra

LIB = -lm -lmlx -framework OpenGL -framework AppKit -lpthread
SRC = fractal.c env.c main.c common.c

HEAD = -I$(LIBFT) -I$(GNL)
LIB_A = $(LIBFT)/libft.a
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(LIB_A):
	make -C $(LIBFT) addfct

$(OBJ):
	gcc $(FLAGS) -I.. -I. $(HEAD) -c $(SRC)

$(NAME): $(LIB_A) $(OBJ)
	gcc $(FLAGS) -I.. -I. $(OBJ) $(LIB_A) $(HEAD) -o $(NAME) $(LIB)

clean:
		rm -f $(OBJ)

fclean: clean
#		make -C $(LIBFT) fclean
		rm -f $(NAME)

re: fclean all
