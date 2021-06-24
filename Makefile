NAME = philosophers

OBJ_DIR = obj

UTILS =		utils.c

PARSER =	parser.c

PHILOS =	init_philos.c

UTILS_PREFIX = $(addprefix utils/, $(UTILS))

PARSER_PREFIX = $(addprefix parser/, $(PARSER))

PHILOS_PREFIX = $(addprefix philos/, $(PHILOS))

SRC =	main.c \
		$(UTILS_PREFIX) \
		$(PARSER_PREFIX) \
		$(PHILOS_PREFIX)

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

FLAGS = -Wall -Wextra -Werror

CC = gcc

INCLUDES = -Iinc

LIBFT = -Ilft/

all: $(NAME)

$(NAME): $(OBJ)
		@make bonus -C lft/
		@$(CC) $(FLAGS) $(OBJ) $(INCLUDES) $(LIBFT) -lft -Llft -g -o $(NAME)

$(OBJ_DIR)/%.o: %.c
		@mkdir -p $(@D)
		$(CC) $(FLAGS) $(INCLUDES) $(LIBFT) -g -c $< -o $@

clean:
		@make clean -C lft/
		@rm -rf $(OBJ_DIR)

fclean: clean
		@make fclean -C lft/
		rm -f $(NAME)

re: fclean all

