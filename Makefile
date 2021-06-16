NAME = philosophers

# UTILS =	 \

UTILS_PREFIX = $(addprefix utils/, $(UTILS))

SRC =	main.c \
		# $(UTILS_PREFIX)

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = gcc

INCLUDES = -Iinc

LIBFT = -Ilft/

all: $(NAME)

$(NAME): $(OBJ)
		@make bonus -C lft/
		@$(CC) $(FLAGS) $(OBJ) $(INCLUDES) $(LIBFT) -lft -Llft -g -o $(NAME)

%.o: %.c
		$(CC) $(FLAGS) $(INCLUDES) $(LIBFT) -g -c $< -o $@

clean:
		@make clean -C lft/
		rm -f $(OBJ)

fclean: clean
		@make fclean -C lft/
		rm -f $(NAME)

re: fclean all

