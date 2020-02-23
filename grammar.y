# minishell Grammar

<ascii>						: [0 .. 254]
							;
<letter>					: ['a' .. 'z']
							| ['A' .. 'Z']
<symbole>					: '!' | '#' | '%' | '+' | ',' | '-' | '.' | ':'
							| '=' | '@' | '[' | ']' | '^' | '_' | '`' | '{'
							| '}' | '/' | '~' | '?' | '*'|
							;
<digit>						: ['0' .. '9']
							;
<number>					: <digit>
							| <number> <digit>
							;
<escaped>					: '\' <ascii>
							;
<word>						: <letter>
							| <digit>
							| <escaped>
							| <word> <letter>
							| <word> <digit>
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
<list_terminator>			: '\n'
							| ';'
							;
<newline_list>				:
							| <newline_list> '\n'
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
<pipeline>					:
							| <pipeline> '|' <newline_list> <pipeline>
		  					| <command>
