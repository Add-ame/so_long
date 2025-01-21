CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ./src/check_map.c ./src/get_next_line.c ./src/get_next_line_utils.c ./src/handle_key.c ./src/so_long.c \
		./src/tools_1.c ./src/tools.c ./src/valid_map.c 
OBJ = $(SRC:.c=.o)
NAME = so_long

GREEN = \033[1;32m
PURPLE = \033[1;35m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $^ -lmlx -L/usr/include/minilibx-linux/ -lXext -lX11 -o $@
	@sleep 1
	@echo "$(GREEN)Compilation complete for mandatory!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -Imlx_Linux  -o $@

clean:
	@echo "$(PURPLE)Cleaned!$(RESET)"
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

aclean: all clean

.PHONY: all clean aclean fclean
