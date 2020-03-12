/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer__defined_tokens.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:55:50 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/12 18:07:21 by tharchen         ###   ########.fr       */
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
	int		tl[2];
	char	cn[2];

	if (!lex->line && (tl[1] = 0))
		return (I_ERR);
	cn[0] = lex->current_char;
	cn[1] = lex->len_line > 1 ? lex->line[lex->pos + 1] : 0;
	if ((tl[0] = lexer__deftoken_double(lex, &tl[1], cn[0], cn[1])) == I_ERR)
	{
		if (unsupported_feature(lex, &tl[0], cn[0], cn[1]))
			return (tl[0]);
		else if (cn[0] == '<' && (tl[1] = 1))
			tl[0] = I_REDIREC_IN;
		else if (cn[0] == '>' && (tl[1] = 1))
			tl[0] = I_REDIREC_OUT;
		else if (tl[0] == I_ERR && cn[0] == '|' && (tl[1] = 1))
			tl[0] = I_PIPE;
		else if (cn[0] == ';' && (tl[1] = 1))
			tl[0] = I_SEMICON;
		else if (!tl[0])
			return (I_NONE);
	}
	if (tl[0] != I_ERR && adv == ADVANCE)
		lexer__advance(lex, tl[1]);
	return (tl[0]);
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
