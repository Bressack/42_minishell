/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:59:11 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/02 16:03:49 by tharchen         ###   ########.fr       */
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
** char	*get_next_path(char **env, char *path, char *command)
** {
** 	int		i;
**
** 	// i = -1;
** 	// while (path[++i])
** 	// 	if (path[i] == '/' && !(env = NULL))
** 	// 		return (path);
** 	i = 0;
** 	while (**env && **env != '\n' && **env != ':')
** 		path[i++] = *((*env)++);
** 	if (**env == ':')
** 		(*env)++;
** 	path[i++] = '/';
** 	while (command && *command)
** 		path[i++] = *command++;
** 	path[i] = '\0';
** 	return (path);
** }
*/

char	*get_next_path(char *path, char *command)
{
	int		i;
	int		p;
	static	int c = 0;
	char *env;

	i = -1;
	if (c == -1)
		return (NULL);
	while (command[++i])
		if (command[i] == '/')
			p = 1;
	if (p == 1)
	{
		if (*command == '.' && (command += 2))
			env = ret_envval("PWD");
		else
			env = NULL;
		printf("ENV: %s\n", env);
	}
	else
		env = ret_envval("PATH");
	i = 0;
	while (env && env[c] && env[c] != '\n' && env[c] != ':')
		path[i++] = env[c++];
	if (env[c] == ':')
		c++;
	if (env[c] == '\0')
		c = -1;
	path[i++] = '/';
	while (command && *command)
		path[i++] = *command++;
	path[i] = '\0';
	// printf("PATH [%s]\n", path);
	return (path);
}

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
	while (trav && size > -1)
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
		exit (3);
	}
}

int		launch(t_node *cmd, char **av)
{
	pid_t	pid;
	pid_t	wpid;
	int		sloc;
	char	path[LINE_MAX]; // BRUH // yes, use malloc, it's better.
	char	**environ;

	environ = env_to_arr(g_env);
	sloc = 0;
	pid = fork();
	signal(SIGINT, sig_exec);
	signal(SIGQUIT, sig_exec);
	if (pid == 0) //child
	{
		dup2(cmd->fd[ISTDOUT][PIPE_WRITE], cmd->stdio[ISTDOUT]);
		dup2(cmd->fd[ISTDIN][PIPE_READ], cmd->stdio[ISTDIN]);
		// close(cmd->stdio[ISTDOUT]);
		// close(cmd->stdio[ISTDIN]);
		// cmd->stdio[ISTDOUT] != ISTDOUT ? close(ISTDOUT) : 0;
		// cmd->stdio[ISTDIN] != ISTDIN ? close(ISTDIN) : 0;
		while (get_next_path(path, av[0]))
			execve(path, av, environ); // SHOULD MAYBE NOT USE MALLOC?
		bi_error(av[0], NULL, "command not found", 0);
		exit(-1);
	}
	else if (pid < 0) //error with fork
		bi_error(av[0], NULL, strerror(errno), 0);
	else //parent
		wpid = waitpid(pid, &sloc, WUNTRACED);
	mfree(environ);
	return (sloc);
}

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
	while (++j < ac && assign == j)
	{
		if (ok_envchar(av[j][0]) && ((av[j][0] < '0' || av[j][0] > '9')) && (i = -1) == -1)
			while (av[j][++i])
				if (av[j][i] == '=')
					assign++;
	}
	if (assign == ac)
		return (export(ac, av));
	ac -= assign;
	av += assign;
	j = -1;
	while (++j < BUILTINS)
		if (!ft_strcmp(av[0], g_builtins[j].name))
			return (g_builtins[j].f(ac, av));
	return (launch(cmd, av));
}
