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
PRINTF = ../ft_printf
GNL = ../get_next_line

NAME = ft_ls
FLAGS = -Wall -Wextra -Werror

CC = gcc
SRC = ls.c print.c tools.c file.c extension_map.c main.c print_bis.c sort_fcts.c sort_parse_os.c opts.c usage.c
OBJ = $(SRC:.c=.o)
LIBFT_A = $(LIBFT)/libft.a

all: $(NAME)

$(OBJ):
		make -C $(LIBFT) addbonus
		$(CC) $(FLAGS) -I. -I$(LIBFT) -I$(PRINTF) -I$(GNL) -I.. -c $(SRC) $(GNL)/get_next_line.c

$(NAME): $(OBJ)
		$(CC) $(FLAGS) -I. -I$(LIBFT) -I$(PRINTF) $(LIBFT_A) -I.. $(OBJ) get_next_line.o -o $(NAME)

clean:
		/bin/rm -f $(OBJ) get_next_line.o

#dclean:
#		make -C $(PRINTF) fclean
#		make -C $(LIBFT) fclean

fclean: clean
		/bin/rm -f $(NAME)

re:		fclean all

bin: $(NAME)
	sudo cp $(NAME) /usr/bin/