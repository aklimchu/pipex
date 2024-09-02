# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 11:18:05 by aklimchu          #+#    #+#              #
#    Updated: 2024/09/02 08:11:17 by aklimchu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		= pipex
NAME_B		= pipex_bonus

# Compiler
CC 			= cc
CFLAGS		= -Wall -Wextra -Werror -I $(LIBFT_DIR)
RM			= rm -f

# Libft
LIBFT_DIR	= libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

# Source / OBJ files / Includes
SRC 		= ./src/main.c ./src/path.c \
			./src/ft_strjoin_new.c \
			./src/free_all.c ./src/count_param.c \
			./src/child_process_1.c \
			./src/child_process_2.c ./src/printing.c \
			./src/tools.c ./src/ft_split_new.c
OBJ 		= $(SRC:.c=.o)
INCLUDE		= -I "./inc"

# Source / OBJ files / Includes for bonus
SRC_B 		= ./src_bonus/main_bonus.c ./src_bonus/path.c \
			./src_bonus/ft_strjoin_new.c \
			./src_bonus/free_all_bonus.c \
			./src_bonus/count_param.c \
			./src_bonus/child_process_bonus.c \
			./src_bonus/last_process_bonus.c \
			./src_bonus/printing.c \
			./src_bonus/tools.c ./src_bonus/ft_split_new.c
OBJ_B 		= $(SRC_B:.c=.o)
INCLUDE_B	= -I "./inc_bonus"

# Rules
all:		$(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) $(INCLUDE) $^ -c -o $@

$(NAME):	$(OBJ)
	@make -C $(LIBFT_DIR)		# make libft
	@cp $(LIBFT_LIB) $(NAME)	# copy libft to current
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(INCLUDE) -o $(NAME)

# Rules bonus
bonus:		$(NAME_B)

%.o: %.c 
	$(CC) $(CFLAGS) $(INCLUDE_B) $^ -c -o $@

$(NAME_B):	$(OBJ_B)
	@make -C $(LIBFT_DIR)		# make libft
	@cp $(LIBFT_LIB) $(NAME_B)	# copy libft to current
	@$(CC) $(CFLAGS) $(OBJ_B) $(LIBFT_LIB) $(INCLUDE_B) -o $(NAME_B)

clean:
	$(RM) $(OBJ) $(OBJ_B)
	@make clean -C $(LIBFT_DIR)

fclean:		clean 
	$(RM) $(NAME) $(NAME_B) $(LIBFT_LIB)

re: 		fclean all

re_bonus: 	fclean bonus

.PHONY: 	all clean fclean re re_bonus bonus
