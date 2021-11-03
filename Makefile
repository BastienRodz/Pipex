# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/15 17:18:05 by barodrig          #+#    #+#              #
#    Updated: 2021/11/03 10:57:18 by barodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL	= /bin/sh

OS	:= $(shell uname -s)

NAME = pipex

CC = clang -g3 -Wall -Wextra -Werror

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

bonus: $(OBJ_BONUS)
	@echo "Compiling libft..."
	@make -s -C ./libft
	@echo "--> [OK]"
	@echo "Compiling pipex with bonus...."
	-@$(CC) $(INC) $(OBJ_BONUS) -Llibft -lft -o $(NAME)
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

re: fclean all

.SILENT: clean

.PHONY: all clean fclean re bonus
