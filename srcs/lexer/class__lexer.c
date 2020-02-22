/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:59:23 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/22 13:24:16 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lexer				lexer__new(char *line)
{
	t_lexer			lex;

	lex.line = line; // not a duplicated str (if line is freed, lex.line will be freed too)
	lex.len_line = ft_strlen(line);
	lex.pos = 0;
	lex.start = 0;
	lex.current_char = lex.line[lex.pos];
	lex.start_char = lex.line[lex.pos];
	return (lex);
}

inline void			lexer__error(t_lexer *lex)
{
	printf("Invalid character \'%c\' (%#x)\n",
		lex->current_char, lex->current_char);
}

inline int			lexer__istype(char c, t_char_type type)
{
	return (type & g_token_ascii_table[(int)c]);
}

/*
** function here just for the debug, it will be remove at the end
**
** lexer__debug take a t_lex as parameter and print a debugging message on
** stderr about the character type of lex->current_char
** if the type of lex->current_char is unknown, print '/!\ UNKNOWN CHARACTER TYPE /!\' on stderr
*/
char				*lexer__debug(t_lexer *lex, int lever, int opt)
{
	if (opt == DEBUG_PRINT_CHAR_TYPE)
	{
			 if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_ERR))		dprintf(2, "type: CHR_ERR        \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_EOT))		dprintf(2, "type: CHR_EOT        \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_SPACE))		dprintf(2, "type: CHR_SPACE      \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_WORD))		dprintf(2, "type: CHR_WORD       \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_LPAREN))		dprintf(2, "type: CHR_LPAREN     \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_RPAREN))		dprintf(2, "type: CHR_RPAREN     \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_REDIREC_IN))	dprintf(2, "type: CHR_REDIREC_IN \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_REDIREC_OUT))dprintf(2, "type: CHR_REDIREC_OUT\n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_SQUOTE))		dprintf(2, "type: CHR_SQUOTE     \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_DQUOTE))		dprintf(2, "type: CHR_DQUOTE     \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_AND))		dprintf(2, "type: CHR_AND        \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_PIPE))		dprintf(2, "type: CHR_PIPE       \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_SEMICON))	dprintf(2, "type: CHR_SEMICON    \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_SLASH))		dprintf(2, "type: CHR_SLASH      \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_PASS))		dprintf(2, "type: CHR_PASS       \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_DOLLAR))		dprintf(2, "type: CHR_DOLLAR     \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_BSLASH))		dprintf(2, "type: CHR_BSLASH     \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_QUESMARK))	dprintf(2, "type: CHR_QUESMARK   \n");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_STAR))		dprintf(2, "type: CHR_STAR       \n");
		else	dprintf(2, "CHR_UNKNOWN\n");
	}
	if (opt == DEBUG_RET_CHAR_TYPE)
	{
			 if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_ERR))		return ("CHR_ERR");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_EOT))		return ("CHR_EOT");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_SPACE))		return ("CHR_SPACE");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_WORD))		return ("CHR_WORD");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_LPAREN))		return ("CHR_LPAREN");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_RPAREN))		return ("CHR_RPAREN");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_REDIREC_IN))	return ("CHR_REDIREC_IN");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_REDIREC_OUT))return ("CHR_REDIREC_OUT");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_SQUOTE))		return ("CHR_SQUOTE");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_DQUOTE))		return ("CHR_DQUOTE");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_AND))		return ("CHR_AND");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_PIPE))		return ("CHR_PIPE");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_SEMICON))	return ("CHR_SEMICON");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_SLASH))		return ("CHR_SLASH");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_PASS))		return ("CHR_PASS");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_DOLLAR))		return ("CHR_DOLLAR");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_BSLASH))		return ("CHR_BSLASH");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_QUESMARK))	return ("CHR_QUESMARK");
		else if (lexer__istype(lever == POS ? lex->current_char : lex->start_char, CHR_STAR))		return ("CHR_STAR");
		else	return ("CHR_UNKNOWN");
	}
	else if (opt == DEBUG_POS)
	{
		char *tmp_start = lexer__debug(lex, START, DEBUG_RET_CHAR_TYPE);
		char *tmp_pos = lexer__debug(lex, POS, DEBUG_RET_CHAR_TYPE);
		printf("[ DEBUG :                ] [%s ]\n", lex->line);
		printf("[ start : %-15s] [%*s%c%*s]\n", tmp_start, lex->start, "", '^', lex->len_line - lex->start, "");
		printf("[ pos   : %-15s] [%*s%c%*s]\n", tmp_pos, lex->pos, "", '^', lex->len_line - lex->pos, "");
	}
	return (NULL);
}

void				lexer__set_start_pos(t_lexer *lex, int new_pos)
{
	if (new_pos >= lex->len_line - 1)
		new_pos = lex->len_line - 1;
	lex->start = new_pos;
	lex->start_char = lex->line[new_pos];
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
		return (n - 1 > 0 ? lexer__advance(lex, n - 1) : 1);
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

void				lexer__refill_line(t_lexer *lex, int join_nl, int prompt)
{
	char			*line;
	char			*tmp;

	print_prompt(prompt);
	if (get_next_line(0, &line) == -1)
	{
		dprintf(2, "gnl error (%s - %d)\n", _FL_);
		exit(-1);
	}
	if (lex->line)
	{
		if (join_nl)
			tmp = ft_strjoin(3, lex->line, "\n", line);
		else
			tmp = ft_strjoin(2, lex->line, line);
		try_free_((void **)&lex->line, _FL_);
		try_free_((void **)&line, _FL_);
		lex->line = tmp;
	}
	else
		*lex = lexer__new(line);
	lex->len_line = ft_strlen(lex->line);
	lex->current_char = lex->line[lex->pos];
	// lexer__debug(lex, POS, DEBUG_PRINT_CHAR_TYPE);
	// lexer__debug(lex, POS, DEBUG_POS);
}

void				lexer__get_word_quote_token(t_lexer *lex, t_char_type ct)
{
	while (1)
	{
		if (!lexer__advance(lex, 1))
			lexer__refill_line(lex, 1, ct == CHR_SQUOTE ? PROMPT_SQUOTE : PROMPT_DQUOTE);
		else if (lexer__istype(lex->current_char, CHR_BSLASH))
		{
			if (!lexer__advance(lex, 1))
				lexer__refill_line(lex, 0, PROMPT_BSLASH);
		}
		else if (lexer__istype(lex->current_char, ct))
			break ;
	}
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

	// lexer__debug(lex, POS, DEBUG_PRINT_CHAR_TYPE);
	// lexer__debug(lex, POS, DEBUG_POS);
	while (lexer__istype(lex->current_char,
		CHR_WORD | CHR_SQUOTE | CHR_DQUOTE | CHR_BSLASH | CHR_STAR | CHR_SLASH))
	{
		if (lexer__istype(lex->current_char, CHR_BSLASH))
		{
			if (!lexer__advance(lex, 2))
				lexer__refill_line(lex, 0, PROMPT_BSLASH);
		}
		else if ((ct = lexer__istype(lex->current_char, CHR_SQUOTE | CHR_DQUOTE)))
			lexer__get_word_quote_token(lex, ct);
		else
			lexer__advance(lex, 1);
	}
	new.type = WORD;
	new.len = lex->pos - lex->start;
	new.pos_in_line = lex->start;
	ft_strncpy(new.value, &lex->line[lex->start], new.len);
	new.value[new.len] = 0;
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
	lexer__set_start_pos(lex, lex->pos);
	if ((rtype = lexer__istype(lex->current_char, CHR_ERR | CHR_EOT)))
		ret = g_defined_tokens[rtype];
	else
		ret = lexer__search_defined_token(lex);
	return (ret);
}

// "les 'enfants' des 'ville' " sont" petits"
// "les 'enfants' des 'ville' \" sont \" petits"

