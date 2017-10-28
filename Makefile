# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcharloi <jcharloi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/01 10:06:17 by jcharloi          #+#    #+#              #
#    Updated: 2017/10/25 18:37:02 by jcharloi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = lem-in

SRC_PATH = ./sources/
SRC_NAME = main.c
OBJ_PATH = ./objects/
OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_PATH = ./sources/libft/
LIB_NAME = ./sources/libft/libft.a
PRINT_NAME = ./sources/libft/ft_printf/libftprintf.a

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

YELLOW = "\033[3;38;5;228m"
ORANGE = "\033[3;38;5;214m"
RED = "\033[3;5;49;31m"
PURPLE = "\033[3;49;35m"
BLUE = "\033[3;5;49;34m"
GREEN = "\033[3;33;32m"
EOC = "\033[0m"

all: creation
	@make $(NAME)

creation:
	@make -C $(LIB_PATH)
	@echo $(PURPLE)"Your $(LIB_NAME) AND your $(PRINT_NAME) are (al)ready to work !"$(EOC)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@echo $(BLUE)"Your folder $(OBJ_PATH) is (already) created !"$(EOC)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LIB_NAME) $(PRINT_NAME) $(CFLAGS)
	@echo $(GREEN)"Your ./$(NAME) is ready to work ! ✅"$(EOC)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) -o $@ -c $< $(CFLAGS)
	@echo $(ORANGE)"Your ./$(OBJ_NAME) is compiled !"$(EOC)

clean:
	@make clean -C $(LIB_PATH)
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo $(YELLOW)"Make clean done !"$(EOC)

fclean: clean
	@make fclean -C $(LIB_PATH)
	@rm -f $(NAME)
	@echo $(RED)"Make fclean done !"$(EOC)

re: fclean all

.PHONY: clean fclean re all