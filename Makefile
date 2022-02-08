
SRCS = pipex.c pipex_utils.c

NAME = pipex

HEADER = pipex.h

CC = gcc 

OBJ = $(SRCS:c=o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME) 

$(NAME): $(OBJ)
		 @$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.c $(SRCS)
		 @$(CC) $(FLAGS) -c $(SRCS)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re