/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer__refill_line.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 04:33:20 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/11 20:52:00 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** **************************************************************************
** **** set and init ********************************************************
** **************************************************************************
*/

void			lexer__set_start_pos(t_lexer *lex, int new_pos)
{
	lex->start = new_pos;
	lex->start_char = lex->line[new_pos];
}

/*
** **************************************************************************
** **** body functions ******************************************************
** **************************************************************************
*/

int				lexer__refill_line(t_lexer *lex, int sloc)
{
	mfree((void **)&lex->line);
	print_prompt(sloc);
	if (get_next_line(STDIN, &lex->line) == -1 || !lex->line)
		return (lexer__error(ERR_GNL, lex));
	if (g_sigint == 1)
	{
		g_sigint = 0;
		mfree((void **)&lex->line);
		if (get_next_line(STDIN, &lex->line) == -1 || !lex->line)
			return (lexer__error(ERR_GNL, lex));
	}
	lex->pos = 0;
	lex->start = 0;
	lex->len_line = ft_strlen(lex->line);
	lex->current_char = lex->line[lex->pos];
	lex->start_char = lex->line[lex->start];
	return (SUCCESS);
}

/*
** just return the word token just found in lexer__get_next_token. The token
** start at 'start_pos' included until 'pos' excluded (variable included in lex)
*/
t_token			*lexer__token_grabber(t_lexer *lex, t_token_type_m type)
{
	t_token		*new;

	new = token__new(type, ft_strsub(lex->line, lex->start, lex->pos - lex->start),
		lex->start);
	return (new);
}
