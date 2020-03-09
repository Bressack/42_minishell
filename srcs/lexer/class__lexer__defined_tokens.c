/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer__defined_tokens.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:55:50 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/09 04:40:19 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#if BONUS == 1

int			unsupported_feature(t_lexer *lex, int *type, char curr, char next)
{
	if (curr == '(' && !(*type = I_ERR))
		lexer__error(ERR_UNSUPPORTED_FEATURE_SUBSHELL, lex);
	else if (curr == ')' && !(*type = I_ERR))
		lexer__error(ERR_UNSUPPORTED_FEATURE_SUBSHELL, lex);
	else if (lex->len_line > 1 && curr == '<' && next == '<' &&
		!(*type = I_ERR))
		lexer__error(ERR_UNSUPPORTED_FEATURE_HEREDOC, lex);
	else if (curr == '&' && !(*type = I_ERR))
		lexer__error(ERR_UNSUPPORTED_FEATURE, lex);
	else
		return (0);
	return (1);
}

int			lexer__deftoken_double(t_lexer *lex, int *len, char curr, char next)
{
	if (lex->len_line > 1 && curr == '&' && next == '&' && (*len = 2))
		return (I_DBL_AND);
	if (lex->len_line > 1 && curr == '|' && next == '|' && (*len = 2))
		return (I_DBL_OR);
	if (lex->len_line > 1 && curr == '>' && next == '>' && (*len = 2))
		return (I_DREDIREC_OUT);
	return (0);
}

int			lexer__isdefined_token(t_lexer *lex, int adv)
{
	int		type;
	int		len;
	char	curr;
	char	next;

	if (!lex->line && (len = 0))
		return (I_ERR);
	curr = lex->current_char;
	next = lex->len_line > 1 ? lex->line[lex->pos + 1] : 0;
	type = lexer__deftoken_double(lex, &len, curr, next);
	if (type == I_ERR && unsupported_feature(lex, &type, curr, next))
		return (type);
	else if (curr == '<' && (len = 1))
		type = I_REDIREC_IN;
	else if (curr == '>' && (len = 1))
		type = I_REDIREC_OUT;
	else if (type == I_ERR && curr == '|' && (len = 1))
		type = I_PIPE;
	else if (curr == ';' && (len = 1))
		type = I_SEMICON;
	else if (!type)
		return (I_NONE);
	if (type != I_ERR && adv == ADVANCE)
		lexer__advance(lex, len);
	return (type);
}
#else

int			unsupported_feature(t_lexer *lex, int *type, char curr, char next)
{
	if (lex->len_line > 1 && curr == '&' && next == '&' && !(*type = I_ERR))
		lexer__error(ERR_UNSUPPORTED_FEATURE_DBL_AND, lex);
	else if (lex->len_line > 1 && curr == '|' && next == '|'
		&& !(*type = I_ERR))
		lexer__error(ERR_UNSUPPORTED_FEATURE_DBL_OR, lex);
	else if (curr == '(' && !(*type = I_ERR))
		lexer__error(ERR_UNSUPPORTED_FEATURE_SUBSHELL, lex);
	else if (curr == ')' && !(*type = I_ERR))
		lexer__error(ERR_UNSUPPORTED_FEATURE_SUBSHELL, lex);
	else if (lex->len_line > 1 && curr == '<' && next == '<'
		&& !(*type = I_ERR))
		lexer__error(ERR_UNSUPPORTED_FEATURE_HEREDOC, lex);
	else if (curr == '&' && !(*type = I_ERR))
		lexer__error(ERR_UNSUPPORTED_FEATURE, lex);
	else
		return (0);
	return (1);
}

int			lexer__isdefined_token(t_lexer *lex, int adv)
{
	int		len;
	int		type;
	char	curr;
	char	next;

	if (!lex->line && !(len = 0))
		return (I_ERR);
	curr = lex->current_char;
	next = lex->len_line > 1 ? lex->line[lex->pos + 1] : 0;
	if ((type = EOT) && unsupported_feature(lex, &type, curr, next))
		return (type);
	if (lex->len_line > 1 && curr == '>' && next == '>' && (len = 2))
		type = I_DREDIREC_OUT;
	else if (curr == '<' && (len = 1))
		type = I_REDIREC_IN;
	else if (curr == '>' && (len = 1))
		type = I_REDIREC_OUT;
	else if (curr == '|' && (len = 1))
		type = I_PIPE;
	else if (curr == ';' && (len = 1))
		type = I_SEMICON;
	else
		return (I_NONE);
	type != I_ERR && adv == ADVANCE ? lexer__advance(lex, len) : 0;
	return (type);
}
#endif
