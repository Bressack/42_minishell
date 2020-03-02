/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_git_current_branch_name.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:49:51 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/02 02:47:51 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <libc.h>
# define CURR_DIR	"/Users/user/Prog/42/projects/circle_4/minishell"

# define PIPE_READ			0
# define PIPE_WRITE			1

# define ISTDOUT			0
# define ISTDIN			1


static void	*join(char **ret, char *arg, int *retsize)
{
	char	*tmp;
	int		size;

	size = strlen(arg);
	if (!(tmp = malloc(sizeof(char) * (*retsize + size + 1))))
		return (NULL);
	memcpy(tmp, *ret, *retsize);
	memcpy(tmp + *retsize, arg, size);
	*retsize += size;
	tmp[*retsize] = '\0';
	free(*ret);
	*ret = tmp;
	return (tmp);
}

char		*ft_strjoin(int nb_str, ...)
{
	char	*arg;
	char	*ret;
	va_list	ap;
	int		size;

	ret = NULL;
	size = 0;
	va_start(ap, nb_str);
	while (nb_str--)
	{
		if (!(arg = va_arg(ap, char *)))
			continue ;
		if (!ret)
		{
			if (!(ret = strdup(arg)))
				return (NULL);
			size = strlen(ret);
		}
		else
			if (join(&ret, arg, &size) == NULL)
				return (NULL);
	}
	va_end(ap);
	return (ret);
}

void		function_before(int fd_in, int fd_out, void *arg)
{

}
void		function_after(int fd_in, int fd_out, void *arg)
{

}

int			run_shell_cmd(char **env, int opt, char *path_cmd, int ac, ...)
{
	va_list	ap;
	pid_t	pid;
	char	**av;
	int		stt;
	int		fd[2][2];

	fd[ISTDOUT] = {ISTDOUT, ISTDIN};
	fd[ISTDIN] = {ISTDIN, ISTDOUT};
	va_start(ap, ac);
	if (!(av = calloc(sizeof(char *), ac + 2)))
		exit(-1);
	av[0] = path_cmd;
	for (int i = 1; i < ac; i++)
		av[i] = (char *)ap[i - 1];
	function_before();
	if (!(pid = fork()))
	{
		dup2(fd[ISTDOUT][PIPE_READ], ISTDOUT);
		dup2(fd[ISTDIN][PIPE_WRITE], ISTDIN);
		close(ISTDOUT);
		close(ISTDIN);
		execve(path_cmd, av, env);
		exit(-1);
	}
	waitpid(pid, &stt, WUNTRACED);
	free(av);
	function_after();
	return (0);
}

char		*git__get_current_branch_name(char **env)
{
	pid_t	pid;
	char	**av;
	int		stt;

	int		fd[2];

	if (pipe(fd) != 0)
		return (NULL);
	av = malloc(sizeof(char *) * 3);
	av[0] = strdup("/bin/cat");
	av[1] = ft_strjoin(3, CURR_DIR, "/", ".git/HEAD");
	av[2] = NULL;
	if (!(pid = fork()))
	{
		dup2(fd[PIPE_WRITE], ISTDIN);
		close(0);
		execve("/bin/cat", av, env);
		exit(-1);
	}
	waitpid(pid, &stt, WUNTRACED);
	printf("$?: %d\n", stt);
	free(av[0]);
	free(av[1]);
	free(av);

	char	buf[1024 + 1];
	int		ret;

	ret = read(fd[PIPE_READ], buf, 1024);
	buf[ret] = 0;

	int i = strlen(buf);
	char *branch_name = NULL;

	while (--i > 0 && buf[i] != '/')
		;
	branch_name = ;
	"ref: refs/heads/*"
	return (NULL);
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	git__get_current_branch_name(env);
	return (0);
}
