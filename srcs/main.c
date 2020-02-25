/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:52:12 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/25 14:02:05 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bi		g_builtins[BUILTINS] =
{
	{"echo", 4, &xecho},
	{"cd", 2, &xcd},
	{"pwd", 3, &xpwd},
	{"exit", 4, &xexit}, // or just immidiately?
	{"export", 6, &export},
	{"unset", 5, &unset},
	{"env", 3, &print_env}
};

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
		signal(SIGINT, sig_handler);
	}
}

// void	sigq_handler(int signo)
// {
// 	if (signo == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		print_prompt(PROMPT_CASUAL);
// 		signal(SIGINT, sig_handler);
// 	}
// }

int		main(int ac, char **av, char **env)
{
	t_lexer		lex;
	t_token		current_token;
	int			sloc;
	int			pid;
	// t_ast		ast;

	bzero(&lex, sizeof(t_lexer));
	get_env(ac, av, env);
	printf("echo $HOME \"je \'suis\' un \\\" chat\"$OK$SALUT\\$HOME\n");
	sloc = 0;
	while (1)
	{
		signal(SIGINT, sig_handler);
		lexer__refill_line(&lex, sloc, PROMPT_CASUAL);
		if (!ft_strcmp(lex.line, "exit") || (lex.line[0] < 0 && ft_dprintf(1, "exit\n")))
			break ;
		// ast = ast__new(lex);
		if (!(pid = fork()))
		{
			while (1)
			{
				current_token = lexer__get_next_token(&lex);
				token__print(current_token);
				// getchar();
				if (current_token.type == ERR)
				{
					lexer__error(1, &lex);
					break ;
				}
				if (token__istype(current_token, EOT | NONE))
					break ;
				token__del(current_token);
				// ast__add_node(&ast, current_token);
			}
			exit(0);
		}
		waitpid(pid, &sloc, WUNTRACED);
		try_free_((void **)&lex.line, _FL_);
	}
	try_free_((void **)&lex.line, _FL_);
	// print_mem__(PRINT_ERR);
	try_free_all(_FL_);
	return (0);
}
