/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:59:23 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/19 19:29:22 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lexer				lexer__new(char *line)
{
	t_lexer			lex;

	lex.line = line; // not a duplicated str (if line is freed, lex.line will be freed too)
	lex.len_line = ft_strlen(line);
	lex.pos = 0;
	lex.current_char = lex.line[lex.pos];
	return (lex);
}

void				lexer__error(t_lexer *lex)
{
	printf("Invalid character \'%c\' (%#x)\n",
		lex->current_char, lex->current_char);
}

inline int			lexer__istype(char c, t_char_type type)
{
	return (type & g_token_ascii_table[c]);
}

void				lexer__debug(t_lexer *lex)
{
		 if (lexer__istype(lex->current_char, CHR_ERR))			printf("type: CHR_ERR        \n");
	else if (lexer__istype(lex->current_char, CHR_EOT))			printf("type: CHR_EOT        \n");
	else if (lexer__istype(lex->current_char, CHR_SPACE))		printf("type: CHR_SPACE      \n");
	else if (lexer__istype(lex->current_char, CHR_WORD))		printf("type: CHR_WORD       \n");
	else if (lexer__istype(lex->current_char, CHR_LPAREN))		printf("type: CHR_LPAREN     \n");
	else if (lexer__istype(lex->current_char, CHR_RPAREN))		printf("type: CHR_RPAREN     \n");
	else if (lexer__istype(lex->current_char, CHR_REDIREC_IN))	printf("type: CHR_REDIREC_IN \n");
	else if (lexer__istype(lex->current_char, CHR_REDIREC_OUT))	printf("type: CHR_REDIREC_OUT\n");
	else if (lexer__istype(lex->current_char, CHR_SQUOTE))		printf("type: CHR_SQUOTE     \n");
	else if (lexer__istype(lex->current_char, CHR_DQUOTE))		printf("type: CHR_DQUOTE     \n");
	else if (lexer__istype(lex->current_char, CHR_AND))			printf("type: CHR_AND        \n");
	else if (lexer__istype(lex->current_char, CHR_PIPE))		printf("type: CHR_PIPE       \n");
	else if (lexer__istype(lex->current_char, CHR_SEMICON))		printf("type: CHR_SEMICON    \n");
	else if (lexer__istype(lex->current_char, CHR_PATH))		printf("type: CHR_PATH       \n");
	else if (lexer__istype(lex->current_char, CHR_PASS))		printf("type: CHR_PASS       \n");
	else if (lexer__istype(lex->current_char, CHR_DOLLAR))		printf("type: CHR_DOLLAR     \n");
	else if (lexer__istype(lex->current_char, CHR_BSLASH))		printf("type: CHR_BSLASH     \n");
	else if (lexer__istype(lex->current_char, CHR_QUESMARK))	printf("type: CHR_QUESMARK   \n");
	else if (lexer__istype(lex->current_char, CHR_STAR))		printf("type: CHR_STAR       \n");
	else	printf("WTF\n");
}


/*
** lexer__advance:
**
** moves the read head by n
** cannot move after the end of line (PROTECTED)
**
**
*/
int					lexer__advance(t_lexer *lex, int n)
{
	if (lex->current_char == CHR_EOT)
		return (0);
	lex->pos += 1;
	if (lex->pos > lex->len_line - 1)
	{
		lex->current_char = CHR_EOT;
		return (0);
	}
	else
	{
		lex->current_char = lex->line[lex->pos];
		return (n - 1 ? lexer__advance(lex, n - 1) : 1);
	}
}

void				lexer__advence_foreach(t_lexer *lex, t_char_type type)
{
	while (lexer__istype(lex->current_char, type))
		lexer__advance(lex, 1);
}
// echo "1111 ' 111 11111 11' 111 1 1 1 '1'" 2222"222" '333' 4444 5 6 7 "888'8'"88"8"8;10;12

/*
echo
"les amis 'je suis la' et aussi les canards"
les
petit
'paingouin'"des iles"aussi""des hommes"'et'des'femmes'
;
ls
*/

t_token				lexer__get_word_token(t_lexer *lex)
{
	t_token			new;
	int				start_pos;

	start_pos = lex->pos;
	while (	lexer__istype(lex->current_char, CHR_WORD)		||
			lexer__istype(lex->current_char, CHR_BSLASH)	||
			lexer__istype(lex->current_char, CHR_SQUOTE)	||
			lexer__istype(lex->current_char, CHR_DQUOTE))
	{
		if (lexer__istype(lex->current_char, CHR_BSLASH))
			lexer__advance(lex, 2);
		else if (lexer__istype(lex->current_char, CHR_SQUOTE))
		{
			while (lexer__advance(lex, 1) && !lexer__istype(lex->current_char,
				CHR_SQUOTE))
				continue ;
			lexer__advance(lex, 1);
		}
		else if (lexer__istype(lex->current_char, CHR_DQUOTE))
		{
			while (lexer__advance(lex, 1) && !lexer__istype(lex->current_char,
				CHR_DQUOTE))
				continue ;
			lexer__advance(lex, 1);
		}
		else
			lexer__advance(lex, 1);
	}
	new.type = WORD;
	new.len = lex->pos - start_pos;
	new.pos_in_line = start_pos;
	new.value = ft_strsub(lex->line, start_pos, new.len); // malloc = free needed; call token__del() to destroy
	return (new);
}

/*
&&

0: prev_is_word
0: prev_is_spec
0: prev_is_space
0:
0:
0:
0:
0:

0: do_skip_space
0: do_skip_pass
0:
0:
0:
0:
0:
0:

0:
0:
0:
0:
0:
0:
0:
0:

0:
0:
0:
0:
0:
0:
0:
0:
*/

t_token				lexer__get_next_token(t_lexer *lex, int opt)
{
	token			ret;
	int				rtype;

	ret = g_defined_tokens[EOT];
	lexer__advence_foreach(lex, CHR_SPACE | CHR_PASS);
	if ((rtype = lexer__istype(lex->current_char, CHR_ERR | CHR_EOT)))
		return (g_defined_tokens[rtype]);
	if ((idx = lexer__isdefined_token(lex)) != -1)
		return (lexer__get_defined_token(lex));
	else
		return (lexer__get_word_token);
}

t_token				lexer__get_next_token(t_lexer *lex)
{
	lexer__advence_foreach(lex, CHR_SPACE | CHR_PASS);
	if (lexer__istype(lex->current_char, CHR_EOT))
		return (lexer__get_defined_token(EOT));
	else if (lexer__istype(lex->current_char,
		CHR_WORD | CHR_BSLASH | CHR_SQUOTE | CHR_DQUOTE))
		return (lexer__get_word_token(lex));
	else if (lexer__istype(lex->current_char, CHR_ERR))
	{
		lexer__error(lex);
		return (lexer__get_defined_token(ERR));
	}
	return (lexer__search_defined_token(lex));
}

// "les 'enfants' des 'ville' " sont" petits"
// "les 'enfants' des 'ville' \" sont \" petits"


