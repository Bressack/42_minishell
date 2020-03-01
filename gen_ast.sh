rm -f tree.png
rm -f tree.dot
make\
&& printf "$1\nexit\n" | ./minishell \
# && dot -Tpng tree.dot -o tree.png && open tree.png