/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer__defined_tokens.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:55:50 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/20 11:32:05 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** return: t_token
** lexer__get_defined_token_with_index()
** parameter: int index, an index of the global array g_defined_tokens
**
** value must be in range 0 to NB_DEFINED_TOKEN
** return the defined token NONE else
*/
t_token				lexer__get_defined_token_with_index(int index)
{
	if (index >= 0 && index < NB_DEFINED_TOKEN)
		return (g_defined_tokens[index]);
	return (g_defined_tokens[NONE]);
}

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
	t_token			tmp;
	int				i;
	int				j;
	int				match;

	match = -1;	// i save
	j = -1;	// j save
	i = 0;
	tmp = lexer__get_defined_token_with_index(i);
	while (tmp.type != NONE) // until the end of the array
	{
		if (tmp.len > 0)
		{
			j = 0;
			while (tmp.value[j] && tmp.value[j] ==
				lex->line[lex->start + j]) // compare the two string until the end of tmp.value
				j++;
			if (j == tmp.len)
				match = i;
		}
		tmp = lexer__get_defined_token_with_index(++i);
	}
	if (match == -1)
		lexer__advance(lex, 1);
	return (match);
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
** ex: line & echo
**          ^
** there, '&' is not in the global array g_defined_tokens, so the lexer will
** read it as a word character.
**
** if no match, current_char is taken as a word and lexer__search_defined_token
** call lexer__get_word_token to found a word token who start by this char
*/

t_token				lexer__search_defined_token(t_lexer *lex)
{
	t_token			ret;
	int				token_idx;

	if (!lexer__istype(lex->current_char,
		CHR_ERR|CHR_EOT|CHR_SPACE|CHR_PASS|CHR_WORD|CHR_SQUOTE|CHR_DQUOTE) &&
		(token_idx = lexer__isdefined_token(lex)) != -1)
	{
		ret = lexer__get_defined_token_with_index(token_idx);
		lexer__advance(lex, ret.len);
	}
	else
		ret = lexer__get_word_token(lex);
	return (ret);
}
