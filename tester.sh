# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/18 14:36:04 by tharchen          #+#    #+#              #
#    Updated: 2020/02/18 15:33:27 by tharchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BIN_SHELL_REF=bash
BIN_SHELL_USER=./minishell

REPORTS_PATH=/tmp

# make re;


function test()
{
	printf "$1\nexit\n" | $BIN_SHELL_REF > $REPORTS_PATH/report_bash
	printf "$1\nexit\n" | $BIN_SHELL_USER > $REPORTS_PATH/report_user
	diff $REPORTS_PATH/report_bash $REPORTS_PATH/report_user
}

function test_lexer()
{
	printf "$1\nexit\n" | $BIN_SHELL_REF > $REPORTS_PATH/report_bash
	printf "$1\nexit\n" | $BIN_SHELL_USER > $REPORTS_PATH/report_user
	diff $REPORTS_PATH/report_bash $REPORTS_PATH/report_user
}

test "ls -l | cat -e"
test "echo"
