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

NAME = minishell

LIBFT = ../libft

LIBFT_A = $(LIBFT)/libft.a
GNL = ../get_next_line
CFLAGS = -Wall -Wextra -Werror -g

LIBS = $(LIBFT_A)

BUILTIN = builtin/builtin_cd.c builtin/builtin_env.c builtin/builtin_setenv.c builtin/builtin_unsetenv.c builtin/builtin_common.c
BUILTIN_O = builtin_cd.o builtin_env.o builtin_setenv.o builtin_unsetenv.o builtin_common.o

SRC = term.c main.c command_parser.c command_parser_bis.c launcher.c environ_research.c utils.c read_line.c completion.c historik.c signal.c
OBJ = $(SRC:.c=.o) $(BUILTIN_O)

all: $(NAME)

$(OBJ):
	gcc $(CFLAGS) -I. -I.. -Ibuiltin -c $(SRC) $(BUILTIN) $(GNL)/get_next_line.c

$(LIBS):
	make -C $(LIBFT) addbonus

$(NAME): $(LIBS) $(OBJ)
	gcc $(CFLAGS) -I. -I.. -Ibuiltin $(OBJ) get_next_line.o $(LIBFT_A) -o $(NAME)

clean:
	rm -f $(OBJ) get_next_line.o
#	make -C $(LIBFT) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all
