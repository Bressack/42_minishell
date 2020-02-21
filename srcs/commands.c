/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 11:59:36 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/21 01:27:07 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ""

#define BUILTINS 7

typedef struct		s_bi
{
	char	*name;
	void	(f*)(const char	*arg);
}					t_bi;

t_bi		g_builtins[BUILTINS] =
{
	{"echo", &bi_echo},
	{"cd", &bi_cd},
	{"pwd", &bi_pwd},
	{"exit", &bi_exit}, // or just immidiately?
	{"export", &bi_export},
	{"unset", &bi_unset},
	{"env", &bi_env}
};

void	xecho(int fd, char **args)
{
	int n;

	if (ft_strcmp(*args, "-n") == 0 && (n = 1) == 1)
		args++;
/*
** 	if (args > 2)
** 		ft_fprintf(2, "cd: too many arguments\n");
*/
	while (*args != NULL)
		ft_fprintf(fd, "%s", *args++);
	if (n != 1)
		ft_fprintf(fd, "\n");
}

void	xpwd(int fd, char **args)
{
	char	cwd[1024];

	getcwd(cwd, 1024);
	ft_fprintf(fd, "%s\n", cwd);
}

void	xexit()
{
	ft_fprintf(1, "exit");
	exit (0);
}

void	xcd(char *args)
{
	if (args == NULL)
		chdir("/Users/frlindh"); // get from env list
	else
		if (chdir(args) != 0)
			ft_fprintf(2, "%s\n", (strerror(errno)));
}

int		launch(char **args)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0) //child
	{
		signal(SIGINT, SIG_DFL);
		if (execve(args[0], args) == -1)
		 	strerror(errno);
		exit(-1);
	}
	else if (pid < 0)
		strerror(errno);
	else
	{
		wpid = waitpid(pid, &status, WUNTRACTED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status)) // dooo smth killlll here?
			;
	}
	return (1);
}

int		execute(const char **args)
{
	int i;

	i = -1;
	while (++i < BUILTINS)
	{
		if (strcmp(args[0], g_builtins[i].name) == 0)
			return (g_builtins[i].f)(args[1]);
	}
	return launch(args);
}

int		main(int ac, char **av, char **ep)
{
	if (ac < 1)
		return (1);
	if (strcmp(av[1], "cd"))
		ft_cd(av);
	else
		execute(av);
}
