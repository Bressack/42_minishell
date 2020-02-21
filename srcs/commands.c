/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:59:36 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/21 19:41:15 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	xecho(char *args)
{
	int n;

	n = 0;
	if (ft_strncmp(args, "-n", 2) == 0 && (n = 1) == 1)
		args = args + 3;
	ft_fprintf(1, "%s", args);
	if (n != 1)
		ft_fprintf(1, "\n");
}

void	xpwd(char *args)
{
	(void)args;
	char	cwd[1024];

	getcwd(cwd, 1024);
	ft_fprintf(1, "%s\n", cwd);
}

void	xexit(char *args)
{
	(void)args;
	ft_fprintf(1, "exit\n");
	exit (0);
}

void	xcd(char *args)
{
	if (args == NULL)
		chdir(*(ret_env("HOME"))); // chdir(*ret_env("HOME")); // get from env list | is too many args here?
	else if (chdir(args) != 0)
		ft_fprintf(2, "%s\n", (strerror(errno)));
}

/*
** int		launch(char **args)
** {
** 	pid_t	pid;
** 	pid_t	wpid;
** 	int		status;
**
** 	pid = fork();
** 	if (pid == 0) //child
** 	{
** 		signal(SIGINT, SIG_DFL);
** 		if (execve(args[0], args) == -1)
** 		 	strerror(errno);
** 		exit(-1);
** 	}
** 	else if (pid < 0)
** 		strerror(errno);
** 	else
** 	{
** 		wpid = waitpid(pid, &status, WUNTRACTED);
** 		while (!WIFEXITED(status) && !WIFSIGNALED(status)) // dooo smth, killlll
**< here?
** 			;
** 	}
** 	return (1);
** }
**
** int		execute(const char **args)
** {
** 	int i;
**
** 	i = -1;
** 	while (++i < BUILTINS)
** 		if (ft_strcmp(args[0], g_builtins[i].name) == 0)
** 			return (g_builtins[i].f)(args[1]);
** 	return launch(args);
** }
**
** int		main(int ac, char **av, char **ep)
** {
** 	if (ac < 1)
** 		return (1);
** 	if (strcmp(av[1], "cd"))
** 		ft_cd(av);
** 	else
** 		execute(av);
** }
*/
