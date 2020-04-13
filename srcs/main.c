/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:52:12 by tharchen          #+#    #+#             */
/*   Updated: 2020/04/13 14:08:26 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_prompt(int sloc)
{
	char	prompt[LINE_MAX];
	int		i;
	int		last;

	(!g_exit && sloc) ? g_exit = sloc : 0;
	if (!getcwd(prompt, LINE_MAX))
	{
		ft_dprintf(2, "%s➜  %sminishell > %s", !g_exit ? C_G_GREEN : C_G_RED,
			C_G_CYAN, C_RES);
		return ;
	}
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

#if BONUS == 1

int		main(int ac, char **av, char **env)
{
	int			sloc;
	t_node		*ast;

	get_env(ac, av, env);
	sloc = 0;
	g_exit = 0;
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		if ((ast = ast_builder(sloc)))
		{
			tree_draw(ast);
			sloc = ast_interpreter(ast);
			g_exit = sloc;
			node__del(&ast, RECURCIVLY);
		}
		else
			g_exit = 2;
	}
	free_all_malloc();
	return (0);
}

#else

int		main(int ac, char **av, char **env)
{
	int			sloc;
	t_node		*ast;

	get_env(ac, av, env);
	sloc = 0;
	g_exit = 0;
	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		if ((ast = ast_builder(sloc)))
		{
			sloc = ast_interpreter(ast);
			g_exit = sloc;
			node__del(&ast, RECURCIVLY);
		}
		else
			g_exit = 2;
	}
	free_all_malloc();
	return (0);
}

#endif
