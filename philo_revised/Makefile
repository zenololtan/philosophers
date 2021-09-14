# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: zenotan <zenotan@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/09/14 22:01:26 by zenotan       #+#    #+#                  #
#    Updated: 2021/09/15 00:24:41 by zenotan       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		philo

OBJ_DIR =	obj

SRC =		main.c \
			libft_utils.c \
			utils.c \
			timekeep.c \
			parser.c \
			philo.c \
			actions.c \
			print.c

OBJ =		$(SRC:%.c=$(OBJ_DIR)/%.o)

TAIL =		-pthread

FLAGS =		-Wall -Wextra -Werror

CC =		gcc

all: $(NAME)

debug: $(OBJ)
	@$(CC) $(FLAGS) -fsanitize=thread -O1 $(OBJ) $(TAIL) -g -o $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $^ $(TAIL) -o $@
	@echo "Succesfully compiled $(NAME)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@echo "Compiling $@"
	@$(CC) -c $(FLAGS) $< $(TAIL) -o $@

clean:
		@rm -rf $(OBJ_DIR)

fclean: clean
		rm -f $(NAME)

re: fclean all

