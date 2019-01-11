# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/08 10:01:54 by vjovanov          #+#    #+#              #
#    Updated: 2019/01/08 10:01:55 by vjovanov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= ft_ls

LIBFT_NAME= libft
LIBFT_LIB= libft/libft.a

SRCS= ft_ls.c arg_checker.c generic_func.c
SRCS_DIR= $(addprefix srcs/, $(SRCS))

SRCS_LIST_FUNC= lst_dir.c lst_dir_ext.c
SRCS_LIST_FUNC_DIR = $(addprefix srcs/list_func/, $(SRCS_LIST_FUNC))

INCLUDES= -Iincludes -Ilibft/includes

FLAGS= -Wall -Werror -Wextra

$(NAME):
	@make -C libft/ && make -C libft/ clean
	@gcc $(FLAGS) $(SRCS_DIR) $(SRCS_LIST_FUNC_DIR) $(LIBFT_LIB) $(INCLUDES)