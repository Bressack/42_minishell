# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/05 21:37:03 by tharchen          #+#    #+#              #
#    Updated: 2020/03/07 08:18:27 by tharchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/sh
# a tester for minishell (new 42_cursus)

USER_BIN=$1

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
	mkdir -p tester_dir
	rm -rf tester_dir/*
	cp $1 tester_dir/
}

exit_tester()
{
	printf "test succeded %d/%d\n" $TOTAL_SUCCESS $TOTAL_TEST
	# rm -rf tester_dir
}

test()
{
	# $USER_BIN="$(basename -- USER_BIN)"
	(echo "$1" ; echo "exit") | $USER_BIN 2>&- > tester_dir/user_output
	(echo "$1" ; echo "exit") | /bin/bash 2>&- > tester_dir/bash_output
	# echo "user_output" ; cat tester_dir/user_output ; echo
	# echo "bash_output" ; cat tester_dir/bash_output ; echo
	let "TOTAL_TEST+=1"
	diff --text tester_dir/user_output tester_dir/bash_output > /dev/null
	if [[ $? == 0 ]]; then
		printf "\033[33;01mtest \033[32;01mOK\033[0m : $1\n"
		let "TOTAL_SUCCESS+=1"
	else
		printf "\033[33;01mtest \033[31;01mKO\033[0m : $1\n"
	fi
	diff --text tester_dir/user_output tester_dir/bash_output
}

init_tester $1 $2 $3

# **************************************************************************** #
# *** tests ****************************************************************** #
# **************************************************************************** #

test ""
test "ls"
# test "echo \'salut\'"
# test "ls|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e|cat -e "
# test "ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|cat -e"
# test "mkdir ok
# cd ok
# pwd
# rm -rf ../ok
# cd .
# cd ..
# pwd"
# test "ls | asdf"
# test "ls > test && cat test"
# test "ls > test
# ls >> test
# cat test | cat -e | cat -e && echo KO | cat -e"
# test "echo SALUT > test ; rm test ; cat test"
# test "echo \"coucou les \'amis\' je suis la\""
# test "echo gotta sleep, se ya tommorow; echo 'Hello future theo ;)'"
# test "cat /dev/null"
# test "man bash | head -c 1000 | cat -e | tail"
# test "< test"
# test "rm test
# > test
# ls test
# rm test"
# test "export HEJ=da;echo \$HEJ"

# **************************************************************************** #
# **************************************************************************** #
# **************************************************************************** #
exit_tester
