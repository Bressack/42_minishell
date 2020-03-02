/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:59:11 by frlindh           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/03/02 16:03:49 by tharchen         ###   ########.fr       */
=======
/*   Updated: 2020/03/02 18:10:37 by frlindh          ###   ########.fr       */
>>>>>>> 44f8c5ad97bc88be0e3ebc5c641ec8aee615262b
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

char	*get_next_path(char **env, char *command)
{
	int		i;
	char	*path;

	i = 0;
	while ((*env)[i] && (*env)[i] != '\n' && (*env)[i] != ':')
		i++;
	path = (char *)mmalloc(sizeof(char) * (i + ft_strlen(command) + 1));
	i = 0;
	while (**env && **env != '\n' && **env != ':')
		path[i++] = *((*env)++);
	if (**env == ':')
		(*env)++;
	path[i++] = '/';
	while (command && *command)
		path[i++] = *command++;
	path[i] = '\0';
	printf("GNPATH: [%s]\n", path);
	return (path);
}

char	*get_no_path(char *com)
{
	int		i;
	char	*path;

	path = (char *)mmalloc(sizeof(char) * (ft_strlen(com)) + 3);
	i = 0;
	path[i++] = '.';
	path[i++] = '/';
	while (com && *com)
		path[i++] = *com++;
	path[i] = '\0';
	return(path);
}

// OBS RETURN OF STAT FUNCTIONS
// struct stat {
//     dev_t     st_dev;     /* ID of device containing file */
//     ino_t     st_ino;     /* inode number */
//     mode_t    st_mode;    /* protection */
//     nlink_t   st_nlink;   /* number of hard links */
//     uid_t     st_uid;     /* user ID of owner */
//     gid_t     st_gid;     /* group ID of owner */
//     dev_t     st_rdev;    /* device ID (if special file) */
//     off_t     st_size;    /* total size, in bytes */
//     blksize_t st_blksize; /* blocksize for file system I/O */
//     blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
//     time_t    st_atime;   /* time of last access */
//     time_t    st_mtime;   /* time of last modification */
//     time_t    st_ctime;   /* time of last status change */
// };


char	*get_path(char *command)
{
	int		i;
	char	*env;
	char	*path;
	struct stat buf;

	i = -1;
	path = NULL;
	while (command[++i] && (command[i] == '.' || command[i] == '/'))
		if (command[i] == '/' && (i = -1) < 0)
			break;
	if (i == -1)
		path = command;
	else if (!ret_envval("PATH"))
		path = get_no_path(command);
	else
		env = ret_envval("PATH");
	if (path && !stat(path, &buf))
		return (path);
	else if (!path)
		while (env && *env && (path = get_next_path(&env, command)))
			if (!stat(path, &buf))
				return (path);
	bi_error(command, NULL, strerror(errno), 0);
	// bi_error(command, NULL, "command not found", 0);
	return (NULL);
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
		// exit (3);
	}
}

int		launch(t_node *cmd, char **av)
{
	pid_t	pid;
	pid_t	wpid;
	int		sloc;
	char	*path; // BRUH // yes, use malloc, it's better.
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
		if ((path = get_path(av[0])))
			execve(path, av, environ); // SHOULD MAYBE NOT USE MALLOC?
		exit(1);
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
<<<<<<< HEAD
	av += assign;
=======
>>>>>>> 44f8c5ad97bc88be0e3ebc5c641ec8aee615262b
	j = -1;
	while (++j < BUILTINS)
		if (!ft_strcmp(av[assign], g_builtins[j].name))
			return (g_builtins[j].f(ac, &av[assign]));
	return (launch(cmd, &av[assign]));
}
