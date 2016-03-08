NAME = printmem

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror main.c ft_print_memory.c -o $(NAME)

addbin: $(NAME)
	#sudo mkdir /bin/libft
	sudo cp -f $(NAME) /bin/libft

addsys:
	sudo cp -f $(NAME) /bin

clean:
	rm -f $(NAME)

re: clean all
