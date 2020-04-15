# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/05 21:37:03 by tharchen          #+#    #+#              #
#    Updated: 2020/04/15 16:10:20 by tharchen         ###   ########.fr        #
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

TEST__REDIR=1

TEST__ECHO=1
TEST__CD=1
TEST__PWD=1
TEST__EXPORT=1
TEST__UNSET=1
TEST__ENV=1
TEST__EXIT=1
TEST__RANDOM_FRED=1

TEST__BAD=1
TEST__GOOD=1

# SUB TEST

TEST__SIMPLE=1
TEST__SIMPLE_REDIR=1
TEST__DOUBLE_REDIR=1
TEST__SIMPLE_REDIR_IN=1

# **************************************************************************** #
# **************************************************************************** #

TOTAL_TEST=0
TOTAL_SUCCESS=0

init_tester()
{
	# printf "\n**********************************************************\n"
	# printf "$C_G_WHITE print only fails (uncomment line 142 to print all tests) $C_RES \n"
	# printf "**********************************************************\n\n"
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
	if [ $TOTAL_TEST != $TOTAL_SUCCESS ]
	then
		printf "sorry :( bros ... not yet there, bon courage!! ..\n"
	else
		printf "Great ! Good job ! You can set as finish !\n"
	fi
	cd $MAIN_DIR
	rm -rf tester_dir
	rm -rf bash_output
	rm -rf user_output
}

reset_dirtest()
{
	rm -rf *
}

test()
{
	# TEST minishell # ******************************************************* #
	# (printf "$1\nexit\n") | /bin/bash 2>/dev/null > $MAIN_DIR/user_output
	# (printf "$1\nexit\n") | zsh 2>/dev/null > $MAIN_DIR/user_output
	(printf "$1\nexit\n") | $MAIN_DIR/minishell 2>/dev/null > $MAIN_DIR/user_output
	USER_RETVAL=$?
	reset_dirtest

	# TEST bash # ************************************************************ #
	# (printf "$1\nexit\n") | /bin/bash 2>/dev/null > $MAIN_DIR/bash_output
	(printf "$1\nexit\n") | bash 2>/dev/null > $MAIN_DIR/bash_output
	BASH_RETVAL=$?
	reset_dirtest

	# ANALYZE RESULT ********************************************************* #
	let "TOTAL_TEST+=1"
	diff --text $MAIN_DIR/user_output $MAIN_DIR/bash_output > /dev/null
	DIFF_RET=$?
	if [ $DIFF_RET == 0 ] && [ $USER_RETVAL == $BASH_RETVAL ]
	then
		printf "$C_G_WHITE test $C_G_CYAN %-8d$C_G_GREEN OK !$C_G_WHITE : \"$C_G_GRAY$1$C_G_WHITE\"$C_RES\n" $TOTAL_TEST
		let "TOTAL_SUCCESS+=1"
	else
		if [ $DIFF_RET != 0 ]
		then
			printf "$C_G_WHITE test $C_G_CYAN %-8d$C_G_RED KO !$C_G_WHITE :$C_G_RED DIFF ERROR $C_RES\"$C_G_GRAY$1$C_G_WHITE\"$C_RES\n" $TOTAL_TEST
			printf "user_output (%d):\n" $USER_RETVAL ; printf "$C_G_RED" ; cat $MAIN_DIR/user_output; printf "$C_RES"
			echo "********************************************"
			printf "bash_output (%d):\n" $BASH_RETVAL ; printf "$C_G_GREEN" ; cat $MAIN_DIR/bash_output; printf "$C_RES"
			printf "\n"
		elif [ $USER_RETVAL != $BASH_RETVAL ]
		then
			printf "$C_G_WHITE test $C_G_CYAN %-8d$C_G_RED KO !$C_G_WHITE :$C_G_RED BAD RETURN VALUE$C_RES [ $C_G_RED%d$C_RES instead of $C_G_GREEN%d$C_RES ] \"$C_G_GRAY$1$C_G_WHITE\"$C_RES\n" $TOTAL_TEST $USER_RETVAL $BASH_RETVAL
		fi
	fi
	# printf "user_output (%d):\n" $USER_RETVAL ; printf "$C_G_RED" ; cat $MAIN_DIR/user_output; printf "$C_RES"
	# echo "********************************************"
	# printf "bash_output (%d):\n" $BASH_RETVAL ; printf "$C_G_GREEN" ; cat $MAIN_DIR/bash_output; printf "$C_RES"
}

init_tester $1 $2 $3

# **************************************************************************** #
# *** tests ****************************************************************** #
# **************************************************************************** #

test "qwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwe > test ; cat test"
test "qwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwer > test ; cat test"
test "qwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerq > test ; cat test"
test "qwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwerqwer > test ; cat test"
test "touch 000 hej; ./hej > test1 ; cat test1"
test "mkdir a;mkdir b; cp a ./b > test2 ; cat test2"
test "mkdir a; cp a ./b > test2 ; cat test2"
test "cat qewr > test1 ; cat test1"

test ""
test "\n"
test "\n\n"
test "\n\n\n"
test "ls;ls"
test "ls"

if [ $TEST__REDIR == 1 ]; then

test "<"
test "< test"
test "< test < test"
test "< test < test1"
test "< test < test1 < test"
test "< test < test1 < test < test"

test ">"
test "> test"
test "> test > test"
test "> test > test1"
test "> test > test1 > test"
test "> test > test1 > test > test"

test ">>"
test ">> test"
test ">> test >> test"
test ">> test >> test1"
test ">> test >> test1 >> test"
test ">> test >> test1 >> test >> test"

test "ls -l > test; <"
test "ls -l > test; <; cat -e test"
test "ls -l > test; < test"
test "ls -l > test; < test; cat -e test"
test "ls -l > test; < test < test"
test "ls -l > test; < test < test; cat -e test"
test "ls -l > test; < test < test1"
test "ls -l > test; < test < test1; cat -e test;"
test "ls -l > test; < test < test1 < test;"
test "ls -l > test; < test < test1 < test; cat -e test;"
test "ls -l > test; < test < test1 < test < test;"
test "ls -l > test; < test < test1 < test < test; cat -e test"

test "ls -l > test; >;"
test "ls -l > test; >; cat -e test;"
test "ls -l > test; > test;"
test "ls -l > test; > test; cat -e test;"
test "ls -l > test; > test > test;"
test "ls -l > test; > test > test; cat -e test;"
test "ls -l > test; > test > test1"
test "ls -l > test; > test > test1; cat -e test"
test "ls -l > test; > test > test1 > test"
test "ls -l > test; > test > test1 > test; cat -e test"
test "ls -l > test; > test > test1 > test > test"
test "ls -l > test; > test > test1 > test > test; cat -e test"

test "ls -l > test; >>"
test "ls -l > test; >>; cat -e test"
test "ls -l > test; >> test"
test "ls -l > test; >> test; cat -e test"
test "ls -l > test; >> test >> test"
test "ls -l > test; >> test >> test; cat -e test;"
test "ls -l > test; >> test >> test1;"
test "ls -l > test; >> test >> test1; cat -e test;"
test "ls -l > test; >> test >> test1 >> test;"
test "ls -l > test; >> test >> test1 >> test; cat -e test;"
test "ls -l > test; >> test >> test1 >> test >> test;"
test "ls -l > test; >> test >> test1 >> test >> test; cat -e test;"

test "cat -e /dev/urandom | head -c 100 > test | wc -c test | wc -l | cat -e"
test "cat -e /dev/urandom | head -c 100 > test ; wc -c test > test;cat -e test"

test "> test echo bli bla blou > test;cat -e test;"
test "> test echo bli bla blou > test;>> test echo bli bla blou >> test;cat -e test;"

fi

## BUILTINS

# **************************************************************************** #
# echo
if [ $TEST__ECHO == 1 ]; then
printf "\n$C_G_WHITE TEST__ECHO$C_RES:\n"
# simple
if [ $TEST__SIMPLE == 1 ]; then
printf "\n$C_G_WHITE TEST__SIMPLE$C_RES:\n"
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
test "echo \$HOME"
test "echo \$H1OME"
test "echo \$HOME1"
test "echo \$PWD"
test "echo \$PWD"
test "echo \$P1WD"
test "echo \$PWD1"
test "echo \$OLDPWD"
test "echo \$OLDPWD"
test "echo \$O1LDPWD"
test "echo \$OLDPWD1"
test "echo \$ \$HOME \$PWD ok \$OLDPWD"
test "echo \$ \$HOME \$PWD \$ \$OLDPWD"
test "echo \$HOME \$PWD \$ \$OLDPWD"
test "echo \$HOME\$PWD\$OLDPWD"
test "echo \$ \$HOME \$PWD ok \$OLDPWD"
test "echo \$ \$HOME \$PWD \$ \$OLDPWD"
test "echo \$HOME \$PWD \$ \$OLDPWD"
test "echo \$HOME\$PWD\$OLDPWD"
test "echo \$ \$HOME \$PWD ok \$OLDPWD"
test "echo \$ \$HOME \$PWD \$ \$OLDPWD"
test "echo \$HOME \$PWD \$ \$OLDPWD"
test "echo \$HOME\$PWD\$OLDPWD"
test "export LS=\"          ls      -l   \" ; echo \$LS\$LS\$LS"
test "export IFS=_ TEST=hej_jag_heter_fredrika ; echo \$TEST"
test "echo \$"
test "echo echo"
test "echo ls -l"
#adding // FRED
test "\\t \\\\ \\\$\'\\\\ \$HEJ \$HOME \\\$\'\"\\\\ \$HEJ \$HOME \\\$\""
test "\\\$? \$?"
fi
# redir out
if [ $TEST__SIMPLE_REDIR == 1 ]; then
test ">"
test "> test1"
test "> test1 cat -e > test2 test1"
test "> test1 > test2"
test "cat > test1 > test2 -e"
test "> test1 > test1 cat test1"
test "> test1 cat > test1"
test "> test1 cat test1"
test "> test1 < test1 cat"
test "> test1 < test1"
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
test " > test1 echo \$HOME > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$H1OME > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$HOME1 > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$PWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$PWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$P1WD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$PWD1 > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$O1LDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$OLDPWD1 > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$ \$HOME \$PWD ok \$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$ \$HOME \$PWD \$ \$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$HOME \$PWD \$ \$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$HOME\$PWD\$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$ \$HOME \$PWD ok \$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$ \$HOME \$PWD \$ \$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$HOME \$PWD \$ \$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$HOME\$PWD\$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$ \$HOME \$PWD ok \$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$ \$HOME \$PWD \$ \$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$HOME \$PWD \$ \$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$HOME\$PWD\$OLDPWD > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo \$ > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo echo > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
test " > test1 echo ls -l > test2 > test2 okcgood > test3; cat -e test1 test2 test3"
printf "\n$C_G_WHITE TEST__SIMPLE_REDIR$C_RES:\n"
fi
# double redir out
if [ $TEST__DOUBLE_REDIR == 1 ]; then
test ">>"
test ">> test1"
test ">> test1 cat -e >> test2 test1"
test ">> test1 >> test2"
test "cat >> test1 >> test2 -e"
test "> test1 >> test1 cat test1"
test "> test1 cat >> test1"
test ">> test1 cat test1"
test ">> test1 < test1 cat"
test ">> test1 < test1"
test ">test1 > test2 echo  >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo a >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo aaa >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo a b c d e f g h >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$? >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$ >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo 920347912slakjdfhlsakfhlaskf__D_SD_FS_DF_S_FS709304 >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$HOME >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$HOME >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$H1OME >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$HOME1 >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$PWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$PWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$P1WD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$PWD1 >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$O1LDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$OLDPWD1 >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$ \$HOME \$PWD ok \$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$ \$HOME \$PWD \$ \$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$HOME \$PWD \$ \$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$HOME\$PWD\$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$ \$HOME \$PWD ok \$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$ \$HOME \$PWD \$ \$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$HOME \$PWD \$ \$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$HOME\$PWD\$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$ \$HOME \$PWD ok \$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$ \$HOME \$PWD \$ \$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$HOME \$PWD \$ \$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$HOME\$PWD\$OLDPWD >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo \$ >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo echo >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"
test ">test1 > test2 echo ls -l >test2 >> test1 >> test1 >> test2 >> test3 OK CTREGOOD >> test1; cat -e test1 test2 test3"

printf "\n$C_G_WHITE TEST__DOUBLE_REDIR$C_RES:\n"
fi
# double redir out
if [ $TEST__SIMPLE_REDIR_IN == 1 ]; then
printf "\n$C_G_WHITE TEST__SIMPLE_REDIR_IN$C_RES:\n"
test "<"
test "<; cat -e test1 test2 test3"
test "<; echo END"
test "<; echo END; cat -e test1 test2 test3"
test "echo START;<"
test "echo START;<; cat -e test1 test2 test3"
test "ls > test1 >> test1;ls -l >> test1; <test1 cat >>test1 -e <test1 < test1 > test1 >> test2"
test "ls > test1 >> test1;ls -l >> test1; <test1 cat >>test1 -e <test1 < test1 > test1 >> test2; cat -e test1 test2 test3"
test "ls > test1 >> test1;ls -l >> test1; <test1 cat >>test1 -e <test1 < test1 > test1 >> test2; echo END"
test "ls > test1 >> test1;ls -l >> test1; <test1 cat >>test1 -e <test1 < test1 > test1 >> test2; echo END; cat -e test1 test2 test3"
test "echo START;ls > test1 >> test1;ls -l >> test1; <test1 cat >>test1 -e <test1 < test1 > test1 >> test2"
test "echo START;ls > test1 >> test1;ls -l >> test1; <test1 cat >>test1 -e <test1 < test1 > test1 >> test2; cat -e test1 test2 test3"
test "ls -l > test1; < test1 cat -e"
test "ls -l > test1; < test1 cat -e; cat -e test1 test2 test3"
test "ls -l > test1; < test1 cat -e; echo END"
test "ls -l > test1; < test1 cat -e; echo END; cat -e test1 test2 test3"
test "echo START;ls -l > test1; < test1 cat -e"
test "echo START;ls -l > test1; < test1 cat -e; cat -e test1 test2 test3"
test "< test1"
test "< test1; cat -e test1 test2 test3"
test "< test1; echo END"
test "< test1; echo END; cat -e test1 test2 test3"
test "echo START;< test1"
test "echo START;< test1; cat -e test1 test2 test3"
test "ls > test1; < test1"
test "ls > test1; < test1; cat -e test1 test2 test3"
test "ls > test1; < test1; echo END"
test "ls > test1; < test1; echo END; cat -e test1 test2 test3"
test "echo START;ls > test1; < test1"
test "echo START;ls > test1; < test1; cat -e test1 test2 test3"
test "ls >> test1; < test1"
test "ls >> test1; < test1; cat -e test1 test2 test3"
test "ls >> test1; < test1; echo END"
test "ls >> test1; < test1; echo END; cat -e test1 test2 test3"
test "echo START;ls >> test1; < test1"
test "echo START;ls >> test1; < test1; cat -e test1 test2 test3"
test "cat -e < test1 | < test1 > test2; cat -e test1 test2 test3"
test "cat -e < test1 | < test1 > test2; echo END"
test "cat -e < test1 | < test1 > test2; echo END; cat -e test1 test2 test3"
test "echo START;cat -e < test1 | < test1 > test2; cat -e test1 test2 test3"
test "> test1 < test1"
test "> test1 < test1; cat -e test1 test2 test3"
test "> test1 < test1; echo END"
test "> test1 < test1; echo END; cat -e test1 test2 test3"
test "echo START;> test1 < test1"
test "echo START;> test1 < test1; cat -e test1 test2 test3"
test "< test1 cat test1"
test "< test1 cat test1; cat -e test1 test2 test3"
test "< test1 cat test1; echo END"
test "< test1 cat test1; echo END; cat -e test1 test2 test3"
test "echo START;< test1 cat test1"
test "echo START;< test1 cat test1; cat -e test1 test2 test3"
test "> test1 cat test1"
test "> test1 cat test1; cat -e test1 test2 test3"
test "> test1 cat test1; echo END"
test "> test1 cat test1; echo END; cat -e test1 test2 test3"
test "echo START;> test1 cat test1"
test "echo START;> test1 cat test1; cat -e test1 test2 test3"
test ">> test1 < test1 cat test1"
test ">> test1 < test1 cat test1; cat -e test1 test2 test3"
test ">> test1 < test1 cat test1; echo END"
test ">> test1 < test1 cat test1; echo END; cat -e test1 test2 test3"
test "echo START;>> test1 < test1 cat test1"
test "echo START;>> test1 < test1 cat test1; cat -e test1 test2 test3"
test "> test cat < test1 -e >> test2"
test "> test cat < test1 -e >> test2; cat -e test1 test2 test3"
test "> test cat < test1 -e >> test2; echo END"
test "> test cat < test1 -e >> test2; echo END; cat -e test1 test2 test3"
test "echo START;> test cat < test1 -e >> test2"
test "echo START;> test cat < test1 -e >> test2; cat -e test1 test2 test3"
fi
fi
# **************************************************************************** #

# **************************************************************************** #
# cd
if [ $TEST__CD == 1 ]; then
printf "\n$C_G_WHITE TEST__CD$C_RES:\n"
test "pwd;cd;pwd"
test "pwd;cd qwerwqer;pwd"
test "pwd;cd _;pwd"
test "pwd;cd ~;pwd"
test "pwd;mkdir dir1;mkdir dir1/dir2;mkdir dir1/dir2/dir3;mkdir dir1/dir2/dir3/dir4;cd dir1;pwd; cd dir1/dir2; pwd;cd dir3/ ;pwd; cd ../../../dir1/dir2/dir3/dir4;pwd;cd ../../../../; pwd"
test "pwd;cd ;pwd"
test "pwd;cd /;pwd"
test "pwd;cd /dev;pwd"
test "pwd;cd /dev/random;pwd"
test "pwd;cd /dev/fd;pwd"
test "pwd;cd /dev/fd/0;pwd;cd \$MAIN_DIR/tester_dir;pwd"
test "pwd;cd /dev/fd/0;pwd;cd asdfasdf;pwd;cd \$MAIN_DIR/tester_dir;pwd"
test "pwd;cd /dev/fd/1;pwd;cd \$MAIN_DIR/tester_dir;pwd"
test "pwd;cd /dev/fd/1;pwd;cd asdfasdf;pwd;cd \$MAIN_DIR/tester_dir;pwd"
test "pwd;cd /dev/fd/2;pwd;cd \$MAIN_DIR/tester_dir;pwd"
test "pwd;cd /dev/fd/2;pwd;cd asdfasdf;pwd;cd \$MAIN_DIR/tester_dir;pwd"
test "pwd;cd /dev/fd/3;pwd;cd \$MAIN_DIR/tester_dir;pwd"
test "pwd;cd /dev/fd/3;pwd;cd asdfasdf;pwd;cd \$MAIN_DIR/tester_dir;pwd"
test "pwd;cd /dev/fd/4;pwd;cd \$MAIN_DIR/tester_dir;pwd"
test "pwd;cd /dev/fd/4;pwd;cd asdfasdf;pwd;cd \$MAIN_DIR/tester_dir;pwd"
test "pwd;cd bad_arg;pwd"
test "pwd;cd bad_arg1 bad_arg2;pwd"
test "mkdir dir1\ncd dir1;pwd"
fi
# **************************************************************************** #

# **************************************************************************** #
# pwd
if [ $TEST__PWD == 1 ]; then
printf "\n$C_G_WHITE TEST__PWD$C_RES:\n"
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
test "pwd > test"
test "pwdmkdir dir1;pwd;cd dir1;pwd;rm -rf ../dir1;pwd;cd;pwd"
test "pwd;cd /;pwd;cd ..;pwd;cd ~;pwd"
fi
# **************************************************************************** #

# **************************************************************************** #
# export
if [ $TEST__EXPORT == 1 ]; then
SHOW_EXPORT="export | sort | grep -v \"declare -x _=\" | grep -v \"declare -x SHLVL\""
printf "\n$C_G_WHITE TEST__EXPORT$C_RES:\n"
test "export LS=\"    ls     -l      \" ; \$LS"
test "export hej hej+=da 56=he"
test "$SHOW_EXPORT"
test "export HEJ1=da5;$SHOW_EXPORT"
test "export a=b c=d e=f g=h i=j k=l m=n o=p;$SHOW_EXPORT"
test "export a=1;$SHOW_EXPORT"
test "export 1=a;$SHOW_EXPORT"
test "export a1=a;$SHOW_EXPORT"
test "export 1a=a;$SHOW_EXPORT"
test "export a=1a;$SHOW_EXPORT"
test "export a=a1;$SHOW_EXPORT"
test "export 1a=a1;$SHOW_EXPORT"
test "export 1a1=1a1;$SHOW_EXPORT"
test "export =1a1;$SHOW_EXPORT"
test "export 1a1=;$SHOW_EXPORT"
test "export =;$SHOW_EXPORT"
test "export a=b=c=d=e=f=g=h;$SHOW_EXPORT"
test "export a=b=c=d=e=f=g=h=;$SHOW_EXPORT"
test "export =a=b=c=d=e=f=g=h;$SHOW_EXPORT"
test "export =a=b=c=d=e=f=g=h=;$SHOW_EXPORT"
test "export ============;$SHOW_EXPORT"
test "export =====1=======;$SHOW_EXPORT"
fi
# **************************************************************************** #

# **************************************************************************** #
# unset
if [ $TEST__UNSET == 1 ]; then
printf "\n$C_G_WHITE TEST__UNSET$C_RES:\n"
test "unset PATH;ls"
test "unset PWD;cd \$PWD"
test "unset PWD;cd \$PWD ; export PWD=~;cd PWD"
test "unset sdafasd"
test "unset sdafasd asdfsd"
test "unset"
test "unset \$HOME\$HOME"
test "unset \$HOME\$PWD"
test "unset \$HOME\$PWD\$?"
test "unset \$HOME asdf \$PWD"
test "unset he52_ge _hej 77 hej*"
test "unset B C= 54+=45 D"

fi
# **************************************************************************** #

# **************************************************************************** #
# env
if [ $TEST__ENV == 1 ]; then
printf "\n$C_G_WHITE TEST__ENV$C_RES:\n"
test "env | sort | grep -v \"_=/\""
fi
# **************************************************************************** #

# **************************************************************************** #
# exit
if [ $TEST__EXIT == 1 ]; then
printf "\n$C_G_WHITE TEST__EXIT$C_RES:\n"
test "exit"
test "exit 92233720"
test "exit 9223372036"
test "exit -9223372036"
test "exit 9223372036854775808"
test "exit -9223372036854775809"
test "exit -1"
test "exit -123412341234123398740239"
test "exit 12382397429180470123849"
test "exit -123412341234123398740239 129834761298346981723469182734"
test "exit 12382397429180470123849 129834761298346981723469182734"
test "exit -123412341234123398740239 jkdsafdjs"
test "exit 12382397429180470123849 jkdsafdjs"
test "exit -123412341234123398740239 129834761298346981723469182734 jkdsafdjs"
test "exit 12382397429180470123849 129834761298346981723469182734 jkdsafdjs"
test "exit 123"
test "exit 123 345"
test "exit +12+3"
test "exit ++123"
test "exit -----123"
test "exit 0"
test "exit 1"
test "exit 2"
test "exit -1"
test "exit -2"
test "exit 127"
test "exit -128"
test "exit 255"
test "exit 256"
test "exit -255"
test "exit -256"
test "exit -"
test "exit +"
test "exit ++"
test "exit __"
test "exit a"
test "exit a1"
test "exit 1a1"
test "exit 1a"
test "exit abeille"
test "exit --"
test "exit ---"
test "exit --+-"
test "exit ++"
test "exit +++"
test "exit ++-+"
test "exit 1-"
test "exit 1+"
test "exit 1--"
test "exit 1---"
test "exit 1--+-"
test "exit 1++"
test "exit 1+++"
test "exit 1++-+"
test "exit -1-"
test "exit +1-"
test "exit -1+"
test "exit +1+"
test "exit -1--"
test "exit +1--"
test "exit -1---"
test "exit +1---"
test "exit -1--+-"
test "exit +1--+-"
test "exit -1++"
test "exit +1++"
test "exit -1+++"
test "exit +1+++"
test "exit -1++-+"
test "exit +1++-+"
fi
# **************************************************************************** #

if [ $TEST__BAD == 1 ]; then
printf "\n$C_G_WHITE TEST__BAD$C_RES:\n"
test ";"
test "||"
test "&&"
test ")"
test ";"
test ";;"
test "|"
test "|a"
test "d|;"
test "d                                 ;|&&"
test "ecasd"
test "_"
test "\-"
test "\$"
test "\$?"
test "LONG=aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa ; echo \$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG"
test "LONG=aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa ; echo \$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG\$LONG> long.txt | cat -e"
# yes it's wierd but it's obviously an error of our shell (LINE_MAX is definitivly not a good idea haha)
test "echo STARTaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaEND"
# yes it's wierd but it's obviously an error of our shell (LINE_MAX is definitivly not a good idea haha)
test "echo STARTaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaEND> test1 ; cat -e test1"
fi

if [ $TEST__GOOD == 1 ]; then
printf "\n$C_G_WHITE TEST__GOOD$C_RES:\n"
test "ls;ls|cat -e&&ls>test || cat test | head -c 5 ; echo KO | cat -e && ls ; cat test | head -c 100"
test "ls; && cd / ; pwd && cd \$MAIN_DIR\tester_dir ; ls || pwd; rm qwerwqrqwer"
test "echo hej \'da\' ; jag \'talar\'\"inte\" s\'v\'ens\"ka\""
test "echo START | cat && ls > test >> test >> test | cat -e | cat -e || echo KO || echo NICE && ls | cat | cat -e | head -c 2"
test "ls"
test "cat ../Makefile | head -c 100"
test "ls;cat ../Makefile | head -c 100"
test "ls;cat ../Makefile | head -c 100;ls"
test "ls|cat -e;cat ../Makefile | head -c 100;ls"
test "ls|cat -e;cat ../Makefile | head -c 100;ls;cat ../Makefile | head -c 100;cat ../Makefile | head -c 100;cat ../Makefile | head -c 100"
test "ls|ls"
test "ls|bla"
test "bla|ls"
test "cat|cat|ls"
test "ls|cat -e"
test "ls | cat"
test "cat | ls -l"
test "       \n              "
test "badcmd\n\n\n\necho \$?"
test "badcmd\n\n\n    \necho \$?"
test "\nexit"
test "\nexit exit exit"
test "cd asdfasdf\nok"
test "ls\necho \$?"
test "ls|ls|\n\ncat -e ../Makefile | cat -e | wc -l | cat -e\necho \$?\nasdfs\necho \$?\necho\$?"
test "A=\"cat -e\";ls|\$A|\$A"
printf "$C_G_MAGENTA warning:$C_RES$C_G_WHITE heavy test. this can take several tens of seconds$C_RES\n"
test "ls|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e"
printf "$C_G_MAGENTA warning:$C_RES$C_G_WHITE heavy test. this can take several tens of seconds$C_RES\n"
test "ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls"
printf "$C_G_MAGENTA warning:$C_RES$C_G_WHITE heavy test. this can take several tens of seconds$C_RES\n"
test "ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls;ls -laGhost"
printf "$C_G_MAGENTA warning:$C_RES$C_G_WHITE heavy test. this can take several tens of seconds$C_RES\n"
test "ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls||ls"
printf "$C_G_MAGENTA warning:$C_RES$C_G_WHITE heavy test. this can take several tens of seconds$C_RES\n"
test "ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls&&ls"
fi

if [ $TEST__RANDOM_FRED == 1 ]; then

test "              ls          -l "
test "           echo       \$~\$?\$HOME"
test "           echo      ~"
test "export TILDE=~           echo      \"~\$TILDE~\$TILDE\$~\""
test "           echo       \$.\$?\$HOME"
test "           echo       ~"
test "    export    | sort     |                          grep PWD             "
test "\$PWD"
test "unset 354 ge= PWD \$PWD; \$PWD"
test "BIG=teeeeeeeeeeeeeeeeeeest; export \$BIG\$BIG\$BIG=too_long ; echo \$BIG\$BIG\$BIG"
test "BIG=teeeeeeeeeeeeeeeeeeest; export \$BIG\$BIG\$BIG\$BIG=too_long ; echo \$BIG\$BIG\$BIG\$BIG"
test "BIG=teeeeeeeeeeeeeeeeeeest; export \$BIG\$BIG\$BIG\$BIG\$BIG\$BIG\$BIG\$BIG\$BIG\$BIG\$BIG\$BIG\$BIG\$BIG\$BIG\$BIG=too_long ; echo \$BIG\$BIG\$BIG\$BIG\$BIG\$BIG\$BIG\$BIG"
test "BIG=\$PWD\$PWD\$PWD\$PWD; \$BIG\$BIG\$BIG=too_long"
test "BIG=\$PWD\$PWD\$PWD\$PWD; \$BIG\$BIG\$BIG\$BIG=too_long"
test "BIG=\$PWD\$PWD\$PWD\$PWD; \$BIG\$BIG\$BIG\$BIG\$BIG\$BIG\$BIG\$BIG=too_long"
test "bad one"
test "a=b b=3 c"
test "a=b b=3 c=3; echo \$a\$b\$c"
test "a=b b=3 echo \$a\$b\$c"
test "a=b b=3 ; export a b= c=1 a+ a+=\$c\$c\$c echo \$a\$b\$c"
test "a=b b=3 ; export a b= c=1 a+ a+=\$c\$c\$c ; echo \$a\$b\$c"
test "a=b b=3 _hej; export a b= c=1 a+ a+=\$c\$c\$c ; echo \$a\$b\$c"
test "a=b b=3 _hej=da; export a b= c=1 a+ a+=\$c\$c\$c ; echo \$a\$b\$c"
test "a=b b=3 _he?j=da; export a b= c=1 a+ a+=\$c\$c\$c ; echo \$a\$b\$c"
test "./sre"
test "./Makefile"
test "/bin/notfound"
test "hej"
test ""
test "          "
test "          l "
test "å"
test "./å"
test "mkdir test; cd test; rm -r ../test ; cd ."
test "mkdir test; cd test; rm -r ../test ; cd . ; pwd"
test "mkdir test; cd test; rm -r ../test ; cd . ; echo \$PWD \$OLDPWD"
test "mkdir test; cd test; rm -r ../test ; cd .. ; echo \$PWD \$OLDPWD"
test "mkdir test; cd test; rm -r ../test ; cd .. ; cd -"
test "unset HOME; cd "
test "unset PWD OLDPWD HOME; echo \$PWD \$OLDPWD \$HOME; cd . "
test "\$? \$?"
test "\$#"
test "./notlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilename"
test "/toolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenamee"
test "famf2 > mf2;"
test "echo hej > mf2 ;/toolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenametoolongfilenamee > mf2"
test "lsha ; teaaaa ; cat mf2"
test "lsha > tea; echo hej; cat hea"
test "lsha > tea; echo hej; cat tea"
test "lsha > tea; echo hej; >tea; cat tea;SO FOR SOME REASON STDERR GETS REDIRECTED INTO THE FILE"
test "lsha > tea; echo hej; rm tea; cat tea"
test "lsha > tea ; cat tea"
test "lsha > tea ; cat tea ga"
test "ls > test ; ghhh < test > test2; cat test; echo hej"
test "echo hej > mf2 ; mf2 < mf2aa ; cat mf2aa"
test "mkdir -p ./notlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilename/notlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilename/notlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilename/notlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilename/notlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilename; cd ./notlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilename/notlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilename/notlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilename/notlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilename/notlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilenamenotlongfilename ; pwd"

test "echo aharhhshrah > test < test ; cat test"
test "echo '\$HH' \$HH\$USER\\t \"\\t\""
test "\$USER"
test "\$USER\$NOPE"
test "\$NOPE\$USER\$NOPE"
test "\$NOPE"
test "\$NOPE\$NOPE"

fi

exit_tester
