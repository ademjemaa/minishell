# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adjemaa <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 21:13:47 by adjemaa           #+#    #+#              #
#    Updated: 2021/02/22 13:42:20 by adjemaa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = minishell

SRCS =	minishell.c\
		parser.c\
		params.c\
		args_split.c\
		cmd_name_proces.c\
		cleaner.c\
		file_retrieve.c\
		execution.c\
		exec_args.c\
		exec_utils.c\
		exec_utils2.c\
		exec_utils3.c\
		quotes2.c\
		tools.c\
		tools_for_tools.c\
		extra_tools.c\
		files.c\
		ft_tools.c\
		free_cmds.c\
		quotes.c\
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c\
		env_changer.c\
		signal_handler.c\
		exec_built_in.c\
		built_in/ft_echo.c\
		built_in/ft_pwd.c\
		built_in/ft_cd.c\
		built_in/ft_exit.c\
		built_in/ft_export.c\
		built_in/ft_unset.c\
		built_in/env_tools.c\
		built_in/ft_env.c\
		built_in/env_tree.c

SRC =		libft/ft_memset.c\
		libft/ft_memcpy.c\
		libft/ft_memccpy.c\
		libft/ft_memmove.c\
		libft/ft_memchr.c\
		libft/ft_memcmp.c\
		libft/ft_strlcat.c\
		libft/ft_isalpha.c\
		libft/ft_isdigit.c\
		libft/ft_isalnum.c\
		libft/ft_isascii.c\
		libft/ft_isprint.c\
		libft/ft_toupper.c\
		libft/ft_tolower.c\
		libft/ft_strchr.c\
		libft/ft_strrchr.c\
		libft/ft_strncmp.c\
		libft/ft_strlcpy.c\
		libft/ft_strnstr.c\
		libft/ft_atoi.c\
		libft/ft_calloc.c\
		libft/ft_strtrim.c\
		libft/ft_split.c\
		libft/ft_itoa.c\
		libft/ft_strmapi.c\
		libft/ft_putchar_fd.c\
		libft/ft_putstr_fd.c\
		libft/ft_putendl_fd.c\
		libft/ft_putnbr_fd.c\
		libft/ft_strjoinfree.c\



OBJECT = $(SRCS:.c=.o)

OBJECT_B = $(SRC:.c=.o)

.c.o :
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): ${OBJECT} ${OBJECT_B}
	$(CC) $(FLAGS) -o $(NAME) ${OBJECT} ${OBJECT_B}

all: $(NAME)

clean:
	@rm -rf $(OBJECT_B)
	@rm -rf $(OBJECT)

fclean : clean 
	@rm -rf $(NAME)

re : fclean all

.PHONY: re clean fclean all bonus
