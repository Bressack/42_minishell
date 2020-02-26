/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:59:23 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/26 21:46:02 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lexer				lexer__new(int sloc)
{
	t_lexer			lex;

	lexer__refill_line(&lex, sloc, PROMPT_CASUAL);
	return (lex);
}

void				lexer__del(t_lexer *lex)
{
	try_free_((void **)&lex->line, _FL_);
}

void				lexer__error(int opt, t_lexer *lex)
{
	if (opt == UNEXPECTED_EOT)
		printf("error: unexpected \'EOT\' after \'%c\'\n", lex->current_char);
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
		lexer__error(UNEXPECTED_EOT, lex);

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


