# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/15 17:18:05 by barodrig          #+#    #+#              #
#    Updated: 2021/10/25 13:50:43 by barodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL	= /bin/sh

OS	:= $(shell uname -s)

NAME = pipex

CC = clang -g3 -Wall -Wextra -Werror

INC= -I./includes

SRCS = 	main ft_errors_manager\

FIL = $(addsuffix .c, $(addprefix srcs/, $(SRCS)))

OBJ = $(FIL:.c=.o)

BIN = $(addsuffix .o, $(SRCS))

BIN_BONUS = $(addsuffix .o, $(BONUS))

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

clean:
	@echo "CLEANING ..."
	@make -s clean -C ./libft
	@rm -rf $(OBJ)
	@echo "--> [OK]"

fclean: clean
	@make -s fclean -C ./libft
	@rm -f $(NAME)

re: fclean all

.SILENT: clean

.PHONY: all clean fclean re bonus
