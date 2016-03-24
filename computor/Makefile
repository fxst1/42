NAME = computor
OBJ = computor.o
SRC = computor.c

all: $(NAME)

$(OBJ):
	make -C ../libft 
	gcc -Wall -Wextra ../libft/libft.a -c $(SRC) -lm	

$(NAME): $(OBJ)
	gcc -Wall -Wextra -o $(NAME) ../libft/libft.a $(OBJ) -lm

clean:
	rm -f $(NAME)
	
fclean: clean
	rm -f $(OBJ)
	
re: fclean all
