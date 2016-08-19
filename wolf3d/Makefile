# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/14 22:50:59 by fjacquem          #+#    #+#              #
#    Updated: 2016/04/14 22:51:01 by fjacquem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# compilation
CC =			cc
NAME =			wolf3d
CFLAGS =		-Wall -Wextra -Werror -g
LINK =			-lmlx -lX11 -lXext -lm -lgnl -lft

# directories
SRC_DIR =		./src/
LIB_DIR =		./libft/
GNL_DIR =		./get_next_line/
GRAPHICS_DIR =	./src/graphics/
ENGINE_DIR =	./src/engine/
INC_DIR =	./includes/
OBJ_DIR =		./obj/

HEADS = 		-I$(INC_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR)

GRAPHICS_SRC =	start_graphics.c stop_graphics.c expose.c draw.c point.c raycasting.c\
				textures.c
GRAPHICS_OBJ =	$(GRAPHICS_SRC:.c=.o)

ENGINE_SRC =	event.c init_world.c camera.c
ENGINE_OBJ =	$(ENGINE_SRC:.c=.o)

# [...]
SRCS = main.c
OBJS = $(GRAPHICS_SRC:.c=.o) $(SRCS:.c=.o) $(ENGINE_SRC:.c=.o)
SRC = $(addprefix $(SRC_DIR), $(SRCS))
OBJ = $(addprefix $(OBJ_DIR), $(OBJS))
INC = $(addprefix -I, $(INC_DIR))
INC += $(addprefix -I, $(LIB_DIR))

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_DIR)
	$(CC) $(CFLAGS) $(HEADS) $(OBJ) -o $(NAME) $(LINK)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(GRAPHICS_DIR)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)%.o: $(ENGINE_DIR)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIB_DIR) clean

fclean:
	rm -rf $(OBJ)
	rm -f $(NAME)
	make -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
