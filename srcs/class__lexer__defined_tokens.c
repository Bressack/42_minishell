/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer__defined_tokens.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:55:50 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/19 15:07:08 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** return: t_token
** lexer__get_defined_token()
** parameter: t_token_type, type of the desired token
**
** return a token who match with type parameter
**
** if lexer__get_defined_token return a token typed NONE that is meaning the
** desired type is not a defined token (see also: class__token__global_arrays.c)
*/

t_token				lexer__get_defined_token(t_token_type type)
{
	int				i;

	i = 0;
	while (g_defined_tokens[i].type != NONE && g_defined_tokens[i].type != type)
		i++;
	return (g_defined_tokens[i]);
}

/*
** return: int
** lexer__isdefined_token()
** parameter: t_lexer, (see class__lexer.h)
**
** return the an index of the global array g_defined_tokens
** this index point on the defined token corresponding to lex->current_char
**
** return -1 if no match
*/
int					lexer__isdefined_token(t_lexer *lex)
{
	int				i;
	int				j_max;
	int				i_max;

	i_max = -1;	// i save
	j_max = -1;	// j save
	i = -1;
	while (g_defined_tokens[++i].type != NONE) // until the end of the array
	{
		if (g_defined_tokens[i].value == NULL)
			continue ; // ERR or EOT
		if (j_max > 0 && g_defined_tokens[i].len < g_defined_tokens[j_max].len)
			continue ; // avoid useless calcules cause g_defined_tokens[i] can't match more than g_defined_tokens[j_max]
		if (!ft_strncmp(g_defined_tokens[i].value, &lex->line[lex->pos], g_defined_tokens[i].len))
		{
			if (j_max <= g_defined_tokens[i].len)
			{
				j_max = g_defined_tokens[i].len;
				i_max = i;
			}
		}
	}
	return (i_max);
}

/*
** return: t_token
** lexer__search_defined_token
** parameter: t_lexer
**
** retuen a token corresponding to the matched token found in line
** ex: line: ls && echo
**              ^~
** there is a token '&&' so return the token '&&' who is in the global array
** g_defined_tokens.
**
**
** ex: line & echo
**          ^
** there, '&' is not in the global array g_defined_tokens, so le lexer will
** read it as a word character.

** if no match, current_char is taken as a word and lexer__search_defined_token
** call lexer__get_word_token to found a word token who start by this char
*/

t_token				lexer__search_defined_token(t_lexer *lex)
{
	int				i;
	int				token_idx;

	if ((token_idx = lexer__isdefined_token(lex)) == -1)
		return (lexer__get_word_token(lex));
	// return (lexer__get_defined_token(ERR));
	i = -1;
	while (++i < g_defined_tokens[token_idx].len)
		lexer__advance(lex, 1);
	return (g_defined_tokens[token_idx]); // if the while statement has found a corresponding token in the table, then return it
}
