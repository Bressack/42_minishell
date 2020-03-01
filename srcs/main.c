/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:52:12 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/01 16:27:32 by tharchen         ###   ########.fr       */
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
		;
	else if (signo == SIGQUIT)
		ft_dprintf(0, "\b\b  \b\b"); // tellement laid lmao
}

int		main(int ac, char **av, char **env)
{
	int			sloc;
	t_node		*ast;
	pid_t		pid;

	get_env(ac, av, env);
	while (1)
	{
		if (signal(SIGINT, sig_handler) == CONTINUE)
			continue ;
		signal(SIGQUIT, sig_handler);
		if (!(pid = fork()))
		{
			if ((ast = ast_builder(sloc)))
				ast ? tree_draw(ast) : 0; // gen a tree.dot file used by the cmd dot in the shell
			del_node(&ast, RECURCIVLY);
			exit(0);
		}
		waitpid(pid, &sloc, WUNTRACED);
	}
	try_free_all(_FL_);
	free_all_malloc();
	return (0);
}
