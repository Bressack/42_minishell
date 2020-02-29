/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:52:12 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/29 15:39:36 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_prompt(int sloc, int prompt_lever)
{
	char	prompt[1024];
	int		i;
	int		last;

	if (prompt_lever == PROMPT_CASUAL)
	{
		getcwd(prompt, 1024);
		i = -1;
		while (prompt[++i])
			if (prompt[i] == '/')
				last = i + 1;
		ft_dprintf(1, "%s➜  %s%s > %s", !sloc ? C_G_GREEN : C_G_RED, C_G_CYAN, &prompt[last], C_RES);
	}
	else if (prompt_lever == PROMPT_SQUOTE)
		ft_dprintf(1, "%s➜  %s\n", !sloc ? C_G_GREEN : C_G_RED, PROMPT_SQUOTE_STR);
	else if (prompt_lever == PROMPT_DQUOTE)
		ft_dprintf(1, "%s➜  %s\n", !sloc ? C_G_GREEN : C_G_RED, PROMPT_DQUOTE_STR);
	else if (prompt_lever == PROMPT_BSLASH)
		ft_dprintf(1, "%s➜  %s\n", !sloc ? C_G_GREEN : C_G_RED, PROMPT_BSLASH_STR);
	else
		print_prompt(sloc, PROMPT_CASUAL);
}

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		print_prompt(0, PROMPT_CASUAL);
		// signal(SIGINT, sig_handler);
	}
	if (signo == SIGQUIT)
		ft_dprintf(0, "\b\b  \b\b");
}

int		main(int ac, char **av, char **env)
{
	t_lexer		lex;
	t_token		*current_token;
	int			sloc;
	// t_ast		ast;
	t_token		*args;
	t_token		*trav;
	t_token		*prev;

	g_all_malloc = NULL;
	bzero(&lex, sizeof(t_lexer));
	get_env(ac, av, env);
	// printf("echo $HOME \"je \'suis\' un \\\" chat\"$OK$SALUT\\$HOME\n");
	sloc = 0;
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		lexer__refill_line(&lex, sloc, PROMPT_CASUAL);
		if (lex.line[0] < 0 && ft_dprintf(1, "exit\n") && !free_all_malloc()) // CALL XEXIT INSTEAD ?
			break ;
		// ast = ast__new(lex);
		args = NULL;
		while (1)
		{
			current_token = lexer__get_next_token(&lex);
			// token__print(current_token);
			if (current_token->type == ERR)
			{
				lexer__error(1, &lex);
				break ;
			}
			if (token__istype(current_token, EOT | NONE) && !(trav->next = NULL))
				break ;
			trav = (t_token *)mmalloc(sizeof(t_token));
			if (args == NULL)
				args = trav;
			else
				prev->next = trav;
			prev = trav;
			trav->value = ft_strdup(current_token->value);
			// token__del(current_token);
			// ast__add_node(&ast, current_token);

		}
		execute(args);
		try_free_((void **)&lex.line, _FL_);
	}
	try_free_((void **)&lex.line, _FL_);
	// print_mem__(PRINT_ERR);
	try_free_all(_FL_);
	return (0);
}
