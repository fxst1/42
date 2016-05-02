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
BONUS_STACK = ft_stknew.c ft_stkinit.c ft_stkempty.c ft_stkfull.c ft_stkclear.c\
	ft_stkpop.c ft_stkpush.c
BONUS_BTREE = ft_btreenew.c ft_btreeadd.c ft_btreefree.c ft_btreeforeach.c
BONUS_FCT = ft_keep.c ft_strclen.c ft_build_cmd.c\
	ft_getenv.c ft_lstfree.c ft_lstsize.c ft_lstadd_begin.c ft_strcasecmp.c\
	ft_atoi_casebase.c ft_atoi_base.c ft_isspace.c ft_random.c ft_memndel.c\
	ft_strsort.c ft_strsplit_cmd.c ft_strcut.c ft_putansi_str.c ft_putansi_nbr.c\
	ft_setfilename.c ft_realloc.c ft_abs.c ft_swap.c ft_putnstr.c ft_pow.c\
	ft_putnbr_base_fd.c ft_putnbr_base.c ft_itoa_base.c ft_print_memory.c\
	ft_strrev.c ft_putdouble.c ft_puthex.c ft_swapn.c ft_swaplen.c ft_strnword.c
BONUS_MAP = ft_mapnew.c ft_mapdel.c ft_mapget.c ft_mapadd_at.c ft_mapadd_begin.c ft_mapadd_end.c
BONUS_GARBAGE = ft_gc.c ft_gcnew.c ft_gcdym.c ft_gcref.c ft_gcadd.c ft_gcstop.c ft_gcprint.c
BONUS_ALL = $(SRC) $(BONUS_FCT) $(BONUS_MAP) $(BONUS_STACK) $(BONUS_BTREE) $(BONUS_GARBAGE)

OBJ = $(SRC:.c=.o)
OBJ_FCT = $(BONUS_FCT:.c=.o)
OBJ_STACK = $(BONUS_STACK:.c=.o)
OBJ_BTREE = $(BONUS_BTREE:.c=.o)
OBJ_MAP = $(BONUS_MAP:.c=.o)
OBJ_GARBAGE = $(BONUS_GARBAGE:.c=.o)

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
		@rm -f $(OBJ_BTREE)
		@rm -f $(OBJ_STACK)
		@rm -f $(OBJ_GARBAGE)

fclean: clean
		@rm -f $(NAME)

re:		fclean all

dymlib: $(NAME)
		@echo "\033[38;5;1mMay sure to have root permissions\033[0m"
		@sudo rm -f usr/lib/libft.a
		@sudo cp -f $(NAME) /usr/lib/

dymheader:
		@echo "\033[38;5;1mMay sure to have root permissions\033[0m"
		@sudo rm -f /usr/include/libft/libft.h /usr/include/libft/implemt.h /usr/include/libft/btree.h /usr/include/libft/stack.h /usr/include/libft/gc.h
		@sudo cp -f libft.h os.h master.h map.h btree.h implemt.h stack.h gc.h /usr/include/libft/
		@sudo chmod 644 /usr/include/libft/*.h

$(OBJ_STACK):
		@$(CC) $(FLAGS) -c $(BONUS_STACK)
		@ar rc $(NAME) $(OBJ_STACK) $(OBJ)
		@echo "\033[38;5;76mGeneric stack added\033[0m"
		@ranlib $(NAME)

$(OBJ_BTREE):
		@$(CC) $(FLAGS) -c $(BONUS_BTREE)
		@ar rc $(NAME) $(OBJ_BTREE) $(OBJ)
		@echo "\033[38;5;76mGeneric binary tree added\033[0m"
		@ranlib $(NAME)

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

$(OBJ_GARBAGE):
		@$(CC) $(FLAGS) -c $(BONUS_GARBAGE)
		@ar rc $(NAME) $(OBJ_GARBAGE) $(OBJ) $(OBJ_FCT)
		@echo "\033[38;5;76mGarbage collector added\033[0m"
		@ranlib $(NAME)

addmap: $(NAME) $(OBJ_MAP)

addstack: $(NAME) $(OBJ_STACK)

addbtree: $(NAME) $(OBJ_BTREE)

addfct: $(NAME) $(OBJ_FCT)

addgc: $(NAME) $(OBJ_FCT) $(OBJ_GARBAGE)

addbonus: $(NAME) $(OBJ_MAP) $(OBJ_FCT) $(OBJ_STACK) $(OBJ_GARBAGE) $(OBJ_BTREE)

.PHONY: addmap addstack addbonus addgc addbtree re fclean clean all 
