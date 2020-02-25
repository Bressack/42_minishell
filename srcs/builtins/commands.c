/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:59:36 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/25 14:23:16 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	xecho(char *args)
{
	int n;

	n = 0;
	while (args && *args && *args == ' ')
		args++;
	if (args && *args == '$' && *args++)
		ft_dprintf(1, "%s", (ret_env(args))->value);
	else if (args && *args != '\0')
	{
		if (ft_strncmp(args, "-n", 2) == 0 && (n = 1) == 1)
			args = args + 3;
		ft_dprintf(1, "%s", args);
	}
	if (n != 1)
		ft_dprintf(1, "\n");
}

void	xpwd(char *args)
{
	(void)args;
	char	cwd[1024];

	getcwd(cwd, 1024);
	ft_dprintf(1, "%s\n", cwd);
}

void	xexit(char *args)
{
	(void)args;
	// int code;
	//
	// if (!is_digit(args))
	// 	ft_dprintf(2, "error: non-digit exit codes\n");
	// else
	// 	code = ft_atoi(args);
	// ft_dprintf(1, "exit\n");
	// exit (code);
	exit (0);
}

void	xcd(char *args)
{
	t_env	*change;
	char	*tmp;
	char	dir[500];

	while (args && *args && *args == ' ')
		args++;
	change = ret_env("OLDPWD");
	tmp = change->value;
	if (*args == '~')
		args = strcat(ft_strdup(ret_env("HOME")->value), args + 1); //OWN STRCAT without realloc
	if (args == NULL || *args == '\0')
		chdir(ret_env("HOME")->value);
	else if (*args == '-')
		chdir(change->value);
	else if (chdir(args) != 0)
	{
		ft_dprintf(2, "cd: %s: %s\n", strerror(errno), args);
		return ;
	}
	change->value = ret_env("PWD")->value; // gets previous PWD
	change = ret_env("PWD"); // in order to change the value of PWD VAR
	getcwd(dir, 500);
	change->value = ft_strdup(dir); //OWN STRDUP
	free(tmp);
}


// int		launch(char *args)
// {
// 	pid_t	pid;
// 	pid_t	wpid;
// 	int		status;
// 	char	*path;
//
// 	pid = fork();
// 	if (pid == 0) //child
// 	{
// 		signal(SIGINT, SIG_DFL);
// 		path = ret_env("PATH")->value;
// 		if (execve(ft_copsep(&path, ':'), args, environ) == -1)
// 		 	ft_dprintf(2, "%s\n", strerror(errno));
// 		exit(-1);
// 	}
// 	else if (pid < 0)
// 		strerror(errno);
// 	else
// 	{
// 		wpid = waitpid(pid, &status, WEXITED);
// 		while (!WIFEXITED(status) && !WIFSIGNALED(status)) // dooo smth, killlll here?
// 			;
// 	}
// 	return (1);
// }

// int		execute(const char **args)
// {
// 	int i;
//
// 	i = -1;
// 	while (++i < BUILTINS)
// 		if (ft_strcmp(args[0], g_builtins[i].name) == 0)
// 			return (g_builtins[i].f)(args[1]);
// 	return launch(args);
// }
