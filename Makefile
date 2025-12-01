NAME := philo
SRC := main.c mutex.c philo.c
SRC_DIR := src
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

HEADER := include/$(NAME).h
OBJ_DIR := obj
LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a
INC := -I./include -I$(LIBFT_DIR)/include

CFLAGS := -Wall -Wextra -Werror

.PHONY: all clean fclean re bonus

all: $(NAME)

bonus: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS) $(OBJ) -L./$(LIBFT_DIR) -lft -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	cc $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
