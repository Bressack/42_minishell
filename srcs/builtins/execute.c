/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:59:11 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/05 11:47:21 by fredrikalindh    ###   ########.fr       */
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
		// if (sloc == 125 && printf("%s\n", path))
		// 	return (chdir(path));
		return (bi_error(av[0], NULL, NULL, sloc));
	}
	pid = fork();
	signal(SIGINT, sig_exec);
	signal(SIGQUIT, sig_exec);
	if (pid == 0) //child
	{
		dup2(cmd->stdout, STDOUT);
		dup2(cmd->stdin, STDIN);
		execve(path, av, environ);
		bi_error(av[0], NULL, strerror(errno), 0);
		exit(errno); // errno ?
	}
	else if (pid < 0) //error with fork
		bi_error(av[0], NULL, strerror(errno), 0);
	else //parent
		wpid = waitpid(pid, &sloc, WUNTRACED);
	mfree(environ);
	mfree(path);
	return (WEXITSTATUS(sloc));
}

/*
** EXECUTE FIRST CALLS EXPAND FUNCTION AND THEN CONVERTS THE EXPANDED ARG LIST
** TO CHAR ARRAY. AFTER THAT IT CHECKS IF ALL ARGS ARE ASSIGNMENTS IF SO IT
** CALLS EXPORT. IF NOT IT SKIPS POSSIBLE FIRST ASSIGNMENTS AND CHECKS IF FIRST
** NON-ASS IS A BUILT-IN, OTHERWISE IT TRIES TO LAUNCH IT.
*/

int		execute(t_node *cmd)
{
	int		i;
	int		j;
	int		assign;
	char	**av;
	int		ac;

	ac = expand(&cmd->av);
	av = convert_to_arr(cmd->av, ac);
	j = -1;
	assign = 0;
	while (++j < ac && assign == j && (i = -1) == -1)
	{
		if (is_valid_variable(av[j], 1))
			while (av[j][++i])
				if (av[j][i] == '=' && ++assign)
					break ;
	}
	if (assign == ac)
		return (export(ac, av, 1));
	ac -= assign;
	j = -1;
	while (++j < BUILTINS)
		if (!ft_strcmp(av[assign], g_builtins[j].name))
			return (g_builtins[j].f(ac, &av[assign], cmd->stdout));
	return (launch(cmd, &av[assign]));
}

int		execute_pipe(char **a1, char **a2)
{
	int		pipefd[2];
	pid_t	p[2];
	char	**environ;
	char	*path[2];

	environ = env_to_arr(g_env);
	if (pipe(pipefd) < 0)
		return (bi_error("pipe", NULL, "failed", 0));
	if (!(path[0] = get_path(a1[0], &p[0])))
		bi_error(a1[0], NULL, NULL, p[0]);
	else if ((p[0] = fork()) < 0)
		return (bi_error("fork", NULL, "failed", 0));
	if (path[0] && p[0] == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		execve(path, a1, environ);
		bi_error(a1[0], NULL, strerror(errno), 0);
		exit(errno);
	}
	if (!(path[1] = get_path(a2[0], &p[1])))
		bi_error(a1[0], NULL, NULL, p[1]);
	else if ((p[1] = fork()) < 0)
		return (bi_error("fork", NULL, "failed", 0));
	if (path[1] && p[1] == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		execve(path, a2, environ);
		bi_error(a2[0], NULL, strerror(errno), 0);
		exit(errno);
	}
	wait();
	wait();
	mfree(environ);
	mfree(path[0]);
	mfree(path[1]);
	return (WEXITSTATUS(p[1]));
}
