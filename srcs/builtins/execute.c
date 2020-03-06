/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:59:11 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/06 17:38:51 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

typedef enum		e_biidx
{
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXIT,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV
}					t_biidx;

t_bi		g_builtins[BUILTINS] =
{
	{"echo", &xecho},
	{"cd", &xcd},
	{"pwd", &xpwd},
	{"exit", &xexit},
	{"export", &export},
	{"unset", &unset},
	{"env", &print_env}
};

/*
** PUTS THE ENVIRONMENT VARS IN A CHAR ARRAR TO PASS ON TO FUNCTIONS.
*/
char	**env_to_arr(t_env *trav)
{
	int		size;
	char	**env;

	size = 0;
	while (trav && ++size != -1)
		trav = trav->next;
	if (!(env = (char **)mmalloc(sizeof(char *) * (size + 2))))
		return (NULL);
	trav = g_env;
	size = 0;
	while (trav)
	{
		if (trav->export && (env[size] =
		(char *)mmalloc(ft_strlen(trav->name) + ft_strlen(trav->value) + 1)))
			env[size++] =
			cat_value(cat_value(ft_strdup(trav->name), "="), trav->value);
		trav = trav->next;
	}
	env[size] = NULL;
	return (env);
}

void	sig_exec(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
	}
	if (signo == SIGQUIT)
	{
		ft_dprintf(2, "Quit: 3\n");
		// exit (3);
	}
}

int		launch(t_node *cmd, char **av)
{
	pid_t	pid;
	pid_t	wpid;
	int		sloc;
	char	*path;
	char	**environ;

	environ = env_to_arr(g_env);
	if (!(path = get_path(av[0], &sloc)))
	{
		mfree(environ);
		return (bi_error(av[0], NULL, NULL, sloc));
	}
	if ((pid = fork()) < 0)
		bi_error(av[0], NULL, strerror(errno), 0); // return ?
	signal(SIGINT, sig_exec);
	signal(SIGQUIT, sig_exec);
	if (pid == 0) //child
	{
		if (cmd->stdout != STDOUT)
		{
			dup2(cmd->stdout, STDOUT);
			close(cmd->stdout);
		}
		if (cmd->stdin != STDIN)
		{
			dup2(cmd->stdin, STDIN);
			close(cmd->stdin);
		}
		execve(path, av, environ);
		mfree(path);
		exit(errno); // errno ?
	}
	wpid = waitpid(pid, &sloc, WUNTRACED);
	mfree(environ);
	mfree(path);
	return (WEXITSTATUS(sloc));
}

/*
** CHECK COMMAND:
** IF ASSIGNMENTS (ALL) ---> SETS TYPE TO -1,  (NOT ALL) ---> SKIPS AND FREES THE ONES IN BEGINNING
** ELSE IF BUILTINS ---> SETS TYPE TO THE CORRESPONDING NUMBER IN ARRAY OF BUILTINS
** ELSE (COMMAND) ---> SETS TYPE TO -2
*/
char	**check_cmd(t_node *cmd, int *ac, int *type)
{
	int		i;
	int		j;
	int		assign;
	char	**av;

	*ac = expand(&cmd->av);
	av = convert_to_arr(cmd->av, *ac);
	j = -1;
	assign = 0;
	while (++j < *ac && assign == j && (i = -1) == -1)
	{
		if (is_valid_variable(av[j], 1))
			while (av[j][++i])
				if (av[j][i] == '=' && ++assign)
					break ;
	}
	if (assign == *ac && (*type = -1))
		return (av);
	j = -1;
	while (++j < assign) // else freee ?
		free(av[j]);
	ac -= assign;
	j = -1;
	while (++j < BUILTINS)
		if (!ft_strcmp(av[assign], g_builtins[j].name) && (*type = j) > -1)
			return (&av[assign]);
	*type = -2;
	return (&av[assign]);
}

int		execute_simple(t_node *cmd) // EXECUTION OF SIMPLE COMMAND, MEANING --NO-- FORK FOR ASSIGNMENTS && BUILTINS
{
	char	**av;
	int		ac;
	int		type;

	av = check_cmd(cmd, &ac, &type);
	if (type >= 0)
		return (g_builtins[type].f(ac, av, cmd->stdout));
	else if (type == -1)
		return (export(ac, av, 1));
	return (launch(cmd, av));
}

int		execute_nofork(t_node *cmd) //USED IF FORKING IS DONE IN PIPE FUNCTION
{
	char	**av;
	int		ac;
	int		type;
	char	*path;
	int		sig;
	char	**environ;

	av = check_cmd(cmd, &ac, &type);
	environ = env_to_arr(g_env);
	if (type >= 0)
		return (g_builtins[type].f(ac, av, cmd->stdout));
	else if (type == -1)
		return (export(ac, av, 1));
	else
	{
		if (!(path = get_path(av[0], &sig)))
			return (bi_error(av[0], NULL, NULL, sig));
		execve(path, av, environ);
		bi_error(av[0], NULL, strerror(errno), 0);
		exit(errno);
	}
}

int		execute_fork(t_node *cmd) //USED IF FORKING IS ---NOT--- DONE IN PIPE FUNCTION
{
	char	**av;
	int		ac;
	int		type;
	char	*path;
	int		pid;
	int		ret;
	char	**environ;

	if ((pid = fork()) < 0)
		return (bi_error("fork", NULL, "failed", 0));
	av = check_cmd(cmd, &ac, &type);
	signal(SIGINT, sig_exec);
	signal(SIGQUIT, sig_exec);
	if (pid == 0)
	{
		if (type >= 0)
			ret = g_builtins[type].f(ac, av, cmd->stdout);
		else if (type == 127)
			ret = export(ac, av, 1);
		else
		{
			if (cmd->stdout != STDOUT)
			{
				dup2(cmd->stdout, STDOUT);
				close(cmd->stdout);
			}
			if (cmd->stdin != STDIN)
			{
				dup2(cmd->stdin, STDIN);
				close(cmd->stdin);
			}
			if (!(path = get_path(av[0], &type)))
				exit (bi_error(av[0], NULL, NULL, type));
			environ = env_to_arr(g_env);
			execve(path, av, environ);
			mfree(environ);
			bi_error(av[0], NULL, strerror(errno), 0);
			exit(errno);
		}
		exit(127);
	}
	cmd->pid = pid;
	if (type == BI_EXIT && !node__parent_ispipe(cmd->parent))
		exit(g_exit);
	// waitpid(pid, &type, WUNTRACED);
	return (WEXITSTATUS(type));
}

/*
** int		execute_pipe(t_node *node) //EXAMPLE PSUEDO FOR PIPE FUNCTION W FORK
** {
** 	int		pipefd[2];
** 	pid_t	p[2];
** 	// char	**environ;
** 	char	*path[2];
** 	int		ret;
**
** 	signal(SIGINT, sig_exec);
** 	signal(SIGQUIT, sig_exec);
** 	// environ = env_to_arr(g_env);
** 	if (pipe(pipefd) < 0)
** 		return (bi_error("pipe", NULL, "failed", 0));
** 	if ((p[0] = fork()) < 0)
** 		return (bi_error("fork", NULL, "failed", 0));
** 	if (path[0] && p[0] == 0)
** 	{
** 		close(pipefd[0]);
** 		dup2(pipefd[1], 1);
** 		close(pipefd[1]);
** 		ret = execute_next_node(node->left);
** 		exit (ret);
** 	}
** 	if ((p[1] = fork()) < 0)
** 		return (bi_error("fork", NULL, "failed", 0));
** 	if (path[1] && p[1] == 0)
** 	{
** 		close(pipefd[1]);
** 		dup2(pipefd[0], 0);
** 		close(pipefd[0]);
** 		ret = execute_nofork(node->right);
** 		exit (ret);
** 	}
** 	wait();
** 	wait();
** 	mfree(environ);
** 	mfree(path[0]);
** 	mfree(path[1]);
** 	return (WEXITSTATUS(p[1]));
** }
*/
