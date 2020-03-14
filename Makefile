# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 21:13:47 by adjemaa           #+#    #+#              #
#    Updated: 2019/11/13 12:17:26 by abarbour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = minishell

SRCS =	minishell.c\
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c


OBJECT = $(SRCS:.c=.o)

OBJECT_B = $(BS:.c=.o)

$(NAME):
	@$(CC) $(FLAGS) $(SRCS) libft/libft.a libft/libft.h

all: $(NAME)

clean:
	@rm -rf $(NAME)

fclean : clean 
	@rm -rf $(NAME)

re : fclean all

.PHONY: re clean fclean all bonus
