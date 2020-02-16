/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:52:12 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/16 09:32:36 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		main(void)
{
	char			*line;
	int				res;
	t_lexer			lex;
	t_token			current_token;

	while (1)
	{
		dprintf(1, ">: ");
		res = get_next_line(1, &line);
		if (!strcmp(line, "exit"))
			break ;
		lex = lexer__new(line);
		while (1)
		{
			current_token = lexer__get_next_token(&lex);
			token__print(current_token);
			token__del(current_token);
			if (current_token.type == EOT || current_token.type == ERR || current_token.type == NONE)
				break ;
		}
		try_free_((void **)&line, _FL_);
	}
	try_free_((void **)&line, _FL_);
	return (0);
}
