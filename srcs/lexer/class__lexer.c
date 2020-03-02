/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:59:23 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/02 21:24:28 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** **************************************************************************
** **** lexer object handle *************************************************
** **************************************************************************
*/

t_lexer			*lexer__new(int sloc)
{
	t_lexer		*lex;

	lex = try_malloc(sizeof(t_lexer), _FL_);
	lexer__refill_line(lex, sloc, PROMPT_CASUAL);
	return (lex);
}

void			lexer__del(t_lexer **lex)
{
	if (*lex)
	{
		try_free_((void **)&(*lex)->line, _FL_);
		try_free_((void **)lex, _FL_);
	}
}

void			lexer__error(int opt, t_lexer *lex)
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

/*
** **************************************************************************
** **** is something and peek ***********************************************
** **************************************************************************
*/

int				lexer__istype(t_lexer *lex, t_char_type type)
{
	return (type & g_token_ascii_table[(int)(lex->current_char)]);
}

int				lexer__istype_start(t_lexer *lex, t_char_type type)
{
	return (type & g_token_ascii_table[(int)(lex->start_char)]);
}

char			lexer__peek(t_lexer *lex)
{
	return (lex->line[lex->pos + 1]);
}

int				lexer__isword(t_lexer *lex)
{
	return (lexer__istype(lex, CHR_WORD | CHR_SQUOTE | CHR_DQUOTE |
		CHR_BSLASH));
}

int				lexer__isquote(t_lexer *lex)
{
	return (lexer__istype(lex, CHR_SQUOTE | CHR_DQUOTE));
}

/*
** **************************************************************************
** **** advance and pass function *******************************************
** **************************************************************************
*/

int				lexer__advance(t_lexer *lex, int n)
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

void			lexer__pass_quotes(t_lexer *lex, t_char_type type)
{
	int			found;

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

/*
** **************************************************************************
** **** set and init ********************************************************
** **************************************************************************
*/

void			lexer__set_start_pos(t_lexer *lex, int new_pos)
{
	lex->start = new_pos;
	lex->start_char = lex->line[new_pos];
}

/*
** **************************************************************************
** **** body functions ******************************************************
** **************************************************************************
*/

void			lexer__refill_line(t_lexer *lex, int sloc, int prompt)
{
	try_free_((void **)&lex->line, _FL_);
	print_prompt(sloc, prompt);
	if (get_next_line(0, &lex->line) == -1)
		lexer__error(ERR_GNL, lex);
	if (*lex->line < 0 && ft_dprintf(1, "exit\n"))
		exit (0);
	lex->pos = 0;
	lex->start = 0;
	lex->len_line = ft_strlen(lex->line);
	lex->current_char = lex->line[lex->pos];
	lex->start_char = lex->line[lex->start];
}

t_token			*lexer__token_grabber(t_lexer *lex, t_token_type_m type)
{
	t_token		*new;

	new = token__new(type, ft_strsub(lex->line, lex->start, lex->pos - lex->start),
		lex->start);
	return (new);
}

t_token			*lexer__get_next_token(t_lexer *lex) // NEEDS COMMENTS
{
	int			rtype;

	while (lexer__istype(lex, CHR_SPACE | CHR_PASS))
		lexer__advance(lex, 1);
	lexer__set_start_pos(lex, lex->pos);
	if (lexer__istype(lex, CHR_EOT))
		return (token__copy(&g_defined_tokens[I_EOT]));
	if ((rtype = lexer__isdefined_token(lex, ADVANCE)) != I_NONE)
		return (token__copy(&g_defined_tokens[rtype]));
	while (!lexer__istype(lex, CHR_EOT | CHR_SPACE | CHR_PASS | CHR_ERR | CHR_BSLASH))
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
