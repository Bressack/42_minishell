/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer__defined_tokens.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:55:50 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/25 00:12:12 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int					lexer__isdefined_token(t_lexer *lex)
{
	int				type;
	int				len;
	char			curr;
	char			next;

	len = 0;
	type = EOT;
	curr = lex->current_char;
	next = lex->line[lex->pos + 1];
	if (curr == '>' && next == '>' && (len = 2))
		type = I_DREDIREC_OUT;
	else if (curr == '&' && next == '&' && (len = 2))
		type = I_DBL_AND;
	else if (curr == '|' && next == '|' && (len = 2))
		type = I_DBL_OR;
	else if (curr == '(' && (len = 1))
		type = I_LPAREN;
	else if (curr == ')' && (len = 1))
		type = I_RPAREN;
	else if (curr == '<' && (len = 1))
		type = I_REDIREC_IN;
	else if (curr == '>' && (len = 1))
		type = I_REDIREC_OUT;
	else if (curr == '|' && (len = 1))
		type = I_PIPE;
	else if (curr == ';' && (len = 1))
		type = I_SEMICON;
	else if (curr == '&')
	{
		lexer__error(SGLAND_NOT_HANDLED, lex);
		return (I_ERR);
	}
	else
		return (NONE);
	lexer__advance(lex, len);
	return (type);
}
