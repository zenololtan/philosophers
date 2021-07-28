NAME =		philosophers
OBJ_DIR =	obj

UTILS =		utils.c

PARSER =	parser.c

PHILOS =	init_philos.c

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

LFT =		-Ilft

all: $(NAME)

debug: $(OBJ)
		@make bonus -C lft/
		@clang $(FLAGS) -fsanitize=thread $(OBJ) $(INC) $(LFT) -lft -Llft $(TAIL) -g -o $(NAME)

$(NAME): $(OBJ)
	@make bonus -C lft/
	@$(CC) $(FLAGS) $^ $(INC) $(LFT) $(TAIL) -lft -Llft -o $@
	@echo "Succesfully compiled $(NAME)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "Compiling $@"
	@$(CC) -c $(FLAGS) $(INC) $(LFT) $< $(TAIL) -o $@

clean:
		@make clean -C lft/
		@rm -rf $(OBJ_DIR)

fclean: clean
		@make fclean -C lft/
		rm -f $(NAME)

re: fclean all

