/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 17:25:26 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/03 17:09:45 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>

# define PIPE_READ		0 // the side of the pipe where the cmd will read
# define PIPE_WRITE		1 // the side of the pipe where the cmd will write
# define STDIN			0 // where the cmd will read
# define STDOUT			1 // where the cmd will write
# define STDERR			2 // where the cmd will write

typedef int			fd_t;

typedef struct		s_cmd
{
	pid_t			pid;
	int				sloc;
	char			**av;
	char			**env;
	fd_t			stdin;
	fd_t			stdout;
}					t_cmd;
typedef struct		s_pipe
{
	int				sloc;
	int				pipeline[2];
	t_cmd			left;
	t_cmd			right;
}					t_pipe;

int		child(t_cmd	*cmd)
{
	if (!(cmd->pid = fork()))
	{
		dup2(cmd->stdout, STDOUT);
		dup2(cmd->stdin, STDIN);
		execve(cmd->av[0], cmd->av, cmd->env);
		dprintf(2, "error\n");
		exit(-1);
	}
	waitpid(cmd->pid, &cmd->sloc, WUNTRACED);
	return (cmd->sloc);
}

int		pipe_handle(t_pipe *ppln)
{
	if (pipe(ppln->pipeline) == -1)
		return (-1);
	ppln->left.stdout = ppln->pipeline[PIPE_WRITE];
	ppln->right.stdin = ppln->pipeline[PIPE_READ];
	if (!(ppln->sloc = child(&ppln->left)))
	{
		close(ppln->left.stdout);
		ppln->sloc = child(&ppln->right);
	}
	return (ppln->sloc);
}

a | b | c | d

           |
         /   \
       |      d
     /   \
   |      c
 /   \
a     b

int		main(int ac, char **av, char **env)
{
	(void)ac, (void)av;

	char			*av_ls[3] = {"/bin/ls", "-l", NULL};
	char			*av_av[3] = {"/bin/cat", "-e", NULL};
	t_pipe			ppln =
	{
		/*sloc     = */ 0,
		/*pipeline = */ {0, 0},
		/*left     = */
		{
			/*pid      = */ 0,
			/*sloc     = */ 0,
			/*av       = */ (char **)&av_ls,
			/*env      = */ env,
			/*stdin    = */ STDIN,
			/*stdout   = */ STDOUT
		},
		/*right = */
		{
			/*pid      = */ 0,
			/*sloc     = */ 0,
			/*av       = */ (char **)&av_av,
			/*env      = */ env,
			/*stdin    = */ STDIN,
			/*stdout   = */ STDOUT
		}
	};
	pipe_handle(&ppln);
	return (0);
}
