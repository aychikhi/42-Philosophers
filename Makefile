CC = cc
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

SRC = ./mandatory/mandatory.c ./utils/ft_putendl_fd.c ./utils/ft_putchar_fd.c ./utils/ft_putstr_fd.c ./utils/ft_isdigit.c ./utils/ft_isspace.c\
		./utils/ft_atoi.c ./mandatory/check_args.c ./mandatory/routine.c\

OBJ = $(SRC:.c=.o)

all: philosopher

philosopher: $(OBJ) header.h
	$(CC) $(CFLAGS) $(OBJ) -o philo

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f philo

re: fclean all

.PHONY: clean
