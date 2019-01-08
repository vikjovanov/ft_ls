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

SRCS= ft_ls.c
SRCS_DIR= $(addprefix srcs/, $(SRCS))

INCLUDES= -Iincludes -Ilibft/includes

FLAGS= -Wall -Werror -Wextra

$(NAME):
	@make -C libft/ && make -C libft/ clean
	@gcc $(FLAGS) $(SRCS_DIR) $(LIBFT_LIB) $(INCLUDES)