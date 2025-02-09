CC = cc
FLAGS = -Wall -Wextra -Werror
FILES = free.c get_path.c main.c utils.c
OBJ = $(FILES:.c=.o)
NAME = pipex
HEADER = pipex.h

# Add libft paths
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

# Rules
all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re