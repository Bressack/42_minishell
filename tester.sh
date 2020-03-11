# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/05 21:37:03 by tharchen          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2020/03/11 14:49:35 by frlindh          ###   ########.fr        #
=======
#    Updated: 2020/03/11 14:00:23 by tharchen         ###   ########.fr        #
>>>>>>> 65ad8e763a981c7e1f1110115c0e14ad68e41d43
#                                                                              #
# **************************************************************************** #

#!/bin/sh
# a tester for minishell (new 42_cursus)

# COLORS

C_BLACK="\033[30m"
C_RED="\033[31m"
C_GREEN="\033[32m"
C_YELLOW="\033[33m"
C_BLUE="\033[34m"
C_MAGENTA="\033[35m"
C_CYAN="\033[36m"
C_WHITE="\033[37m"
C_GRAY="\033[90m"
C_G_BLACK="\033[30;01m"
C_G_RED="\033[31;01m"
C_G_GREEN="\033[32;01m"
C_G_YELLOW="\033[33;01m"
C_G_BLUE="\033[34;01m"
C_G_MAGENTA="\033[35;01m"
C_G_CYAN="\033[36;01m"
C_G_WHITE="\033[37;01m"
C_G_GRAY="\033[90;01m"
C_B_BLACK="\033[40m"
C_B_RED="\033[41m"
C_B_GREEN="\033[42m"
C_B_YELLOW="\033[43m"
C_B_BLUE="\033[44m"
C_B_MAGENTA="\033[45m"
C_B_CYAN="\033[46m"
C_B_WHITE="\033[47m"
C_B_GRAY="\033[100m"
C_RES="\033[0m"

# **************************************************************************** #
# **************************************************************************** #

# ENABLE TEST

TEST__ECHO=0
TEST__CD=0
TEST__PWD=0
TEST__EXPORT=0
TEST__UNSET=1
TEST__ENV=0
TEST__EXIT=0

# SUB TEST

TEST__SIMPLE=1
TEST__SIMPLE_REDIR=1
TEST__DOUBLE_REDIR=1

# **************************************************************************** #
# **************************************************************************** #

TOTAL_TEST=0
TOTAL_SUCCESS=0

init_tester()
{
	if [[ $2 == "make" ]]; then
		if [[ $3 == "re" ]]; then
			make re
		elif [[ $3 == "clean" ]]; then
			make clean
		elif [[ $3 == "bonus" ]]; then
			make bonus
		elif [[ $3 == "-j" ]]; then
			make -j
		else
			make
		fi
	fi
	rm -rf tester_dir
	mkdir tester_dir
	export MAIN_DIR=$PWD
	cd tester_dir
}

exit_tester()
{
	printf "test succeded %d/%d\n" $TOTAL_SUCCESS $TOTAL_TEST
	rm -rf tester_dir
	if [ $TOTAL_TEST != $TOTAL_SUCCESS ]
	then
		printf "wtf bros ... what a shitty job...\n"
	else
		printf "Great ! Good job ! You can set as finish !\n"
	fi
	cd $MAIN_DIR
}

reset_dirtest()
{
	rm -rf *
}

test()
{

	# (printf "$1\nexit\n") | /bin/bash 2>&- > $MAIN_DIR/user_output
	# (printf "$1\nexit\n") | zsh 2>&- > $MAIN_DIR/user_output


	# TEST minishell # ******************************************************* #
	(printf "$1\nexit\n") | $MAIN_DIR/minishell 2>&- > $MAIN_DIR/user_output
	USER_RETVAL=$?
	reset_dirtest

	# TEST bash # ************************************************************ #
	(printf "$1\nexit\n") | bash 2>&- > $MAIN_DIR/bash_output
	BASH_RETVAL=$?
	reset_dirtest

	# ANALYZE RESULT ********************************************************* #
	let "TOTAL_TEST+=1"
	diff --text $MAIN_DIR/user_output $MAIN_DIR/bash_output > /dev/null
	DIFF_RET=$?
	if [ $DIFF_RET == 0 ] && [ $USER_RETVAL == $BASH_RETVAL ]
	then
		printf "$C_G_WHITE test $C_G_CYAN %-8d$C_G_GREEN OK !$C_G_WHITE : \"$C_G_GRAY$1$C_G_WHITE \"$C_RES\n" $TOTAL_TEST
		let "TOTAL_SUCCESS+=1"
	else
		if [ $DIFF_RET != 0 ]
		then
			printf "$C_G_WHITE test $C_G_CYAN %-8d$C_G_RED KO !$C_G_WHITE :$C_G_RED DIFF ERROR $C_RES\"$C_G_GRAY$1$C_G_WHITE\"$C_RES\n" $TOTAL_TEST
		elif [ $USER_RETVAL != $BASH_RETVAL ]
		then
			printf "$C_G_WHITE test $C_G_CYAN %-8d$C_G_RED KO !$C_G_WHITE :$C_G_RED BAD RETURN VALUE$C_RES [ $C_G_BLUE%d$C_RES instead of $C_G_BLUE%d$C_RES ] \"$C_G_GRAY$1$C_G_WHITE \"$C_RES\n" $TOTAL_TEST $USER_RETVAL $BASH_RETVAL
		fi
		printf "user_output (%d):\n" $USER_RETVAL ; printf "$C_G_RED" ; cat -e $MAIN_DIR/user_output; printf "$C_RES"
		echo "********************************************"
		printf "bash_output (%d):\n" $BASH_RETVAL ; printf "$C_G_GREEN" ; cat -e $MAIN_DIR/bash_output; printf "$C_RES"
		printf "\n"
	fi
}

init_tester $1 $2 $3

# **************************************************************************** #
# *** tests ****************************************************************** #
# **************************************************************************** #

## BUILTINS

# **************************************************************************** #
# echo
if [ $TEST__ECHO == 1 ]; then
# simple
if [ $TEST__SIMPLE == 1 ]; then
test "echo "
test "echo a"
test "echo aaa"
test "echo a b c d e f g h"
test "echo @?"
test "echo %%?"
test "echo ??"
test "echo \$?"
test "echo \$"
test "echo 920347912slakjdfhlsakfhlaskf__D_SD_FS_DF_S_FS709304"
test "echo \$HOME"
test "echo \$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME"
test "echo \$1HOME"
test "echo \$H1OME"
test "echo \$HOME1"
test "echo \$PWD"
test "echo \$1PWD"
test "echo \$P1WD"
test "echo \$PWD1"
test "echo \$OLDPWD"
test "echo \$1OLDPWD"
test "echo \$O1LDPWD"
test "echo \$OLDPWD1"
test "echo \$ \$1HOME \$PWD ok \$OLDPWD"
test "echo \$ \$1HOME \$PWD \$ \$1OLDPWD"
test "echo \$1HOME \$PWD \$ \$1OLDPWD"
test "echo \$HOME\$PWD\$OLDPWD"
test "echo \$ \$1HOME \$PWD ok \$OLDPWD"
test "echo \$ \$1HOME \$PWD \$ \$1OLDPWD"
test "echo \$1HOME \$PWD \$ \$1OLDPWD"
test "echo \$HOME\$PWD\$OLDPWD"
test "echo \$ \$1HOME \$PWD ok \$OLDPWD"
test "echo \$ \$1HOME \$PWD \$ \$1OLDPWD"
test "echo \$1HOME \$PWD \$ \$1OLDPWD"
test "echo \$HOME\$PWD\$OLDPWD"
test "echo \$"
test "echo echo"
test "echo ls -l"
#adding // FRED
test "\\t \\\\ \\\$\'\\\\ \$HEJ \$HOME \\\$\'\"\\\\ \$HEJ \$HOME \\\$\""
test "\\\$? \$?"
fi
# redir out
if [ $TEST__SIMPLE_REDIR == 1 ]; then
test " > test1 echo  > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo a > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo aaa > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo a b c d e f g h > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo @? > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo %%? > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo ?? > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$? > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$ > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo 920347912slakjdfhlsakfhlaskf__D_SD_FS_DF_S_FS709304 > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$HOME > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$1HOME > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$H1OME > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$HOME1 > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$PWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$1PWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$P1WD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$PWD1 > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$1OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$O1LDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$OLDPWD1 > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$ \$1HOME \$PWD ok \$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$ \$1HOME \$PWD \$ \$1OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$1HOME \$PWD \$ \$1OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$HOME\$PWD\$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$ \$1HOME \$PWD ok \$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$ \$1HOME \$PWD \$ \$1OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$1HOME \$PWD \$ \$1OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$HOME\$PWD\$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$ \$1HOME \$PWD ok \$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$ \$1HOME \$PWD \$ \$1OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$1HOME \$PWD \$ \$1OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$HOME\$PWD\$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$ > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo echo > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo ls -l > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
fi
# double redir out
if [ $TEST__DOUBLE_REDIR == 1 ]; then
test ">test1 > test2 echo  >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo a >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo aaa >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo a b c d e f g h >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$? >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$ >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo 920347912slakjdfhlsakfhlaskf__D_SD_FS_DF_S_FS709304 >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$HOME >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$1HOME >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$H1OME >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$HOME1 >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$PWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$1PWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$P1WD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$PWD1 >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$1OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$O1LDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$OLDPWD1 >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$ \$1HOME \$PWD ok \$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$ \$1HOME \$PWD \$ \$1OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$1HOME \$PWD \$ \$1OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$HOME\$PWD\$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$ \$1HOME \$PWD ok \$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$ \$1HOME \$PWD \$ \$1OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$1HOME \$PWD \$ \$1OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$HOME\$PWD\$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$ \$1HOME \$PWD ok \$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$ \$1HOME \$PWD \$ \$1OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$1HOME \$PWD \$ \$1OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$HOME\$PWD\$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$ >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo echo >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo ls -l >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
fi
fi
# **************************************************************************** #

# **************************************************************************** #
# cd
if [ $TEST__CD == 1 ]; then
test "cd;pwd"
test "cd /;pwd"
test "cd /dev;pwd"
test "cd bad_arg;pwd"
test "cd bad_arg1 bad_arg2;pwd"
test "mkdir dir1\ncd dir1;pwd"
fi
# **************************************************************************** #

# **************************************************************************** #
# pwd
if [ $TEST__PWD == 1 ]; then
test "pwd"
test "unset \$PWD; pwd"
test "export TESTPWD=\$PWD;unset \$PWD; pwd"
test "export TESTPWD=\$PWD;unset \$PWD; pwd; export PWD=\$TESTPWD;pwd"
test "export TESTPWD=\$PWD;unset \$PWD; pwd; export PWD=\$TESTPWD;pwd;unset \$PWD; pwd"
test "pwd pwd"
test "pwd;pwd;pwd;pwd;pwd;pwd;pwd;pwd;pwd;pwd;pwd;pwd;pwd;pwd"
test "pwd asdf"
test "pwd asdf sadf"
test "pwd ."
test "pwd .."
test "cd / ; pwd"
test "cd asdfSD ; pwd"
test "mkdir dir1;cd dir1 ; pwd"
test "mkdir dir1 ; mkdir dir1/dir2 ; cd dir1/dir2 ; pwd"
test "cd / \npwd"
fi
# **************************************************************************** #

# **************************************************************************** #
# export
if [ $TEST__EXPORT == 1 ]; then
test "export LS=\"    ls     -l      \" ; \$LS"
test "export hej hej+=da 56=he"
test "export | sort"
fi
# **************************************************************************** #

# **************************************************************************** #
# unset
if [ $TEST__UNSET == 1 ]; then
test "unset PATH;ls"
test "unset PWD;cd \$PWD"
test "unset sdafasd"
test "unset sdafasd asdfsd"
test "unset"
test "unset \$HOME\$HOME"
test "unset \$HOME\$PWD"
test "unset \$HOME\$PWD\$?"
test "unset \$HOME asdf \$PWD"

fi
# **************************************************************************** #

# **************************************************************************** #
# env
if [ $TEST__ENV == 1 ]; then
test ""
fi
# **************************************************************************** #

# **************************************************************************** #
# exit
if [ $TEST__EXIT == 1 ]; then
test ""
fi
# **************************************************************************** #

exit_tester
