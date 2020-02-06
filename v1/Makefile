# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 23:43:12 by tharchen          #+#    #+#              #
#    Updated: 2020/01/30 17:01:16 by tharchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#                                                                              #
#    Makefile project minishell by tharchen and flindh                         #
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

FLAGS				=	-Wall -Wextra -Werror -O3 -g3 -fsanitize=address -ferror-limit=1000

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
						.//srcs/gnl/get_next_line.c \
						.//srcs/lists/ft_add_node_f_nextto_np.c \
						.//srcs/lists/ft_swap_node_np.c \
						.//srcs/lists/ft_del_node_np.c \
						.//srcs/lists/ft_del_list_np.c \
						.//srcs/lists/ft_add_node_prevto_np.c \
						.//srcs/lists/ft_foreach_node_f_np.c \
						.//srcs/lists/ft_add_node_end_np.c \
						.//srcs/lists/ft_add_node_start_np.c \
						.//srcs/lists/ft_new_node.c \
						.//srcs/lists/ft_add_node_f_prevto_np.c \
						.//srcs/lists/ft_del_node_start_np.c \
						.//srcs/lists/ft_del_node_end_np.c \
						.//srcs/lists/ft_add_node_nextto_np.c \
						.//srcs/utils/ft_strlen.c \
						.//srcs/utils/ft_bzero.c \
						.//srcs/utils/ft_strjoin.c \
						.//srcs/utils/ft_strstr.c \
						.//srcs/utils/try_malloc.c \
						.//srcs/utils/ft_substr.c \
						.//srcs/utils/ft_strndup.c \
						.//srcs/utils/ft_atoi.c \
						.//srcs/utils/ft_strcmp.c \
						.//srcs/main/main.c \
						.//srcs/main/new_element.c \
						.//srcs/main/debug.c \
						.//srcs/main/f__del_list_np.c \
						.//srcs/main/ft_iss.c \
						.//srcs/main/parser.c \
						.//srcs/main/parser_quote.c \
						.//srcs/main/parser_special.c \
						.//srcs/main/parser_special_init.c \
						.//srcs/main/parser_special_init__bonus.c \
						.//srcs/main/parser_valid_char.c \
						.//srcs/main/pass.c \

SRCS_DIR			=	./srcs_tmp/

SRCS_LIST_TMP		=	\
						get_next_line.c \
						ft_add_node_f_nextto_np.c \
						ft_swap_node_np.c \
						ft_del_node_np.c \
						ft_del_list_np.c \
						ft_add_node_prevto_np.c \
						ft_foreach_node_f_np.c \
						ft_add_node_end_np.c \
						ft_add_node_start_np.c \
						ft_new_node.c \
						ft_add_node_f_prevto_np.c \
						ft_del_node_start_np.c \
						ft_del_node_end_np.c \
						ft_add_node_nextto_np.c \
						ft_strlen.c \
						ft_bzero.c \
						ft_strjoin.c \
						ft_strstr.c \
						try_malloc.c \
						ft_substr.c \
						ft_strndup.c \
						ft_atoi.c \
						ft_strcmp.c \
						main.c \
						new_element.c \
						debug.c \
						f__del_list_np.c \
						ft_iss.c \
						parser.c \
						parser_quote.c \
						parser_special.c \
						parser_special_init.c \
						parser_special_init__bonus.c \
						parser_valid_char.c \
						pass.c \

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
