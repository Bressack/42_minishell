/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:52:12 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/21 20:42:15 by fredrikalindh    ###   ########.fr       */
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

void	get_prompt(void)
{
/*
** 	check either PS1 or get cwd
**	char **prompt = ret_env("PS1");
**	return (prompt[0]);
*/
	char	prompt[1000];
	int		i;
	int		last;

	getcwd(prompt, 1000);
	i = -1;
	while (prompt[++i])
		if (prompt[i] == '/')
			last = i + 1;
	ft_fprintf(1, "%s%s > %s", C_G_CYAN, &prompt[last], C_RES);
	// return ("mysh$ ");
}

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		get_prompt();
		signal(SIGINT, sig_handler);
	}
}

// void	sigq_handler(int signo)
// {
// 	if (signo == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		get_prompt();
// 		signal(SIGINT, sig_handler);
// 	}
// }

int		main(int ac, char **av, char **env)
{
	t_lexer		lex;
	// t_token		current_token;

	get_env(ac, av, env);
	while (1)
	{
		get_prompt();
		signal(SIGINT, sig_handler);
		get_next_line(0, &lex);
		if (!ft_strcmp(lex.line, "exit") || (lex.line[0] <= 0 && ft_fprintf(1, "exit\n")))
			break ;
		ac = -1;
		while (++ac < BUILTINS) // OBVOUSLY MOVE THIS ONE LATER
		{
			if (ft_strncmp(lex.line, g_builtins[ac].name, g_builtins[ac].len) == 0)
			{
				g_builtins[ac].f(lex.line + g_builtins[ac].len + 1);
				break ;
			}
		}
		if (ac == BUILTINS)
			ft_fprintf(1, "minishell: command not found: %s\n", lex.line);
/*
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
*/
		try_free_((void **)&lex.line, _FL_);
	}
	try_free_((void **)&lex.line, _FL_);
	return (0);
}
