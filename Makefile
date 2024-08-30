# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 11:18:05 by aklimchu          #+#    #+#              #
#    Updated: 2024/08/30 15:04:30 by aklimchu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		= pipex
NAME_B		= pipex_bonus

# Compiler
CC 			= gcc
CFLAGS		= -ggdb3 -Wall -Wextra -Werror -I $(LIBFT_DIR)
RM			= rm -f

# Libft
LIBFT_DIR	= libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

# Source / OBJ files / Includes
SRC 		= main.c path.c \
			ft_strjoin_new.c \
			free_all.c count_param.c \
			child_process_1.c \
			child_process_2.c printing.c \
			tools.c ft_split_new.c
OBJ 		= $(SRC:.c=.o)
INCLUDE		= -I "./"
# need to correct the header path


# Source / OBJ files / Includes for bonus
SRC_B 		= main_bonus.c path.c \
			ft_strjoin_new.c \
			free_all_bonus.c count_param.c \
			child_process_bonus.c \
			last_process_bonus.c printing.c \
			tools.c ft_split_new.c
OBJ_B 		= $(SRC_B:.c=.o)
INCLUDE_B	= -I "./"
# need to correct the header path
# do we need to set all files to _bonus?

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
