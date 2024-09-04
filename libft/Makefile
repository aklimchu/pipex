# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aklimchu <aklimchu@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 11:18:05 by aklimchu          #+#    #+#              #
#    Updated: 2024/09/04 15:39:34 by aklimchu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -ggdb3 -Wall -Wextra -Werror

SRC = ft_isascii.c ft_memmove.c \
	ft_strdup.c	ft_strnstr.c \
	ft_isdigit.c ft_memset.c \
	ft_striteri.c ft_strrchr.c \
	ft_isprint.c ft_putchar_fd.c \
	ft_strjoin.c ft_strtrim.c \
	ft_atoi.c ft_itoa.c \
	ft_putendl_fd.c	ft_strlcat.c \
	ft_substr.c ft_bzero.c \
	ft_putnbr_fd.c \
	ft_strlcpy.c ft_tolower.c \
	ft_calloc.c	ft_memchr.c \
	ft_putstr_fd.c ft_strlen.c \
	ft_toupper.c ft_isalnum.c \
	ft_memcmp.c	ft_split.c \
	ft_strmapi.c ft_isalpha.c \
	ft_memcpy.c	ft_strchr.c \
	ft_strncmp.c ft_checkchar.c \
	ft_printf.c \
	ft_puthex.c ft_putnbr_ui.c \
	ft_putptr.c get_next_line.c \
	get_next_line_utils.c \
		
BONUS_SRC = ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c ft_lstclear_bonus.c \
	ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

INCLUDE = ./

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@ -I $(INCLUDE)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

bonus: .bonus
	
.bonus:	$(BONUS_OBJ) $(OBJ)
	ar -rcs $(NAME) $?
	touch .bonus
	
clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean 
	rm -f $(NAME) .bonus

re: fclean all

.PHONY: all test clean fclean re bonus