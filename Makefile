# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 23:43:12 by tharchen          #+#    #+#              #
#    Updated: 2020/02/25 13:25:50 by tharchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#                                                                              #
#    Makefile project minishell by tharchen and frlindh                        #
#                                                                              #
#    rules:                                                                    #
#                                                                              #
#    make           : make the project                                         #
#    make all       : make the project                                         #
#    make minishell : make the project                                         #
#    make norm      : run the norminette of srcs and headers                   #
#    make clean     : clean object files (.o)                                  #
#    make fclean    : clean object files (.o) and remove minishell bin         #
#    make re        : run rules fclean then all                                #
#    make run       : run re then run ./$(NAME)                                #
#                                                                              #
# *** NAME - CC - FLAGS ****************************************************** #

NAME				=	minishell

CC					=	clang

FLAGS				=	\
						-Wall -Wextra -Werror \
						-O3 \
						-g3 -fsanitize=address \

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
						ft_printf.h \
						env.h \
						utils.h \
						commands.h \
						# class__ast.h \
						# class__node.h \

# *** SRCS ******************************************************************* #

SRCS_DIR			=	./srcs/


SRCS_TOKEN			=	\
						token/class__token.c \
						token/class__token__global_arrays.c \

SRCS_ENVIRONEMENT	=	\
						environement/unset.c \
						environement/env.c \
						environement/export.c \

SRCS_LEXER			=	\
						lexer/class__lexer.c \
						lexer/class__lexer__defined_tokens.c \

SRCS_BUILTIN		=	\
						builtins/commands.c \

# SRCS_AST			=	\
# 						ast/class__ast.c \
#
# SRCS_NODE			=	\
# 						node/class__node.c \

SRCS_UTILS			=	\
						utils/ft_strlen.c \
						utils/ft_strjoin.c \
						utils/ft_memcpy.c \
						utils/get_next_line.c \
						utils/try_malloc.c \
						utils/ft_strncmp.c \
						utils/ft_strcpy.c \
						utils/ft_strdup.c \
						utils/ft_strsub.c \
						utils/ft_strncpy.c \
						utils/ft_strcmp.c \

SRCS_PRINTF			=	\
						utils/ft_printf/to_n.c \
						utils/ft_printf/skip_atoi.c \
						utils/ft_printf/ft_strnlen.c \
						utils/ft_printf/to_c.c \
						utils/ft_printf/ft_printf.c \
						utils/ft_printf/to_nbr.c \
						utils/ft_printf/to_s.c \

SRCS_LIST			=	\
						main.c \
						$(SRCS_TOKEN) \
						$(SRCS_ENVIRONEMENT) \
						$(SRCS_LEXER) \
						$(SRCS_BUILTIN) \
						$(SRCS_UTILS) \
						$(SRCS_PRINTF) \
						# $(SRCS_AST) \
						# $(SRCS_NODE) \


SRCS				=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

# *** OBJS ******************************************************************* #

OBJS_DIR			=	./objs/

OBJS_LIST			=	$(patsubst %.c, %.o, $(SRCS_LIST))

OBJS				=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))

# *** RULES ****************************************************************** #

.PHONY: clean fclean all re norm test

all: $(OBJS) $(SRCS) $(NAME)

$(NAME): $(OBJS) $(SRCS)
	@ $(CC) $(FLAGS) $(HDIR) $(OBJS) -o $@
	@ printf "\n"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@ mkdir -p $(dir $@)
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

real: re
	@ ./$(NAME)

test:
	@ echo "OBJS_DIR : " $(OBJS_DIR)
	@ echo
	@ echo "OBJS_LIST: " $(OBJS_LIST)
	@ echo
	@ echo "OBJS     : " $(OBJS)
	@ echo
# **************************************************************************** #
