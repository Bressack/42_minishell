rm -f tree.png
rm -f tree.dot
make\
&& (echo "$1" ; echo "exit") | ./minishell \
# && dot -Tpng tree.dot -o tree.png && open tree.png
