SRC = main.c tools.c

FLAG = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

NAME = Fdf

LIBMLX = /usr/local/lib -lmlx -framework OpenGL -framework AppKit

LIBFT = ./libft/libft.a

INCLUDE = /usr/local/include  ./libft/libft.h
all: $(NAME)

$(NAME):
	gcc -c $(FLAG) $(SRC) -I $(INCLUDE)
	gcc $(FLAG) $(OBJ) -o $(NAME) -L $(LIBMLX)  $(LIBFT)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
