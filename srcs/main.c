/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:52:12 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/11 16:57:59 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_prompt(int sloc)
{
	char	prompt[1024];
	int		i;
	int		last;

	getcwd(prompt, 1024);
	i = -1;
	while (prompt[++i])
		if (prompt[i] == '/')
			last = i + 1;
	ft_dprintf(2, "%s➜  %s%s > %s", !sloc ? C_G_GREEN : C_G_RED, C_G_CYAN,
		&prompt[last], C_RES);
}

void	sig_handler(int signo)
{
	if (signo == SIGINT && ft_dprintf(STDOUT, "\n")) // RESET LINE
		print_prompt(0);
	else if (signo == SIGQUIT)
		ft_dprintf(2, "\b\b  \b\b");
}

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
			// ast ? tree_draw(ast) : 0;
			sloc = ast_interpreter(ast);
			node__del(&ast, RECURCIVLY);
		}
	}
	free_all_malloc();
	return (0);
}
