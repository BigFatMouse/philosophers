NAME = philo
HEADER = philo.h
CC = gcc 
FLAGS = -pthread -Wall -Wextra -Werror 
SRC = philo.c utils.c
	
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(OBJ) -o $(NAME) -lncurses

%.o: %.c $(LIBFT) $(HEADER) 
	$(CC) $(FLAGS) -c $< -o $@
	
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re