# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjacquem <fjacquem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/08/11 17:14:40 by fjacquem          #+#    #+#              #
#    Updated: 2016/04/08 16:25:25 by fjacquem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

CC = gcc
SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memdel.c\
	ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c \
	ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strstr.c \
	ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
	ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
	ft_memalloc.c ft_strnew.c ft_strdel.c ft_strclr.c \
	ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c \
	ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c \
	ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
	ft_lstmap.c ft_memccpy.c
BONUS_FCT = ft_strsort.c ft_putansi_str.c ft_getenv.c
BONUS_MAP = ft_mapnew.c ft_mapdel.c ft_mapget.c ft_mapadd_at.c ft_mapadd_begin.c ft_mapadd_end.c
BONUS_ALL = $(SRC) $(BONUS_FCT) $(BONUS_MAP)

OBJ = $(SRC:.c=.o)
OBJ_FCT = $(BONUS_FCT:.c=.o)
OBJ_MAP = $(BONUS_MAP:.c=.o)

all: $(NAME)

$(OBJ):
		@$(CC) $(FLAGS) -c $(SRC)

$(NAME): $(OBJ)
		@ar rc $(NAME) $(OBJ)
		@echo "\033[38;5;27mLibft essentisials added\033[0m"
		@ranlib $(NAME)

clean:
		@rm -f $(OBJ)
		@rm -f $(OBJ_MAP)
		@rm -f $(OBJ_FCT)

fclean: clean
		@rm -f $(NAME)

re:		fclean all

$(OBJ_FCT):
		@$(CC) $(FLAGS) -c $(BONUS_FCT)
		@ar rc $(NAME) $(OBJ_FCT) $(OBJ)
		@echo "\033[38;5;76mFunctions implementation added\033[0m"
		@ranlib $(NAME)

$(OBJ_MAP):
		@$(CC) $(FLAGS) -c $(BONUS_MAP)
		@ar rc $(NAME) $(OBJ_MAP) $(OBJ)
		@echo "\033[38;5;76mGeneric map added\033[0m"
		@ranlib $(NAME)

addmap: $(NAME) $(OBJ_MAP)

addfct: $(NAME) $(OBJ_FCT)

addbonus: $(NAME) $(OBJ_MAP) $(OBJ_FCT)

.PHONY: addmap addstack addbonus addgc addbtree re fclean clean all 
