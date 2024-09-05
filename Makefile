# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 11:18:05 by aklimchu          #+#    #+#              #
#    Updated: 2024/09/05 08:22:38 by aklimchu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		= pipex

# Compiler
CC 			= gcc
CFLAGS		= -ggdb3 -Wall -Wextra -Werror -I $(LIBFT_DIR)
RM			= rm -f

# Libft
LIBFT_DIR	= libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

# Source / OBJ files / Includes
SRC 		= ./src/main.c ./src/path.c \
			./src/ft_strjoin_new.c ./src/tools_2.c \
			./src/fork_1.c ./src/fork_2.c  \
			./src/tools.c ./src/ft_split_new.c \
			./src/printing.c
OBJ 		= $(SRC:.c=.o)
INCLUDE		= -I "./inc"

# Source / OBJ files / Includes for bonus
SRC_B 		= ./src_bonus/main_bonus.c ./src_bonus/path_bonus.c \
			./src_bonus/ft_strjoin_new_bonus.c \
			./src_bonus/tools_2_bonus.c \
			./src_bonus/child_process_bonus.c \
			./src_bonus/last_process_bonus.c \
			./src_bonus/printing_bonus.c \
			./src_bonus/tools_bonus.c ./src_bonus/ft_split_new_bonus.c \
			./src_bonus/here_doc_bonus.c ./src_bonus/here_doc_tools_bonus.c
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
%.o: %.c 
	$(CC) $(CFLAGS) $(INCLUDE_B) $^ -c -o $@

bonus:	$(OBJ_B)
	@make -C $(LIBFT_DIR)		# make libft
	@cp $(LIBFT_LIB) $(NAME)	# copy libft to current
	@$(CC) $(CFLAGS) $(OBJ_B) $(LIBFT_LIB) $(INCLUDE_B) -o $(NAME)

clean:
	$(RM) $(OBJ) $(OBJ_B)
	@make clean -C $(LIBFT_DIR)

fclean:		clean 
	$(RM) $(NAME) $(LIBFT_LIB)

re: 		fclean all

re_bonus: 	fclean bonus

.PHONY: 	all clean fclean re re_bonus bonus
