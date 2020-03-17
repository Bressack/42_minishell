/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node__pipe_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 02:45:12 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/12 23:40:14 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		pid_save(int pid, int opt)
{
	static t_pid_save	*list = NULL;
	t_pid_save			*new;
	int					sloc;

	sloc = 0;
	if (opt & ADD)
	{
		new = mmalloc(sizeof(t_pid_save));
		new->pid = pid;
		ft_add_node_end_np((t_pnp **)&list, (t_pnp *)new);
	}
	else if (opt & WAIT)
	{
		new = list;
		while (new)
		{
			waitpid(new->pid, &sloc, 0);
			new = new->next;
		}
		return (sloc);
	}
	else if (opt & FREE)
		ft_del_list_np((t_pnp **)&list);
	return (0);
}

/*
** THIS FUNCTION OPEN A NEW PIPE AND ASSIGN THE WRITE SIDE TO THE LEFT CHILD
** AND THE READ SIDE TO THE RIGHT ONE.
**
** IT CLOSE THE STDOUT FD OF THE LEFT CHILD IF DIFFERENT STDOUT (1)
** IT CLOSE THE STDIN FD OF THE RIGHT CHILD IF DIFFERENT STDIN (0)
**
** RUN THE LEFT CHILD THEN CLOSE THE WRITE SIDE OF THE PIPE CAUSE THE LEFT CHILD
** HAS FINISHED TO USE IT
**
** RUN THE RIGHT CHILD THEN CLOSE THE READ SIDE OF THE PIPE CAUSE THE RIGHT
** CHILD HAS FINISHED TO USE IT
*/

int		node__cmdpipefirst_controller(t_node *cmd)
{
	cmd->stdin != STDIN ? close(cmd->stdin) : 0;
	cmd->stdout != STDOUT ? close(cmd->stdout) : 0;
	if (pipe(cmd->pipe_ltor) == -1)
		return (asti_error(NULL, ERR_PIPE));
	cmd->stdout = cmd->pipe_ltor[PIPE_WRITE];
	if (redir_handle(cmd) == ERROR)
		return (-1);
	g_exit = execute_fork(cmd, cmd->pipe_ltor[PIPE_READ]);
	close(cmd->pipe_ltor[PIPE_WRITE]);
	return (cmd->pipe_ltor[PIPE_READ]);
}

int		node__cmdpipe_controller(t_node *cmd, int fdread)
{
	cmd->stdin != STDIN ? close(cmd->stdin) : 0;
	cmd->stdout != STDOUT ? close(cmd->stdout) : 0;
	if (node__parent_ispipe(cmd->parent))
	{
		if (pipe(cmd->pipe_ltor) == -1)
			return (asti_error(NULL, ERR_PIPE));
		cmd->stdout = cmd->pipe_ltor[PIPE_WRITE];
	}
	cmd->stdin = fdread;
	if (redir_handle(cmd) == ERROR)
		return (-1);
	g_exit = node__parent_ispipe(cmd->parent) ?
	execute_fork(cmd, cmd->pipe_ltor[PIPE_READ]) : execute_fork(cmd, 0);
	close(fdread);
	if (node__parent_ispipe(cmd->parent))
	{
		close(cmd->pipe_ltor[PIPE_WRITE]);
		return (cmd->pipe_ltor[PIPE_READ]);
	}
	return (STDOUT);
}

int		node__subpipe_handle(t_node *ppln)
{
	int	fdread;

	if (ppln->left->type == CMD)
	{
		if ((fdread = node__cmdpipefirst_controller(ppln->left)) == -1)
			return (-1);
	}
	else if ((fdread = node__subpipe_handle(ppln->left)) == -1)
		return (-1);
	if ((fdread = node__cmdpipe_controller(ppln->right, fdread)) == -1)
		return (-1);
	return (fdread);
}

int		node__pipe_handle(t_node *ppln)
{
	int sig;

	if ((node__subpipe_handle(ppln)) == -1)
		return (1);
	sig = pid_save(0, WAIT | FREE);
	g_exit = WEXITSTATUS(sig);
	return (WEXITSTATUS(sig));
}
