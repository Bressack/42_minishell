# minishell Grammar

ASCII						: [0 .. 254]
							;
LETTER						: ['a' .. 'z']
							| ['A' .. 'Z']
SYMBOLE						: '!' | '#' | '%' | '+' | ',' | '-' | '.' | ':'
							| '=' | '@' | '[' | ']' | '^' | '_' | '{'
							| '}' | '/' | '~' | '?' | '*'
							;
DIGIT						: ['0' .. '9']
							;
<number>					: DIGIT
							| <number> DIGIT
							;
<escaped>					: '\' ASCII
							;
<empty>						:
							;
<word>						: LETTER
							| DIGIT
							| SYMBOLE
							| <escaped>
							| <word> LETTER
							| <word> DIGIT
							| <word> SYMBOLE
							| <word> <escaped>
							;
<word_list> 				: <word>
							| <word_list> <word>
							;
<assignment_word>			: <word> '=' <word>
							;
<redirection>				: '>' <word>
							| '<' <word>
							| '>>' <word>
							| <number> '>' <word>
							| <number> '<' <word>
							| <number> '>>' <word>
<simple_command_element>	: <word>
							| <assignment_word>
							| <redirection>
							;
<redirection_list>			: <redirection>
							| <redirection_list> <redirection>
							;
<simple_command>			: <simple_command_element>
							| <simple_command> <simple_command_element>
							;
<command>					: <simple_command>
							| <shell_command>
							| <shell_command> <redirection_list>
							;
<subshell>					: '(' <compound_list> ')'
							;
<list>						: <newline_list> <list0>
							;
<compound_list>				: <list>
							| <newline_list> <list1>

<list0>						: <list1> '\n' <newline_list>
							| <list1> '&' <newline_list>
							| <list1> ';' <newline_list>
							;
<list1>						: <list1> '&&' <newline_list> <list1>
							| <list1> '||' <newline_list> <list1>
							| <list1> '&' <newline_list> <list1>
							| <list1> ';' <newline_list> <list1>
							| <list1> '\n' <newline_list> <list1>
							| <pipeline>
							;
<newline_list>				: <empty>
							| <newline_list> '\n'
							;
%% start					: <expr>
							;
<expr>						: <empty>
							| <simple_list>
							;
<simple_list>				: <simple_list1>
							| <simple_list1> '&'
							| <simple_list1> ';'
							;
<simple_list1>				: <simple_list1> '&&' <newline_list> <simple_list1>
							| <simple_list1> '||' <newline_list> <simple_list1>
							| <simple_list1> '&' <simple_list1>
							| <simple_list1> ';' <simple_list1>
							| <pipeline>
							;
<pipeline>					: <empty>
							| <pipeline> '|' <newline_list> <pipeline>
		  					| <command>
