/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer__advance.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 04:32:30 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/12 18:01:46 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** **************************************************************************
** **** advance and pass function *******************************************
** **************************************************************************
*/

/*
** its the 'i++' of the lexer. lexer__advance try to advance the read head in
** line if the current character is already an EOT and return 0, otherwize,
** advance and return 1.
** it's a recurcive function, advance of 1 char and recall itself while n > 0 or
** current_char != EOT.
** PROTECTED: do not go throught the EOT
*/

int			lexer__advance(t_lexer *lex, int n)
{
	if (lex->current_char == CHR_EOT)
		return (0);
	lex->prev_char = lex->current_char;
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
** advance the read head while the current_char is of the same type as the
** variable 'type'
*/

void		lexer__advence_foreach(t_lexer *lex, t_char_type type, int whis)
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

/*
** advance the read head until the current char is not the same quote as the
** start of the function. e.g '"' will go to the next '"' and ''' go to the
** next '''.
*/

int			lexer__pass_quotes(t_lexer *lex, t_char_type type)
{
	int		found;

	found = 0;
	lexer__advance(lex, 1);
	while (!lexer__istype(lex, type))
	{
		if (lexer__istype(lex, CHR_BSLASH))
			lexer__advance(lex, 1);
		if (!lexer__advance(lex, 1))
			break ;
	}
	if (!lexer__istype(lex, type) &&
		lexer__error(EUE, lex) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
