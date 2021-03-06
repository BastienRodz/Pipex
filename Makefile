# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/15 17:18:05 by barodrig          #+#    #+#              #
#    Updated: 2021/11/04 14:23:32 by barodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL	= /bin/sh

NAME = pipex

CC = clang -Wall -Wextra -Werror

INC= -I./includes

BONUS= bonus/main.c srcs/ft_errors_manager.c srcs/ft_execute_cmds.c\

SRCS = 	main ft_errors_manager ft_execute_cmds\

FIL = $(addsuffix .c, $(addprefix srcs/, $(SRCS)))

OBJ = $(FIL:.c=.o)

OBJ_BONUS = $(BONUS:.c=.o)

.c.o:
	-@${CC} ${INC} -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling libft..."
	@make -s -C ./libft
	@echo "--> [OK]"
	@echo "Compiling pipex...."
	-@$(CC) $(INC) $(OBJ) -Llibft -lft -o $(NAME)
	@echo "--> [OK]"
	@echo "Now write : ./pipex file1 | cmd1 | cmd2 | cmd... | cmdX | file2"

bonus: $(NAME)_bonus

$(NAME)_bonus : $(OBJ_BONUS)
	@echo "Compiling libft..."
	@make -s -C ./libft
	@echo "--> [OK]"
	@echo "Compiling pipex with bonus...."
	-@$(CC) $(INC) $(OBJ_BONUS) -Llibft -lft -o $(NAME)_bonus
	@echo "--> [OK]"
	@echo "Now write : ./pipex file1 | cmd1 | cmd2 | cmd... | cmdX | file2"

clean:
	@echo "CLEANING ..."
	@make -s clean -C ./libft
	@rm -rf $(OBJ) $(OBJ_BONUS)
	@echo "--> [OK]"

fclean: clean
	@make -s fclean -C ./libft
	@rm -f $(NAME)
	@rm -f $(NAME)_bonus

re: fclean all

.PHONY: all clean fclean re bonus
