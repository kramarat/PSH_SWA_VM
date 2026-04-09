NAME = push_swap

CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC = push_swap.c aux_push.c aux_reverse_rotate.c aux_rotate.c aux_swap.c \
	stack_utils.c sorting.c sorting_common.c sorting_rotate.c sorting_simple.c \
	sorting_index.c sorting_insertion.c sorting_medium.c sorting_complex.c \
	parsing.c bench.c ft_split.c string_utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re