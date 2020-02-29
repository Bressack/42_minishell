/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer__defined_tokens.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:55:50 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/29 08:18:21 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** int					lexer__isdefined_token_dblchar(
** 	int *type, int *len, char *curr, char *next)
** {
** 	len = 0;
** 	type = EOT;
** 	curr = lex->current_char;
** 	next = lex->line[lex->pos + 1];
**
**
** }
*/

int					lexer__isdefined_token(t_lexer *lex, int adv)
{
	int				type;
	int				len;
	char			curr;
	char			next;

	if (!lex->line)
		return (I_ERR);
	len = 0;
	type = EOT;
	curr = lex->current_char;
	next = lex->len_line > 1 ? lex->line[lex->pos + 1] : 0;
	if (lex->len_line > 1 && curr == '>' && next == '>' && (len = 2))
		type = I_DREDIREC_OUT;
	else if (lex->len_line > 1 && curr == '&' && next == '&' && (len = 2))
		type = I_DBL_AND;
	else if (lex->len_line > 1 && curr == '|' && next == '|' && (len = 2))
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
	else if (curr == '&' || curr == '\\')
		lexer__error(SGLAND_NOT_HANDLED, lex);
	else
		return (I_NONE);
	if (adv == ADVANCE)
		lexer__advance(lex, len);
	return (type);
}
