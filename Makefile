# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/06 21:08:57 by hroh              #+#    #+#              #
#    Updated: 2020/11/06 23:17:48 by hroh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

PATHLIBFT = libft
LIBFT = libft.a
SRCS = ./ft_printf.c \
		./parse.c \
		./print_char.c \
		./print_nbr.c \
		./print_str.c \
		./utils.c
OBJS = $(SRCS:.c=.o)

.c.o: 
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	make all -C $(PATHLIBFT)
	cp $(PATHLIBFT)/$(LIBFT) $(NAME)
	$(AR) $@ $^

all: $(NAME)

clean: 
	rm -f $(OBJS)
	make clean -C $(PATHLIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(PATHLIBFT)

re: fclean all

.PHONY: all clean fclean re
