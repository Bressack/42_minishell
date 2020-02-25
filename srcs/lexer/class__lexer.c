/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:59:23 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/25 13:58:16 by tharchen         ###   ########.fr       */
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

void				lexer__error(int opt, t_lexer *lex)
{
	if (opt == UNEXPECTED_EOF)
		printf("error: unexpected \'EOF\' after \'%c\'\n", lex->current_char);
	else if (opt == SGLAND_NOT_HANDLED)
		printf("error: functionality not supported \'%c\'\n", lex->current_char);
	else if (opt == ERR_GNL)
		printf("error: unable to read on stdout");
	else
		printf("error: invalid character \'%c\' (%#x)\n",
			lex->current_char, lex->current_char);
	exit(-1);
}

inline int			lexer__istype(t_lexer *lex, t_char_type type)
{
	return (type & g_token_ascii_table[(int)(lex->current_char)]);
}

inline int			lexer__istype_start(t_lexer *lex, t_char_type type)
{
	return (type & g_token_ascii_table[(int)(lex->start_char)]);
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
	if (opt == DEBUG_RET_CHAR_TYPE)
	{
		if (lever == POS)
		{
				 if (lexer__istype(lex, CHR_ERR))			return ("CHR_ERR");
			else if (lexer__istype(lex, CHR_EOT))			return ("CHR_EOT");
			else if (lexer__istype(lex, CHR_SPACE))			return ("CHR_SPACE");
			else if (lexer__istype(lex, CHR_WORD))			return ("CHR_WORD");
			else if (lexer__istype(lex, CHR_LPAREN))		return ("CHR_LPAREN");
			else if (lexer__istype(lex, CHR_RPAREN))		return ("CHR_RPAREN");
			else if (lexer__istype(lex, CHR_REDIREC_IN))	return ("CHR_REDIREC_IN");
			else if (lexer__istype(lex, CHR_REDIREC_OUT))	return ("CHR_REDIREC_OUT");
			else if (lexer__istype(lex, CHR_SQUOTE))		return ("CHR_SQUOTE");
			else if (lexer__istype(lex, CHR_DQUOTE))		return ("CHR_DQUOTE");
			else if (lexer__istype(lex, CHR_AND))			return ("CHR_AND");
			else if (lexer__istype(lex, CHR_PIPE))			return ("CHR_PIPE");
			else if (lexer__istype(lex, CHR_SEMICON))		return ("CHR_SEMICON");
			else if (lexer__istype(lex, CHR_PASS))			return ("CHR_PASS");
			else if (lexer__istype(lex, CHR_DOLLAR))		return ("CHR_DOLLAR");
			else if (lexer__istype(lex, CHR_BSLASH))		return ("CHR_BSLASH");
			else											return ("CHR_UNKNOWN");
		}
		else if (lever == START)
		{
				if (lexer__istype_start(lex, CHR_ERR))			return ("CHR_ERR");
			else if (lexer__istype_start(lex, CHR_EOT))			return ("CHR_EOT");
			else if (lexer__istype_start(lex, CHR_SPACE))		return ("CHR_SPACE");
			else if (lexer__istype_start(lex, CHR_WORD))		return ("CHR_WORD");
			else if (lexer__istype_start(lex, CHR_LPAREN))		return ("CHR_LPAREN");
			else if (lexer__istype_start(lex, CHR_RPAREN))		return ("CHR_RPAREN");
			else if (lexer__istype_start(lex, CHR_REDIREC_IN))	return ("CHR_REDIREC_IN");
			else if (lexer__istype_start(lex, CHR_REDIREC_OUT))	return ("CHR_REDIREC_OUT");
			else if (lexer__istype_start(lex, CHR_SQUOTE))		return ("CHR_SQUOTE");
			else if (lexer__istype_start(lex, CHR_DQUOTE))		return ("CHR_DQUOTE");
			else if (lexer__istype_start(lex, CHR_AND))			return ("CHR_AND");
			else if (lexer__istype_start(lex, CHR_PIPE))		return ("CHR_PIPE");
			else if (lexer__istype_start(lex, CHR_SEMICON))		return ("CHR_SEMICON");
			else if (lexer__istype_start(lex, CHR_PASS))		return ("CHR_PASS");
			else if (lexer__istype_start(lex, CHR_DOLLAR))		return ("CHR_DOLLAR");
			else if (lexer__istype_start(lex, CHR_BSLASH))		return ("CHR_BSLASH");
			else												return ("CHR_UNKNOWN");
		}
	}
	else if (opt == DEBUG_POS)
	{
		char *tmp_start = lexer__debug(lex, START, DEBUG_RET_CHAR_TYPE);
		char *tmp_pos = lexer__debug(lex, POS, DEBUG_RET_CHAR_TYPE);

		printf("[ DEBUG :                ] [%s ]\n", lex->line);
		printf("start: %d | char: (%c)\n", lex->start, lex->start_char);
		printf("pos  : %d | char: (%c)\n", lex->pos, lex->current_char);
		printf("[ start : %-15s] [%*s%c%*s]\n", tmp_start, lex->start, "", '^', lex->len_line - lex->start, "");
		printf("[ pos   : %-15s] [%*s%c%*s]\n", tmp_pos, lex->pos, "", '^', lex->len_line - lex->pos, "");
		printf("*****************************************************************************\n");
	}
	return (NULL);
}

void				lexer__set_start_pos(t_lexer *lex, int new_pos)
{
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
void			lexer__advence_foreach(t_lexer *lex, t_char_type type, int whis)
{
	while (1)
	{
		if (lexer__istype(lex, CHR_BSLASH) && type == CHR_WORD)
			lexer__advance(lex, 1);
		else if (lexer__istype(lex, CHR_BSLASH) && (type == CHR_DQUOTE ||
			type == CHR_SQUOTE) && whis == WHILE_ISNOT)
			lexer__advance(lex, 1);
		if (!lexer__advance(lex, 1))
			break ;
		if (whis == WHILE_ISNOT ? lexer__istype(lex, type) : !lexer__istype(
			lex, type))
			break ;
	}
}

char				lexer__peek(t_lexer *lex)
{
	return (lex->line[lex->pos + 1]);
}

void				lexer__refill_line(t_lexer *lex, int sloc, int prompt)
{
	try_free_((void **)&lex->line, _FL_);
	print_prompt(sloc, prompt);
	if (get_next_line(0, &lex->line) == -1)
		lexer__error(ERR_GNL, lex);
	lex->pos = 0;
	lex->start = 0;
	lex->len_line = ft_strlen(lex->line);
	lex->current_char = lex->line[lex->pos];
	lex->start_char = lex->line[lex->start];
}

int					lexer__isword(t_lexer *lex)
{
	return (lexer__istype(lex, CHR_WORD | CHR_SQUOTE | CHR_DQUOTE |
		CHR_BSLASH));
}

int					lexer__isquote(t_lexer *lex)
{
	return (lexer__istype(lex, CHR_SQUOTE | CHR_DQUOTE));
}

void				lexer__pass_quotes(t_lexer *lex, t_char_type type)
{
	int				found;

	found = 0;
	lexer__advance(lex, 1);
	while (!lexer__istype(lex, type))
	{
		if (lexer__istype(lex, CHR_BSLASH))
			lexer__advance(lex, 1);
		if (!lexer__advance(lex, 1))
			break ;
	}
	if (!lexer__istype(lex, type))
		lexer__error(UNEXPECTED_EOF, lex);

}

t_token				lexer__token_grabber(t_lexer *lex, t_token_type_m type)
{
	t_token			new;

	new.type = type;
	new.len = lex->pos - lex->start;
	new.pos_in_line = lex->start;
	ft_strncpy(new.value, &lex->line[lex->start], new.len);
	new.value[new.len] = 0;
	return (new);
}

t_token				lexer__get_next_token(t_lexer *lex)
{
	int				rtype;

	while (lexer__istype(lex, CHR_SPACE | CHR_PASS))
		lexer__advance(lex, 1);
	lexer__set_start_pos(lex, lex->pos);
	if (lexer__istype(lex, CHR_EOT))
		return (g_defined_tokens[I_EOT]);
	if ((rtype = lexer__isdefined_token(lex, ADVANCE)) != I_NONE)
		return (g_defined_tokens[rtype]);
	lexer__istype(lex, CHR_DOLLAR) ? lexer__advance(lex, 1) : 0;
	if (lexer__istype(lex, CHR_DOLLAR) && lexer__advance(lex, 1))
		return (lexer__token_grabber(lex, WORD));
	while (!lexer__istype(lex, CHR_EOT | CHR_SPACE | CHR_PASS | CHR_ERR | CHR_DOLLAR))
	{
		lexer__istype(lex, CHR_BSLASH) ? lexer__advance(lex, 2) : 0;
		if (lexer__isdefined_token(lex, NOADVANCE) != I_NONE)
			break ;
		if ((rtype = lexer__isquote(lex)))
			lexer__pass_quotes(lex, rtype);
		lexer__advance(lex, 1);
	}
	return (lexer__token_grabber(lex, WORD));
}


