/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 12:52:12 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/01 13:38:30 by tharchen         ###   ########.fr       */
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

int		get_deep(t_node *root, int i)
{
	int	lret;
	int	rret;

	if (root->left)
		lret = get_deep(root, i + 1);
	else
		lret = i;
	if (root->right)
		rret = get_deep(root, i + 1);
	else
		rret = i;
	return (lret > rret ? lret : rret);
}

int		main(int ac, char **av, char **env)
{
	int			sloc;
	t_node		*ast;

	get_env(ac, av, env);
	sloc = 0;
	while (1)
	{
		signal(SIGINT, sig_handler);

		// int			pid;
		// if (!(pid = fork()))
		// {
			ast = ast_builder(sloc);
			if (ast)
			{
				printf("AST RECIVED !!\n");
				tree_draw(ast);
			}
			// exit(0);
		// }
		// waitpid(pid, &sloc, WUNTRACED);
		printf("sloc == %d\n", sloc);
		if (sloc == 6)
			printf("[ SEGV  ] You got a segv lmao, you\'re so bad\n");
		// return (sloc);
	}
	try_free_all(_FL_);
	return (0);
}
