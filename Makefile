NAME = philo

CC = cc

CFLAGS = -g -Wall -Wextra -Werror

SRCS =	src/main.c			\
		src/utils.c			\
		src/set_values.c	\
		src/exit.c			\

OBJ_DIR = objs

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

norm:
	@if norminette | grep -q "Error"; then \
		echo "Norminette: \033[31m[KO]\033[0m"; \
		norminette | grep "Error"; \
	else \
		echo "Norminette: \033[32m[OK]\033[0m"; \
	fi

.PHONY: all fclean clean re
