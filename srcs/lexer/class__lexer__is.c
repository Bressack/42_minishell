/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer__is.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 04:30:39 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/10 04:35:43 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
