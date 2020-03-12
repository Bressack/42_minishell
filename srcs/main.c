/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:52:12 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/12 12:52:58 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		g_sigint = 0;

void	print_prompt(int sloc)
{
	char	prompt[LINE_MAX];
	int		i;
	int		last;

	// (void)sloc;
	// printf("sloc %d\n", sloc);
	(!g_exit && sloc) ? g_exit = sloc : 0;
	getcwd(prompt, LINE_MAX);
	i = -1;
	while (prompt[++i])
		if (prompt[i] == '/')
			last = i + 1;
	ft_dprintf(2, "%s➜  %s%s > %s", !g_exit ? C_G_GREEN : C_G_RED, C_G_CYAN,
		&prompt[last], C_RES);
}

void	sig_handler(int signo)
{
	if (signo == SIGINT && ft_dprintf(STDOUT, "\n"))
	{
		g_reset = 1;
		g_exit = 130;
		print_prompt(0);
	}
	else if (signo == SIGQUIT)
		ft_dprintf(2, "\b\b  \b\b");
}

int		main(int ac, char **av, char **env)
{
	int			sloc;
	t_node		*ast;

	get_env(ac, av, env);
	ft_bzero(&g_pids, sizeof(int) * 500);
	sloc = 0;
	g_exit = 0;
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		if ((ast = ast_builder(sloc)))
		{
			// ast ? tree_draw(ast) : 0;
			sloc = ast_interpreter(ast);
			node__del(&ast, RECURCIVLY);
		}
		else
			g_exit = 2;
	}
	free_all_malloc();
	return (0);
}
