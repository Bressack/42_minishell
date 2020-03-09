/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:59:11 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/09 06:06:26 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
			env[size++] = cat_value(trav->name, '=', trav->value);
		trav = trav->next;
	}
	env[size] = NULL;
	return (env);
}

void	sig_exec(int signo)
{
	if (signo == SIGINT) // return 130 !
	{
		write(1, "\n", 1);
		g_exit = 130;
	}
	if (signo == SIGQUIT)
	{
		ft_dprintf(2, "Quit: 3\n"); // return 131 !
		g_exit = 131;
		// exit(3);
	}
}

int		launch(t_node *cmd, char **av)
{
	pid_t	pid;
	int		sloc;
	char	*path;
	char	**environ;

	if (!(path = get_path(av[0], &sloc)))
		return (bi_error(av[0], NULL, NULL, sloc));
	if ((pid = fork()) < 0 && mfree((void **)&path))
		return (bi_error(av[0], NULL, strerror(errno), 0));
	signal(SIGINT, sig_exec);
	signal(SIGQUIT, sig_exec);
	if (pid == 0)
	{
		environ = env_to_arr(g_env);
		if (cmd->stdout != STDOUT && dup2(cmd->stdout, STDOUT) != -1)
			close(cmd->stdout);
		if (cmd->stdin != STDIN && dup2(cmd->stdin, STDIN) != -1)
			close(cmd->stdin);
		execve(path, av, environ);
		free_all_malloc();
		exit(errno); // errno ?
	}
	mfree((void **)&path);
	waitpid(pid, &sloc, WUNTRACED);
	return (WEXITSTATUS(sloc));
}

/*
** CHECK COMMAND:
** IF ASSIGNMENTS (ALL) ---> SETS TYPE TO -1,
** (NOT ALL) ---> SKIPS AND FREES THE ONES IN BEGINNING
** ELSE IF BUILTINS ---> SETS TYPE TO THE CORRESPONDING NUMBER IN ARRAY OF BIs
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
	*ac -= assign;
	while ((j = -1) < 0 && assign-- > 0)
		mfree((void **)av++); //not sure about these
	while (++j < BUILTINS && (*type = -2) < 0)
		if (!ft_strcmp(av[0], g_builtins[j].name) && (*type = j) > -1)
			return (av);
	return (av);
}

/*
** EXECUTION OF SIMPLE COMMAND, MEANING --NO-- FORK FOR ASSIGNMENTS && BUILTINS
** IS TO BE USED FOR WHEN THERE ARE NO PIPES. MEANING BUILTINS AND ASSIGNMENTS
** WILL BE DONE IN CURRENT PROCESS AND THEREFORE CHANGE CURRENT ENVIRONMENT.
*/

int		execute_simple(t_node *cmd)
{
	char	**av;
	int		ac;
	int		type;

	av = check_cmd(cmd, &ac, &type);
	if (type >= 0)
		type = g_builtins[type].f(ac, av, cmd->stdout);
	else if (type == -1)
		type = export(ac, av, 1);
	else
		type = launch(cmd, av);
	while (av && *av)
		mfree((void **)av++); //not sure about these
	mfree((void **)&av);
	return (type);
}

/*
** USED IF FORKING IS DONE IN PIPE FUNCTION. SO THIS JUST EXECUTES BUILTINS,
** ASSIGNMENTS OR COMMANDS IN SPECIFIC PATH OR WILL PATH ENVIRONMENT VAR
*/

/*
** int		execute_nofork(t_node *cmd)
** {
** 	char	**av;
** 	int		ac;
** 	int		type;
** 	char	*path;
** 	int		sig;
** 	char	**environ;
**
** 	av = check_cmd(cmd, &ac, &type);
** 	environ = env_to_arr(g_env);
** 	if (type == 3)
** 		exit (g_builtins[type].f(ac, av, -1));
** 	else if (type >= 0)
** 		exit (g_builtins[type].f(ac, av, cmd->stdout));
** 	else if (type == -1)
** 		exit (export(ac, av, 1));
** 	else
** 	{
** 		if (!(path = get_path(av[0], &sig)))
** 			return (bi_error(av[0], NULL, NULL, sig));
** 		execve(path, av, environ);
** 		bi_error(av[0], NULL, strerror(errno), 0);
** 		exit(errno);
** 	}
** }
*/

/*
** USED IF FORKING IS ---NOT--- DONE IN PIPE FUNCTION. MEANING IT FORKS IN
**< HEREEE
*/

int		execute_in_child(t_node *cmd)
{
	char	**av;
	int		ac;
	int		type;
	char	*path;
	char	**environ;

	av = check_cmd(cmd, &ac, &type);
	if (!av || !*av || type == 3)
		return (0);
	else if (type >= 0)
		return (g_builtins[type].f(ac, av, cmd->stdout));
	else if (type == -1)
		return (export(ac, av, 1));
	if (cmd->stdout != STDOUT && dup2(cmd->stdout, STDOUT) != -1)
		close(cmd->stdout);
	if (cmd->stdin != STDIN && dup2(cmd->stdin, STDIN) != -1)
		close(cmd->stdin);
	if (!(path = get_path(av[0], &type)))
		return (bi_error(av[0], NULL, NULL, type));
	environ = env_to_arr(g_env);
	execve(path, av, environ);
	bi_error(av[0], NULL, strerror(errno), 0);
	return (errno);
}

int		execute_fork(t_node *cmd)
{
	int		pid;
	int		ret;

	if ((pid = fork()) < 0)
		return (bi_error("fork", NULL, "failed", 0));
	signal(SIGINT, sig_exec);
	signal(SIGQUIT, sig_exec);
	if (pid == 0)
	{
		ret = execute_in_child(cmd);
		free_all_malloc();
		exit(ret);
	}
	cmd->pid = pid;
	if (node__parent_ispipe(cmd))
		waitallpipes(pid, ADD);
	return (0);
}
/*
** int		execute_fork(t_node *cmd)
** {
** 	char	**av;
** 	int		ac;
** 	int		type;
** 	char	*path;
** 	int		pid;
** 	int		ret;
** 	char	**environ;
**
** 	if ((pid = fork()) < 0)
** 		return (bi_error("fork", NULL, "failed", 0));
** 	signal(SIGINT, sig_exec);
** 	signal(SIGQUIT, sig_exec);
** 	if (pid == 0)
** 	{
** 		av = check_cmd(cmd, &ac, &type);
** 		if (!av || !*av || type == 3)
** 			ret = 0;
** 		else if (type >= 0)
** 			ret = g_builtins[type].f(ac, av, cmd->stdout);
** 		else if (type == -1)
** 			ret = export(ac, av, 1);
** 		else
** 		{
** 			if (cmd->stdout != STDOUT)
** 			{
** 				dup2(cmd->stdout, STDOUT);
** 				close(cmd->stdout);
** 			}
** 			if (cmd->stdin != STDIN)
** 			{
** 				dup2(cmd->stdin, STDIN);
** 				close(cmd->stdin);
** 			}
** 			if (!(path = get_path(av[0], &type)))
** 				ret = bi_error(av[0], NULL, NULL, type);
** 			else
** 			{
** 				environ = env_to_arr(g_env);
** 				execve(path, av, environ);
** 				bi_error(av[0], NULL, strerror(errno), 0);
** 				ret = errno;
** 			}
** 		}
** 		free_all_malloc();
** 		exit(ret);
** 	}
** 	cmd->pid = pid;
** 	waitallpipes(pid, ADD);
** 	return (0);
** }
*/

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
** 		exit(ret);
** 	}
** 	if ((p[1] = fork()) < 0)
** 		return (bi_error("fork", NULL, "failed", 0));
** 	if (path[1] && p[1] == 0)
** 	{
** 		close(pipefd[1]);
** 		dup2(pipefd[0], 0);
** 		close(pipefd[0]);
** 		ret = execute_nofork(node->right);
** 		exit(ret);
** 	}
** 	wait();
** 	wait();
** 	mfree((void **)&environ);
** 	mfree((void **)&path[0]);
** 	mfree((void **)&path[1]);
** 	return (WEXITSTATUS(p[1]));
** }
*/
