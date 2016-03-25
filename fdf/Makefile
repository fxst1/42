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

NAME = fdf

LIBFT = ./../libft
GNL = ./../get_next_line
MLX = /usr/x11/lib

FLAGS = -Wall -Wextra -Werror
LIB = -lmlx -framework OpenGL -framework AppKit

SRC = 	./fdf_bis.c\
		./color.c\
		./env.c	\
		./opts.c	\
		./fdf.c 			\
		./matrix.c		\
		./init.c			\
		./draw.c			\
		./event.c		\
		$(GNL)/get_next_line.c		\
		./main.c				\
		$(LIBFT)/libft.a

HEAD = -I$(LIBFT) -I$(GNL)
LIB_A = $(LIBFT)/libft.a
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(LIB_A):
	make -C $(LIBFT) addbonus

$(NAME): $(LIB_A)
	@gcc $(FLAGS) $(SRC) -I $(HEAD) $(LIB) -o $(NAME)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all
