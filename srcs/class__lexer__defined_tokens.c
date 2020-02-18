/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer__defined_tokens.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:55:50 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/18 00:59:53 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token				lexer__get_defined_token(t_token_type type)
{
	int				i;

	i = 0;
	while (g_defined_tokens[i].type != NONE && g_defined_tokens[i].type != type)
		i++;
	return (g_defined_tokens[i]);
}

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

t_token				lexer__search_defined_token(t_lexer *lex)
{
	int				i;
	int				token_idx;

	if (i = lexer__isdefined_token == -1)
		return (lexer__get_word_token(lex));
	// return (lexer__get_defined_token(ERR));
	i = -1;
	while (++i < g_defined_tokens[token_idx].len)
		lexer__advance(lex, 1);
	return (g_defined_tokens[token_idx]); // if the while statement has found a corresponding token in the table, then return it
}
