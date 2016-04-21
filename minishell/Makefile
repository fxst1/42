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

# directories
LIBFT_DIR =		../libft
GNL_DIR =		../get_next_line
CFG_DIR =		configs
BUILTIN_DIR =	builtin
FEATURES_DIR =	features

# compilation
NAME =		minishell
CFLAGS =	-Wall -Wextra -Werror -g
HEADS = 	-I. -I$(BUILTIN_DIR) -I$(CFG_DIR) -I$(FEATURES_DIR) -I.. -I$(GNL_DIR)
LIBFT_A =	$(LIBFT_DIR)/libft.a

# necessairy for configs
GNL_SRC =	get_next_line.c
GNL_OBJ =	get_next_line.o

# minishell configs
CFG_SRC =	init_menu.c menu_process.c menu_utils.c init_menuitem.c minicfg.c
CFG_OBJ =	$(CFG_SRC:.c=.o)

# minishell builtins
BUILTIN_SRC =	builtin_cd.c builtin_env.c builtin_setenv.c builtin_common.c\
				builtin_unsetenv.c
BUILTIN_OBJ =	$(BUILTIN_SRC:.c=.o)

# minishell implementation
FEATURES_SRC =	command_parser.c command_parser_bis.c environ_research.c\
				completion.c historik.c completion_utils.c
FEATURES_OBJ =	$(FEATURES_SRC:.c=.o)

# minishell
COMMON_SRC =	term.c main.c launcher.c utils.c read_line.c signal.c\
				term_utils.c
COMMON_OBJ =	$(COMMON_SRC:.c=.o)

# ...
SRCS =	$(addprefix $(GNL_DIR)/,$(GNL_SRC))\
		$(addprefix $(BUILTIN_DIR)/,$(BUILTIN_SRC))\
		$(addprefix $(FEATURES_DIR)/,$(FEATURES_SRC))\
		$(addprefix $(CFG_DIR)/,$(CFG_SRC))\
		$(COMMON_SRC)
OBJS =	$(COMMON_OBJ) $(FEATURES_OBJ) $(BUILTIN_O) $(GNL_O) $(CFG_O)

all: $(NAME)

$(OBJS):
	gcc $(CFLAGS) $(HEADS) -c $(SRCS)

$(LIBFT_A):
	make -C $(LIBFT_DIR) addbonus

$(NAME): #$(LIBFT_A) $(OBJS)
	gcc $(CFLAGS) $(HEADS) $(SRCS) $(LIBFT_A) -o $(NAME)

clean:
	rm -f $(OBJS)
#	make -C $(LIBFT_DIR) clean

fclean:
	rm -rf $(OBJS)
	rm -f $(NAME)
#	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
