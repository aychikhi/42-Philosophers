NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = philo.c ./helper/philo_routine.c ./helper/philo_utils.c ./helper/philo_utils1.c ./helper/philo_routine_utils.c ./parser/parser.c ./init/init_fun.c ./utils/ft_atoi.c\
		./utils/ft_isdigit.c ./utils/ft_isspace.c ./utils/ft_putchar_fd.c ./utils/ft_putstr_fd.c ./utils/ft_putendl_fd.c ./utils/ft_strcmp.c\

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) philo.h
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean