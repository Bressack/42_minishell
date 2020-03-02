/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:25:26 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/02 18:15:28 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>

# define PIPE_READ		0 // the side of the pipe where the cmd will read
# define PIPE_WRITE		1 // the side of the pipe where the cmd will write
# define STDOUT			0 // where the cmd will write
# define STDIN			1 // where the cmd will read

int		child(char *path, char **av, char **env, int *fd, int fd_to)
{
	pid_t	pid;
	int		sloc;

	// printf("path  : {%s}\n", path);
	// printf("av[0] : {%s}\n", av[0]);
	// printf("av[1] : {%s}\n", av[1]);
	// printf("fd    : {%d}\n", *fd);
	// printf("fd_to : {%d}\n", fd_to);
	sloc = 0;
	if (!(pid = fork()))
	{
		dup2(*fd, fd_to);
		close(fd_to);
		execve(path, av, env);
		dprintf(2, "error\n");
		exit(-1);
	}
	waitpid(pid, &sloc, WUNTRACED);
	return (sloc);
}

int		main(int ac, char **av, char **env)
{
	(void)ac, (void)av;

	char *av_ls[3] = {"/bin/ls", "-l", NULL};
	char *av_cat[3] = {"/bin/cat", "-e", NULL};
	// ls -l | cat -e
	int		fd_pipe[2];

	if (pipe(fd_pipe) == -1)
		return (-1);

	if (!(child("/bin/ls", (char **)&av_ls, env, &fd_pipe[PIPE_WRITE], STDIN)))
		child("/bin/cat", (char **)&av_cat, env, &fd_pipe[PIPE_READ], STDOUT);
	return (0);
}
