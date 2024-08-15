# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 11:18:05 by aklimchu          #+#    #+#              #
#    Updated: 2024/08/15 13:10:51 by aklimchu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		= pipex

# Compiler
CC 			= cc
CFLAGS		= -Wall -Wextra -Werror -I $(LIBFT_DIR)
RM			= rm -f

# Libft
LIBFT_DIR	= libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

# Source / OBJ files / Includes
SRC 		= main.c
OBJ 		= $(SRC:.c=.o)
INCLUDE		= -I "./"

# Rules
all:		$(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) $(INCLUDE) $^ -c -o $@

$(NAME):	$(OBJ)
	@make -C $(LIBFT_DIR)		# make libft
	@cp $(LIBFT_LIB) $(NAME)	# copy libft to current
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) $(INCLUDE) -o $(NAME)

clean:
	$(RM) $(OBJ) 
	@make clean -C $(LIBFT_DIR)

fclean:		clean 
	$(RM) $(NAME) $(LIBFT_LIB)

re: 		fclean all

.PHONY: 	all clean fclean re
