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

SRCS= ft_ls.c arg_checker.c generic_func.c order_by.c error.c
SRCS_LIST_FUNC= lst_dir.c lst_dir_ext.c lst_file.c lst_file_ext.c

SRCS_DIR= $(addprefix srcs/, $(SRCS))
SRCS_LIST_FUNC_DIR = $(addprefix srcs/list_func/, $(SRCS_LIST_FUNC))

INCLUDES= -Iincludes -Ilibft/includes

CC= gcc

CFLAGS= -Wall -Werror -Wextra

all:
	@make -C libft/ && make -C libft/ clean
	@$(CC) $(CFLAGS) $(SRCS_DIR) $(SRCS_LIST_FUNC_DIR) $(LIBFT_LIB) $(INCLUDES) -o ft_ls



clean: 


fclean: 

re: 