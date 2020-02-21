/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:52:12 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/21 01:51:50 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** int		main(void)
** {
** 	char			*line;
** 	int				res;
** 	t_lexer			lex;
** 	t_token			current_token;
**
** 	while (1)
** 	{
** 		dprintf(1, ">: ");
** 		res = get_next_line(1, &line); // why
** 		if (!strcmp(line, "exit"))
** 			break ;
** 		lex = lexer__new(line);
** 		while (1)
** 		{
** 			current_token = lexer__get_next_token(&lex);
** 			if (current_token.type == ERR)
** 				lexer__error(&lex);
** 			token__print(current_token);
** 			token__del(current_token);
** 			if (current_token.type == EOT || current_token.type == ERR || current_token.type == NONE)
** 				break ;
** 		}
** 		try_free_((void **)&line, _FL_);
** 	}
** 	try_free_((void **)&line, _FL_);
** 	return (0);
** }
*/

/*
** MAIN: purpose: one loop to keep program running, signal handling calling
** to get command, lexer, parser, execution and freeing.
*/

char	*get_prompt(void)
{
/*
** 	check either PS1 or get cwd
*/

	return ("mysh$ ");
}

int		main(int ac, char **av, char **env)
{
	t_lexer		lex;
	t_token		current_token;

	get_env(ac, av, env); // void inside...
	while (1)
	{
		ft_fprintf(1, "%s", get_prompt());
		get_next_line(0, &lex);
		if (!strcmp(lex.line, "exit"))
			break ;
		while (1)
		{
			current_token = lexer__get_next_token(&lex);
			if (current_token.type == ERR)
				lexer__error(&lex);
			token__print(current_token);
			token__del(current_token);
			if (current_token.type == EOT || current_token.type == ERR || current_token.type == NONE)
				break ;
		}
		try_free_((void **)&lex.line, _FL_);
	}
	try_free_((void **)&lex.line, _FL_);
	return (0);
}
