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
CMD_DIR =		cmdline
LEXER_DIR =		lexer
COMMON_DIR =	common
INCLUDE_DIR =	headers
OBJ_DIR =		obj


# compilation
NAME =		minishell
CFLAGS =	-Wall -Wextra -Werror -g
HEADS = 	-I$(INCLUDE_DIR) -I$(LIBFT_DIR) 
LIBFT_A =	$(LIBFT_DIR)/libft.a


# special builtins
SPEC_BUILTIN_DIR =	$(BUILTIN_DIR)/supl
EXPLORER_DIR =		$(SPEC_BUILTIN_DIR)/explorer


# explorer
EXPLORER_SRC =	add_fcts.c extension_map.c file.c explorer.c initialize.c\
				ls.c opts.c print.c print_bis.c tools.c
EXPLORER_OBJ =	$(EXPLORER_SRC:.c=.o)


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


# minishell command line
CMD_SRC =	read_line.c init_cmdline.c ctrl_inputs.c cmd_utils.c
CMD_OBJ =	$(CMD_SRC:.c=.o)

# minishell lexer
LEXER_SRC =	command.c lexer.c word.c redirection.c parse.c
LEXER_OBJ =	$(LEXER_SRC:.c=.o)

# minishell implementation
FEATURES_SRC =	command_parser.c command_parser_bis.c environ_research.c\
				completion.c historik.c completion_utils.c
FEATURES_OBJ =	$(FEATURES_SRC:.c=.o)


# minishell
COMMON_SRC =	term.c main.c launcher.c utils.c signal.c\
				term_utils.c
COMMON_OBJ =	$(COMMON_SRC:.c=.o)


# ...
SRCS =	$(addprefix $(GNL_DIR)/,$(GNL_SRC))\
		$(addprefix $(BUILTIN_DIR)/,$(BUILTIN_SRC))\
		$(addprefix $(FEATURES_DIR)/,$(FEATURES_SRC))\
		$(addprefix $(CFG_DIR)/,$(CFG_SRC))\
		$(addprefix $(CMD_DIR)/,$(CMD_SRC))\
		$(addprefix $(COMMON_DIR)/,$(COMMON_SRC))\
		$(addprefix $(EXPLORER_DIR)/,$(EXPLORER_SRC))\
		$(addprefix $(LEXER_DIR)/,$(LEXER_SRC))
OBJS =	$(COMMON_OBJ)\
		$(FEATURES_OBJ)\
		$(BUILTIN_OBJ)\
		$(GNL_OBJ)\
		$(CFG_OBJ)\
		$(CMD_OBJ)\
		$(EXPLORER_OBJ)\
		$(LEXER_OBJ)
OBJS_MOVED =	$(addprefix $(OBJ_DIR)/,$(OBJS))

all: $(NAME)

$(OBJS_MOVED): $(LIBFT_A)
	gcc $(CFLAGS) $(HEADS) -c $(SRCS)
	mv $(OBJS) $(OBJ_DIR)

$(LIBFT_A):
	make -C $(LIBFT_DIR) addbonus

$(NAME): $(OBJS_MOVED)
	gcc $(CFLAGS) $(HEADS) $(OBJS_MOVED) $(LIBFT_A) -o $(NAME)

clean:
	rm -f $(OBJ_DIR)/$(OBJS)
#	make -C $(LIBFT_DIR) clean

fclean:
	rm -rf $(OBJ_DIR)/$(OBJS)
	rm -f $(NAME)
#	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
