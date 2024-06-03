NAME	= philo
CC		= cc
RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror #-fsanitize=thread -pthread

SRC =	src/free.c \
		src/init.c \
		src/main.c \
		src/situation.c \
		src/simulation.c \
		src/utils.c \
		src/utils1.c

OBJ_DIR = .objs

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

norm:
	@if norminette | grep -q "Error"; then \
		echo "Norminette: \033[31m[KO]\033[0m"; \
		norminette | grep "Error"; \
	else \
		echo "Norminette: \033[32m[OK]\033[0m"; \
	fi

.PHONY: all fclean clean re
