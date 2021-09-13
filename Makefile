NAME =		philo

OBJ_DIR =	obj

UTILS =		utils.c \
			libft_utils.c \
			time_keep.c \
			print_func.c \
			check_func.c

PARSER =	parser.c \
			init_funcs.c

PHILOS =	philos.c \
			actions.c

UTILS_PREFIX = $(addprefix utils/, $(UTILS))

PARSER_PREFIX = $(addprefix parser/, $(PARSER))

PHILOS_PREFIX = $(addprefix philos/, $(PHILOS))

SRC =		main.c \
			$(UTILS_PREFIX) \
			$(PARSER_PREFIX) \
			$(PHILOS_PREFIX)

OBJ =		$(SRC:%.c=$(OBJ_DIR)/%.o)

TAIL =		-pthread

FLAGS =		-Wall -Wextra -Werror

CC =		gcc

INC =		-Iinc

all: $(NAME)

debug: $(OBJ)
	@$(CC) $(FLAGS) -fsanitize=thread -O1 $(OBJ) $(INC) $(TAIL) -g -o $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $^ $(INC) $(TAIL) -o $@
	@echo "Succesfully compiled $(NAME)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "Compiling $@"
	@$(CC) -c $(FLAGS) $(INC) $< $(TAIL) -o $@

clean:
		@rm -rf $(OBJ_DIR)

fclean: clean
		rm -f $(NAME)

re: fclean all

