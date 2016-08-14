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

CC = gcc
FLAGS = -Wall -Wextra -Werror -g -O3
NAME = fractol
LINK = -lmlx -lXext -lX11 -lm -lft

LIBFT_DIR = ./libft/
INC_DIR = ./include/
OBJ_DIR = ./obj/
SRC_DIR = ./src/

SRCS =	main.c common.c\
		fractal.c env.c\
		mlx_++/mlx_get_str.c\
		music_init.c

SRC = $(addprefix $(SRC_DIR), $(SRCS))
OBJS = $(addsuffix .o, $(basename $(SRCS)))
OBJ = $(addprefix $(OBJ_DIR), $(notdir $(OBJS)))

VPATH = $(shell find $(SRC_DIR) -type d)

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) -I $(INC_DIR) -I . $(LIBFT_DIR)libft.a $(OBJ) -o $(NAME) $(LINK)

$(OBJ_DIR)%.o: %.c
	@mkdir $(OBJ_DIR) 2> /dev/null || echo "" > /dev/null
	$(CC) $(FLAGS) -I $(INC_DIR) -I . -c $< -o $@

clean:
	@rm -vrf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean:
	@rm -vrf $(OBJ_DIR)
	@rm -vf $(NAME)

re: fclean all

sdl_install:
	curl https://dl.dropboxusercontent.com/u/22561204/SDL/Archive.zip > /tmp/Archive.zip
	unzip -o /tmp/Archive.zip -d ~/Library/Frameworks/