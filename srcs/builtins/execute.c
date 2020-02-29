/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:59:11 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/29 16:11:26 by fredrikalindh    ###   ########.fr       */
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

char	*get_next_path(char **env, char *path, char *command)
{
	int		i;

	// i = -1;
	// while (path[++i])
	// 	if (path[i] == '/' && !(env = NULL))
	// 		return (path);
	i = 0;
	while (**env && **env != '\n' && **env != ':')
		path[i++] = *((*env)++);
	if (**env == ':')
		(*env)++;
	path[i++] = '/';
	while (command && *command)
		path[i++] = *command++;
	path[i] = '\0';
	return (path);
}

char	**env_to_arr(t_env *trav)
{
	int		size;
	char	**env;

	size = 0;
	while (trav && ++size != -1)
		trav = trav->next;
	if (!(env = (char **)mmalloc(sizeof(char *) * size + 2)))
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
		// exit (3);
	}

}

int		launch(char **args, char *env)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char	path[LINE_MAX]; // BRUH
	char	**environ;

	environ = env_to_arr(g_env);
	pid = fork();
	signal(SIGINT, sig_exec);
	signal(SIGQUIT, sig_exec);
	if (pid == 0) //child
	{
		while (env && *env && get_next_path(&env, path, args[0]))
			execve(path, args, environ); // SHOULD MAYBE NOT USE MALLOC?
		bi_error(args[0], NULL, "command not found", 0);
		exit(-1);
	}
	else if (pid < 0) //error with fork
		bi_error(args[0], NULL, strerror(errno), 0);
	else //parent
		wpid = waitpid(pid, &status, WUNTRACED);
		// while (!WIFEXITED(status) && !WIFSIGNALED(status)) // kill here?
	mfree(environ);
	return (1);
}

int		execute(t_token *args)
{
	int		i;
	int		j;
	int		assign;
	char	**av;
	int		ac;

	ac = expand(&args);
	av = convert_to_arr(args, ac);
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
	return (launch(av, ret_envval("PATH")));
}
