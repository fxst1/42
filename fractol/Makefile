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

LIB = -lm -lmlx -framework OpenGL -framework AppKit -lpthread -O3
SRC = fractal.c env.c main.c common.c music_init.c

HEAD = -I$(LIBFT) -I$(GNL) -I /usr/X11/include
LIB_A = $(LIBFT)/libft.a
OBJ = $(SRC:.c=.o)

SDL2		= -framework SDL2
SDL2_MIXER  = -framework SDL2_mixer

SDL2_HEADER			= -I ~/Library/Frameworks/SDL2.framework/Headers/
SDL2_HEADER_MIXER   = -I ~/Library/Frameworks/SDL2_mixer.framework/Headers/

SDL         = -F ~/Library/Frameworks $(SDL2_MIXER) $(SDL2)
SDL_HEADER  = -F ~/Library/Frameworks $(SDL2_HEADER_MIXER) $(SDL2_HEADER)

all : $(NAME)

$(LIB_A):
	make -C $(LIBFT) addfct

$(OBJ):
	gcc $(FLAGS) -I.. -I. $(HEAD) $(SDL_HEADER) -c $(SRC)

$(NAME): $(LIB_A) $(OBJ)
	gcc $(FLAGS) -I.. -I. $(OBJ) $(LIB_A) $(HEAD) -o $(NAME) $(LIB) $(SDL) $(SDL_HEADER)

clean:
		rm -f $(OBJ)

fclean: clean
#		make -C $(LIBFT) fclean
		rm -f $(NAME)

re: fclean all

sdl_install :
	curl https://dl.dropboxusercontent.com/u/22561204/SDL/Archive.zip > /tmp/Archive.zip
	unzip -o /tmp/Archive.zip -d ~/Library/Frameworks/