CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

SRC = main.c ./utils/ft_putendl_fd.c ./utils/ft_putchar_fd.c ./utils/ft_putstr_fd.c ./utils/ft_isdigit.c ./utils/ft_isspace.c\
		./utils/ft_atoi.c check_args.c routine.c routine_utils.c ./utils/ft_strcmp.c philo_utils.c philo_utils1.c\

OBJ = $(SRC:.c=.o)

all: philo

philo: $(OBJ) philosopher.h
	$(CC) $(CFLAGS) $(OBJ) -o philo

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f philo

re: fclean all

.PHONY: clean
