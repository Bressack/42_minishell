/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:59:23 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/14 17:57:37 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <class__lexer.h>

t_lexer				lexer__init(char *line)
{
	t_lexer			lex;

	lex.line = line; // not a copy (if line is freed, lex.line will be freed too)
	lex.len_line = ft_strlen(line);
	lex.pos = 0;
	lex.current_char = lex.line[lex.pos];
	return (lex);
}

void				lexer__error(t_lexer *lex)
{
	printf("Invalid character \'%c\' (%#x)\n",
		lex->current_char, lex->current_char);
}

int					lexer__advance(t_lexer *lex)
{
	lex->pos += 1;
	if (lex->pos > lex->len_line - 1)
		lex->current_char = CHR_EOT;
	else
		lex->current_char = lex->line[lex->pos];
	return (1);
}

void				lexer__skip_whitespace(t_lexer *lex)
{
	while (lex->current_char != CHR_EOT)
		lexer__advance(lex);
}

t_token				lexer__get_next_token(t_lexer *lex)
{

}

lsa -l | cat -e || echo | "salut"
