# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 23:43:12 by tharchen          #+#    #+#              #
#    Updated: 2020/02/11 08:17:01 by tharchen         ###   ########.fr        #
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

FLAGS				=	-Wall -Wextra -Werror -O3

# *** PROJECT HEADER ********************************************************* #

HDIR				=	$(addprefix -I, $(HEADER_DIR))

HEADER_DIR			=	\

HEADER				=	\

# *** SRCS ******************************************************************* #

SRCS_LIST			=	\

SRCS_DIR			=	./srcs_tmp/

SRCS_LIST_TMP		=	\

SRCS				=	$(addprefix $(SRCS_DIR), $(SRCS_LIST_TMP))

# *** OBJS ******************************************************************* #

OBJS_DIR			=	objs/

OBJS_LIST			=	$(patsubst %.c, %.o, $(SRCS_LIST_TMP))

OBJS				=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))

# *** RULES ****************************************************************** #

.PHONY: clean fclean lnsrcs all re norm

all: lnsrcs $(OBJS) $(SRCS) $(NAME)

$(NAME): $(SRCS) $(OBJS) $(HEADER)
	@ $(CC) $(FLAGS) $(HDIR) $(OBJS) -o $@

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@ mkdir -p $(OBJS_DIR)
	@ $(CC) $(FLAGS) $(HDIR) -c -o $@ $<
	@ printf "\033[31m Program \033[32m$(NAME) : \033[34mCompilation of \033[36m$(notdir $<)\033[0m                             \r"

lnsrcs:
	@ mkdir -p $(SRCS_DIR)
	@ ln -fn $(SRCS_LIST) $(SRCS_DIR)

norm:
	@ norminette $(SRCS_LIST) $(HEADER)

clean:
	@ rm -rf $(OBJS_DIR)
	@ rm -rf $(SRCS_DIR)

fclean: clean
	@ rm -f $(NAME)

re: fclean lnsrcs
	@ make -j

# **************************************************************************** #
