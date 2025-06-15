CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = philo_bonus.c ./helper_bonus/philo_utils_bonus.c ./parser_bonus/parser_bonus.c ./helper_bonus/philo_routine_bonus.c ./helper_bonus/philo_routine_utils_bonus.c ./init_bonus/init_bonus.c\
		./utils_bonus/ft_isspace.c ./utils_bonus/ft_isdigit.c ./utils_bonus/ft_atoi.c ./utils_bonus/ft_putchar_fd.c ./utils_bonus/ft_putendl_fd.c ./utils_bonus/ft_putstr_fd.c\

OBJ = $(SRC:.c=.o)

all: philo_bonus

philo_bonus: $(OBJ) philo_bonus.h
	$(CC) $(CFLAGS) $(OBJ) -o philo_bonus

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f philo_bonus

re: fclean all

.PHONY: clean