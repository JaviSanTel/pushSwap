NAME		= push_swap
LIBFT_DIR	= ./LIBFT
LIBFT		= $(LIBFT_DIR)/libft.a
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f

SRC =	parser.c \
		utils.c \
		flags.c \
		list_utils.c \
		sort_simple.c \
		sort_small.c \
		chunk.c \
		chunk_utils.c \
		radix.c \
		special_sort.c \
		dispatch.c \
		run_sort.c \
		bench.c \
		disorder.c \
		psindex.c \
		move_swap.c \
		move_push.c \
		move_rotate.c \
		move_reverse_rotate.c \
		op_utilsa.c \
		op_utilsb.c \
		main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(LIBFT_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
