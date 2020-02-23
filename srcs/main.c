/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:52:12 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/23 14:44:41 by tharchen         ###   ########.fr       */
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

void	print_prompt(int prompt_lever)
{
/*
** 	check either PS1 or get cwd
**	char **prompt = ret_env("PS1");
**	return (prompt[0]);
*/
	char	prompt[1000];
	int		i;
	int		last;

	if (prompt_lever == PROMPT_CASUAL)
	{
		getcwd(prompt, 1000);
		i = -1;
		while (prompt[++i])
			if (prompt[i] == '/')
				last = i + 1;
		ft_dprintf(1, "%s%s > %s", C_G_CYAN, &prompt[last], C_RES);
	}
	else if (prompt_lever == PROMPT_SQUOTE)
		ft_dprintf(1, "%s\n", PROMPT_SQUOTE_STR);
	else if (prompt_lever == PROMPT_DQUOTE)
		ft_dprintf(1, "%s\n", PROMPT_DQUOTE_STR);
	else if (prompt_lever == PROMPT_BSLASH)
		ft_dprintf(1, "%s\n", PROMPT_BSLASH_STR);
	else
		print_prompt(PROMPT_CASUAL);
}

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		print_prompt(PROMPT_CASUAL);
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
	t_ast		ast;

	bzero(&lex, sizeof(t_lexer));
	get_env(ac, av, env);
	while (1)
	{
		signal(SIGINT, sig_handler);
		lexer__refill_line(&lex, 0, PROMPT_CASUAL);
		if (!ft_strcmp(lex.line, "exit") || (lex.line[0] <= 0 && ft_dprintf(1, "exit\n")))
			break ;
		// ac = -1;
		// while (++ac < BUILTINS) // OBVOUSLY MOVE THIS ONE LATER // YES OBVOUSLY WE SHALL
		// {
		// 	if (ft_strncmp(lex.line, g_builtins[ac].name, g_builtins[ac].len) == 0)
		// 	{
		// 		g_builtins[ac].f(lex.line + g_builtins[ac].len + 1);
		// 		break ;
		// 	}
		// }
		// if (ac == BUILTINS)
		// 	ft_dprintf(1, "minishell: command not found: %s\n", lex.line);

		ast = ast__new();
		while (1)
		{
			current_token = lexer__get_next_token(&lex);
			if (token__istype(current_token, ERR)
				lexer__error(&lex);
			if (token__istype(current_token, EOT | NONE))
				break ;
			token__print(current_token);
			ast__add_node(&ast, current_token);
		}

		try_free_((void **)&lex.line, _FL_);
	}
	try_free_((void **)&lex.line, _FL_);
	try_free_all(_FL_);
	print_mem__(PRINT_KO);
	return (0);
}
