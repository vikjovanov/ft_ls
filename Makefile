# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/08 10:01:54 by vjovanov          #+#    #+#              #
#    Updated: 2019/01/20 11:47:21 by vjovanov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= ft_ls

LIBFT_NAME= libft
LIBFT_LIB= libft/libft.a

SRCS= ft_ls.c arg_checker.c generic_func.c error.c main_printer.c recurse_nav.c \
		gen_printer.c
SRCS+= list_func/lst_dir.c list_func/lst_dir_ext.c \
		list_func/lst_file.c list_func/lst_file_ext.c list_func/lst_fill_file.c
SRCS+= order/order_by.c order/lst_order_file.c order/order_by_time.c
SRCS_DIR=srcs/


OBJ= $(SRCS:.c=.o)
OBJ_DIR=obj/
OBJS_DIR=$(addprefix $(OBJ_DIR),$(OBJ))

INCLUDES= -Iincludes -Ilibft/includes

CC= gcc
CFLAGS= -Wall -Werror -Wextra

GCCRESET=\033[0m
GCCBLUE=\033[1;36m
GCCBRED=\033[1;91m
GCCYELLOW=\033[1;33m
GCCGREEN=\033[1;32m
GCCRED=\033[1;31m
GCCMAGENTA=\033[1;35m

all:
	@mkdir -p $(OBJ_DIR)
	@make $(NAME)

$(NAME): $(OBJS_DIR)
	@make -C libft/
	@$(CC) $(CFLAGS) $(OBJS_DIR) $(LIBFT_LIB) $(INCLUDES) -o $(NAME)
	@echo "$(GCCMAGENTA)$(basename $(NAME)): $(GCCRESET)$(GCCGREEN)SUCCESS$(GCCRESET)"

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GCCMAGENTA)$(basename $(NAME)): $(GCCRESET)Compilation $(GCCGREEN)-- $(basename $(notdir $<))$(GCCRESET)"

clean: 
	@make -C libft/ clean
	@rm -Rf $(OBJ_DIR)
	@echo "$(GCCMAGENTA)$(basename $(NAME)): $(GCCRESET)Suppression $(GCCRED)-- $(OBJ_DIR)$(GCCRESET)"

fclean:
	@make -C libft/ fclean
	@echo "$(GCCMAGENTA)$(basename $(NAME)): $(GCCRESET)Suppression $(GCCRED)-- $(NAME)$(GCCRESET)"
	@rm -Rf $(NAME)
	@echo "$(GCCMAGENTA)$(basename $(NAME)): $(GCCRESET)Suppression $(GCCRED)-- $(OBJ_DIR)$(GCCRESET)"
	@rm -Rf $(OBJ_DIR)

re: fclean all