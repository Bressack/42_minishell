# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 23:43:12 by tharchen          #+#    #+#              #
#    Updated: 2020/02/07 17:03:49 by tharchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#                                                                              #
#    Makefile project minishell by tharchen and flindh                         #
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
#                                                                              #
# *** NAME - CC - FLAGS ****************************************************** #

NAME				=	minishell

CC					=	gcc

FLAGS				=	-Wall -Wextra -Werror -g3 -fsanitize=address -ferror-limit=1000

# *** PROJECT HEADER ********************************************************* #

HDIR				=	$(addprefix -I, $(HEADER_DIR))

HEADER_DIR			=	./includes/

HEADER				=	\
						color_shell.h \
						double_linked.h \
						get_next_line.h \
						ms.h \
						try_malloc.h \
						utils.h \

# *** SRCS ******************************************************************* #

SRCS_LIST			=	\
						.//srcs/lexer.c \
						.//srcs/lists/ft_add_node_end_np.c \
						.//srcs/lists/ft_add_node_f_nextto_np.c \
						.//srcs/lists/ft_add_node_f_prevto_np.c \
						.//srcs/lists/ft_add_node_nextto_np.c \
						.//srcs/lists/ft_add_node_prevto_np.c \
						.//srcs/lists/ft_add_node_start_np.c \
						.//srcs/lists/ft_del_list_np.c \
						.//srcs/lists/ft_del_node_end_np.c \
						.//srcs/lists/ft_del_node_np.c \
						.//srcs/lists/ft_del_node_start_np.c \
						.//srcs/lists/ft_foreach_node_f_np.c \
						.//srcs/lists/ft_new_node.c \
						.//srcs/lists/ft_swap_node_np.c \
						.//srcs/main.c \
						.//srcs/parser.c \
						.//srcs/utils/ft_atoi.c \
						.//srcs/utils/ft_bzero.c \
						.//srcs/utils/ft_strcmp.c \
						.//srcs/utils/ft_strjoin.c \
						.//srcs/utils/ft_strlen.c \
						.//srcs/utils/ft_strndup.c \
						.//srcs/utils/ft_strstr.c \
						.//srcs/utils/ft_substr.c \
						.//srcs/utils/get_next_line.c \
						.//srcs/utils/try_malloc.c \

						# .//srcs/utils/split_exp.c \

SRCS_DIR			=	./srcs_tmp/

SRCS_LIST_TMP		=	\
						lexer.c \
						ft_add_node_end_np.c \
						ft_add_node_f_nextto_np.c \
						ft_add_node_f_prevto_np.c \
						ft_add_node_nextto_np.c \
						ft_add_node_prevto_np.c \
						ft_add_node_start_np.c \
						ft_del_list_np.c \
						ft_del_node_end_np.c \
						ft_del_node_np.c \
						ft_del_node_start_np.c \
						ft_foreach_node_f_np.c \
						ft_new_node.c \
						ft_swap_node_np.c \
						main.c \
						parser.c \
						ft_atoi.c \
						ft_bzero.c \
						ft_strcmp.c \
						ft_strjoin.c \
						ft_strlen.c \
						ft_strndup.c \
						ft_strstr.c \
						ft_substr.c \
						get_next_line.c \
						try_malloc.c \

						# split_exp.c \

SRCS				=	$(addprefix $(SRCS_DIR), $(SRCS_LIST_TMP))

# *** OBJS ******************************************************************* #

OBJS_DIR			=	objs/

OBJS_LIST			=	$(patsubst %.c, %.o, $(SRCS_LIST_TMP))

OBJS				=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))

# *** RULES ****************************************************************** #

.PHONY: clean fclean lnsrcs all re norm

all: lnsrcs $(NAME)

$(NAME): $(OBJS)
	@ $(CC) $(FLAGS) $(HDIR) $(OBJS) -o $@

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@ mkdir -p $(OBJS_DIR)
	@ $(CC) $(FLAGS) $(HDIR) -c -o $@ $<
	@ echo "\033[31mProgram \033[32m$(NAME) : \033[34mCompilation of \033[36m$(notdir $<)\033[0m"

lnsrcs:
	@ mkdir -p $(SRCS_DIR)
	@ ln -fn $(SRCS_LIST) $(SRCS_DIR)

norm:
	@ norminette $(SRCS) $(HEADER)

clean:
	@ rm -rf $(OBJS_DIR)
	@ rm -rf $(SRCS_DIR)

fclean: clean
	@ rm -f $(NAME)

re: fclean lnsrcs
	@ make -j

# **************************************************************************** #
