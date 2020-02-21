# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/08 14:20:33 by frlindh           #+#    #+#              #
#    Updated: 2020/02/17 13:30:22 by frlindh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME - COMPILATOR - FLAGS ************************************************** #
NAME			=	printf.a
GCC				=	gcc
FLAGS			=	-Wall -Wextra -Werror

# SRCS *********************************************************************** #
SRCS			=	ft_printf.c ft_strnlen.c skip_atoi.c to_c.c to_s.c to_nbr.c to_n.c

# OBJS *********************************************************************** #
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

# RULES ********************************************************************** #

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) ft.h
	ar rcs $@ $^

bonus: $(NAME)

%.o: %.c
	$(GCC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
