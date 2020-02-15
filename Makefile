# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 23:43:12 by tharchen          #+#    #+#              #
#    Updated: 2020/02/15 14:06:12 by tharchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#                                                                              #
#    Makefile project minishell by tharchen and frlindh                        #
#                                                                              #
#    rules:                                                                    #
#                                                                              #
#    make        : make the project                                            #
#    make all    : make the project                                            #
#    make minishell : make the project                                         #
#    make norm   : run the norminette of srcs and headers                      #
#    make clean  : clean object files (.o)                                     #
#    make fclean : clean object files (.o) and remove minishell bin            #
#    make re     : run rules fclean then all                                   #
#                                                                              #
# *** NAME - CC - FLAGS ****************************************************** #

NAME				=	minishell

CC					=	gcc

FLAGS				=	-Wall -Wextra -Werror -O3 -g3 -fsanitize=address

# *** PROJECT HEADER ********************************************************* #

HDIR				=	$(addprefix -I, $(HEADER_DIR))

HEADER_DIR			=	\
						./includes/

HEADER				=	\
						class__lexer.h \
						class__token.h \
						color_shell.h \
						get_next_line.h \
						minishell.h \
						try_malloc.h \

# *** SRCS ******************************************************************* #

SRCS_DIR			=	./srcs/

SRCS_LIST			=	\
						class__lexer.c \
						class__token.c \
						defined_tokens.c \
						ft_strlen.c \
						ft_strncpy.c \
						ft_strsub.c \
						get_next_line.c \
						main.c \
						try_malloc.c \

SRCS				=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

# *** OBJS ******************************************************************* #

OBJS_DIR			=	./objs/

OBJS_LIST			=	$(patsubst %.c, %.o, $(SRCS_LIST))

OBJS				=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))

# *** RULES ****************************************************************** #

.PHONY: clean fclean all re norm

all: $(OBJS) $(SRCS) $(NAME)

$(NAME): $(SRCS) $(OBJS)
	@ $(CC) $(FLAGS) $(HDIR) $(OBJS) -o $@

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@ mkdir -p $(OBJS_DIR)
	@ $(CC) $(FLAGS) $(HDIR) -c -o $@ $<
	@ printf "\033[31m Program \033[32m$(NAME) : \033[34mCompilation of \033[36m$(notdir $<)\033[0m                             \r"

norm:
	@ norminette $(SRCS_LIST) $(HEADER)

clean:
	@ rm -rf $(OBJS_DIR)

fclean: clean
	@ rm -f $(NAME)

re: fclean
	@ make -j

# **************************************************************************** #
