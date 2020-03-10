/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:59:23 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/10 04:35:45 by tharchen         ###   ########.fr       */
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

	lex = mmalloc(sizeof(t_lexer));
	if (lexer__refill_line(lex, sloc) == ERROR)
	{
		lexer__del(&lex);
		return (NULL);
	}
	return (lex);
}

void			lexer__del(t_lexer **lex)
{
	if (*lex)
	{
		mfree((void **)&(*lex)->line);
		mfree((void **)lex);
	}
}

int				lexer__error(int opt, t_lexer *lex)
{
	if (opt == ERR_UNEXPECTED_EOT)
		ft_dprintf(2, "minishell: unexpected \'end of line\' after \'%c\'\n",
		lex->prev_char);
	else if (opt == ERR_UNSUPPORTED_FEATURE)
		ft_dprintf(2, "minishell: functionality not supported \'%c\'\n",
		lex->current_char);
	else if (opt == ERR_UNSUPPORTED_FEATURE_DBL_AND)
		ft_dprintf(2, "minishell: functionality not supported \'&&\'\n");
	else if (opt == ERR_UNSUPPORTED_FEATURE_DBL_OR)
		ft_dprintf(2, "minishell: functionality not supported \'||\'\n");
	else if (opt == ERR_UNSUPPORTED_FEATURE_SUBSHELL)
		ft_dprintf(2, "minishell: subshells are not supported\n");
	else if (opt == ERR_UNSUPPORTED_FEATURE_HEREDOC)
		ft_dprintf(2, "minishell: heredocs are not supported\n");
	else if (opt == ERR_GNL)
		exit(0);
	else
		ft_dprintf(2, "minishell: invalid character \'%c\' (%#x)\n",
			lex->current_char, lex->current_char);
	return (ERROR);
}

/*
** Ok then. I would tell you a story.
**
** When you take a call to get_next_token, this last will try to return the next
** token he can found on the line since the end posision of the last returned token
** or since the begining for the first call.
**
** First step, we want to pass all the nasty little spaces and ignored characters
** trying to pretend to be tokens ;)
**
** Second step, we send a short message to the lexer to ask him to reset the
** position of the variable start_pos to the current pos (just afters spaces and
** passed characters). start_pos is used to know the start position of the token we
** want to return.
**
** Third step, if we find a match with the defined token EOT, we return a copy
** of this token it.
**
** Fourth step, if we find a match with a defind token listed in the function
** lexer__isdefined_token in lexer__isdefined_tokens.c, we return a copy of this
** token it.
**
** Fifth step, here, we are trying to grab a word. A word is defined by a string
** of letters [a ... z], [A ... Z], numbers [0 ... 9], and listed specials
** characters. A backslash '\' "transform" the next character as a word
** character. The word ended when we found the end of the line or a defined token
** like '&&', '||', '|', ';', '<', '<<', '>' or '&' ('&' is not a valid token, for
** now, it's an error).
**
** Sixth step, just return the word token just found. the token start at
** 'start_pos' included until 'pos' excluded (variable included in lex)
*/

t_token			*lexer__get_next_token(t_lexer *lex) // NEEDS COMMENTS
{
	int			rtype;

	while (lexer__istype(lex, CHR_SPACE | CHR_PASS))
		lexer__advance(lex, 1);
	lexer__set_start_pos(lex, lex->pos);
	if (lexer__istype(lex, CHR_EOT))
		return (token__copy(&g_defined_tokens[I_EOT]));
	if ((rtype = lexer__isdefined_token(lex, ADVANCE)) != I_NONE)
		return (rtype == I_ERR ? NULL : token__copy(&g_defined_tokens[rtype]));
	while (!lexer__istype(lex, CHR_EOT | CHR_SPACE | CHR_PASS | CHR_ERR))
	{
		if (lexer__istype(lex, CHR_BSLASH))
	 	{
			lexer__advance(lex, 1);
			if (lexer__istype(lex, CHR_EOT) &&
				lexer__error(ERR_UNEXPECTED_EOT, lex) == ERROR)
				return (NULL);
			lexer__advance(lex, 1);
		}
		if ((rtype = lexer__isdefined_token(lex, NOADVANCE)) == I_ERR)
			return (NULL);
		if (rtype != I_NONE)
			break ;
		if ((rtype = lexer__isquote(lex)))
			lexer__pass_quotes(lex, rtype);
		lexer__advance(lex, 1);
	}
	return (lexer__token_grabber(lex, WORD));
}
