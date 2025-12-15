NAME := philo
SRC := main.c mutex.c philo.c printp.c
SRC_DIR := src
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

HEADER := include/$(NAME).h
OBJ_DIR := obj
INC := -I./include

CFLAGS := -Wall -Wextra -Werror

.PHONY: all clean fclean re bonus

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	cc $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
