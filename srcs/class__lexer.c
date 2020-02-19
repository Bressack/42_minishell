/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:59:23 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/19 23:14:37 by tharchen         ###   ########.fr       */
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

/*
** function here just for the debug, it will be remove at the end
**
** lexer__debug take a t_lex as parameter and print a debugging message on
** stderr about the character type of lex->current_char
** if the type of lex->current_char is unknown, print '/!\ UNKNOWN CHARACTER TYPE /!\' on stderr
*/
void				lexer__debug(t_lexer *lex)
{
		 if (lexer__istype(lex->current_char, CHR_ERR))			dprintf(2, "type: CHR_ERR        \n");
	else if (lexer__istype(lex->current_char, CHR_EOT))			dprintf(2, "type: CHR_EOT        \n");
	else if (lexer__istype(lex->current_char, CHR_SPACE))		dprintf(2, "type: CHR_SPACE      \n");
	else if (lexer__istype(lex->current_char, CHR_WORD))		dprintf(2, "type: CHR_WORD       \n");
	else if (lexer__istype(lex->current_char, CHR_LPAREN))		dprintf(2, "type: CHR_LPAREN     \n");
	else if (lexer__istype(lex->current_char, CHR_RPAREN))		dprintf(2, "type: CHR_RPAREN     \n");
	else if (lexer__istype(lex->current_char, CHR_REDIREC_IN))	dprintf(2, "type: CHR_REDIREC_IN \n");
	else if (lexer__istype(lex->current_char, CHR_REDIREC_OUT))	dprintf(2, "type: CHR_REDIREC_OUT\n");
	else if (lexer__istype(lex->current_char, CHR_SQUOTE))		dprintf(2, "type: CHR_SQUOTE     \n");
	else if (lexer__istype(lex->current_char, CHR_DQUOTE))		dprintf(2, "type: CHR_DQUOTE     \n");
	else if (lexer__istype(lex->current_char, CHR_AND))			dprintf(2, "type: CHR_AND        \n");
	else if (lexer__istype(lex->current_char, CHR_PIPE))		dprintf(2, "type: CHR_PIPE       \n");
	else if (lexer__istype(lex->current_char, CHR_SEMICON))		dprintf(2, "type: CHR_SEMICON    \n");
	else if (lexer__istype(lex->current_char, CHR_PATH))		dprintf(2, "type: CHR_PATH       \n");
	else if (lexer__istype(lex->current_char, CHR_PASS))		dprintf(2, "type: CHR_PASS       \n");
	else if (lexer__istype(lex->current_char, CHR_DOLLAR))		dprintf(2, "type: CHR_DOLLAR     \n");
	else if (lexer__istype(lex->current_char, CHR_BSLASH))		dprintf(2, "type: CHR_BSLASH     \n");
	else if (lexer__istype(lex->current_char, CHR_QUESMARK))	dprintf(2, "type: CHR_QUESMARK   \n");
	else if (lexer__istype(lex->current_char, CHR_STAR))		dprintf(2, "type: CHR_STAR       \n");
	else	dprintf(2, "/!\\ UNKNOWN CHARACTER TYPE /!\\\n");
}


/*
** return: int
** lexer__advance
** parameter: t_lexer *lex, int n
**
** lexer__advance try to advance the reading head by the second parameter 'n'
**
** if lexer__advance fall on the end of the lex->line during the process, it
** assigns the CHR_EOT character type to lex->current_char and return 0
** else return 1
**
** it's a recurcive function
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

/*
** return: void
** lexer__advence_foreach
** parameter: t_lexer *lex, t_char_type type
**
** lexer__advence_foreach advance until lex->current_char type is egale to the
** second parameter 'type'
*/
void				lexer__advence_foreach(t_lexer *lex, t_char_type type)
{
	while (lexer__istype(lex->current_char, type))
		lexer__advance(lex, 1);
}

/*
** return: t_token
** lexer__get_word_token
** parameter: t_lexer *lex
**
** lexer__get_word_token get the following word token present in lex->line
** and starting at lex->start
**
** while lex->current_char is a CHR_WORD character type:
** if lex->current_char is a back slash then pass it and pass his next character
** else if lex->current_char is a quote (single or double) then advance to the
** next corresponding quote
** else lex->current_char is a CHR_WORD character so just advance
**
** then
**
** substitute the token from line to a new WORD token
** then
** return the WORD token
*/
t_token				lexer__get_word_token(t_lexer *lex)
{
	t_token			new;
	t_char_type		ct; // char type

	while (lexer__istype(lex->current_char,
		CHR_WORD | CHR_BSLASH | CHR_SQUOTE | CHR_DQUOTE)
	{
		if (lexer__istype(lex->current_char, CHR_BSLASH))
			lexer__advance(lex, 2);
		else if (ct = lexer__istype(lex->current_char, CHR_SQUOTE | CHR_DQUOTE))
		{
			while (lexer__advance(lex, 1) &&
				!lexer__istype(lex->current_char, ct))
				continue ;
			lexer__advance(lex, 1);
		}
		else
			lexer__advance(lex, 1);
	}
	new = lexer__get_defined_token(WORD);
	new.len = lex->pos - lex->start;
	new.pos_in_line = lex->start;
	new.value = ft_strsub(lex->line, lex->start, new.len); // malloc = free needed; call token__del() on the token to destroy this string
	return (new);
}

/*
** return t_token
** lexer__get_next_token
** parameter: t_lexer *lex
**
** lexer__get_next_token try to return the next token present in the string
** lex->line
**
** skip all spaces and ignored characters
** then
** if current_char is invalid or the end of line, return a corresponding token
** ERR for invalid and EOT for end of line
** then
** try to find a defined token into lexer__search_defined_token
** if lexer__search_defined_token dont find defined token, it will return
** a WORD token instead
** then
** set the begining of the future next token on the character next to the last
** of the current token (which one into 'ret')
** then
** return the grabbed token
*/
t_token				lexer__get_next_token(t_lexer *lex)
{
	t_token			ret;
	int				rtype;

	ret = g_defined_tokens[EOT];
	lexer__advence_foreach(lex, CHR_SPACE | CHR_PASS);
	if ((rtype = lexer__istype(lex->current_char, CHR_ERR | CHR_EOT)))
		return (g_defined_tokens[rtype]);
	ret = lexer__search_defined_token(lex);
	lex.start += ret.len;
	return (ret);
}

// "les 'enfants' des 'ville' " sont" petits"
// "les 'enfants' des 'ville' \" sont \" petits"


