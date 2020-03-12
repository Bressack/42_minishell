/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node__pipe_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 02:45:12 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/12 20:50:54 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** THIS FUNCTION RETURN 1 IF THE PARENT OF THE NODE IS A PIPE
** ELSE IT RETURN 0
*/

int		node__parent_ispipe(t_node *node)
{
	return (node && node->parent && node->parent->type == SEP &&
		node->parent->sep->type == PIPE);
}

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

int		waitallpipes(int pipe[2], int opt)
{
	static t_pipe_save	*list[2] = {NULL, NULL};
	static int			nb_cmd = 1;

	if (opt & ADD)
	{
		list[1] = mmalloc(sizeof(t_pipe_save));
		list[1]->pipe[PIPE_WRITE] = pipe[PIPE_WRITE];
		list[1]->pipe[PIPE_READ] = pipe[PIPE_READ];
		nb_cmd += 1;
		ft_add_node_end_np((t_pnp **)&list[0], (t_pnp *)list[1]);
	}
	if (opt & CLOSE)
	{
		list[1] = list[0];
		while (list[1])
		{
			close(list[1]->pipe[PIPE_WRITE]);
			close(list[1]->pipe[PIPE_READ]);
			list[1] = list[1]->next;
		}
	}
	if (opt & WAIT)
		return (pid_save(0, WAIT | FREE));
	opt & FREE ? ft_del_list_np((t_pnp **)&list[0]) : 0;
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

// int		node__pipe_handle(t_node *ppln)
// {
// 	int	sloc;
// 	int	head;
//
// 	head = 0;
// 	sloc = 0;
// 	if (!node__parent_ispipe(ppln))
// 		head = 1;
// 	if (pipe(ppln->pipe_ltor) == -1)
// 		return (asti_error(NULL, ERR_PIPE));
// 	ppln->left->stdout != STDOUT ? close(ppln->left->stdout) : 0;
// 	ppln->right->stdin != STDIN ? close(ppln->right->stdin) : 0;
// 	ppln->left->stdout = ppln->pipe_ltor[PIPE_WRITE];
// 	ppln->right->stdin = ppln->pipe_ltor[PIPE_READ];
// 	ppln->right->stdout = ppln->stdout;
// 	waitallpipes(ppln->pipe_ltor, ADD);
// 	node__controller(ppln->left);
// 	node__controller(ppln->right);
// 	if (head == 1)
// 		sloc = waitallpipes(ppln->pipe_ltor, WAIT | CLOSE | FREE);
// 	return (WEXITSTATUS(sloc));
// }


int		node__cmdpipefirst_controller(t_node *cmd)
{
	cmd->stdout != STDOUT ? close(cmd->stdout) : 0;
	if (pipe(cmd->pipe_ltor) == -1)
		return (asti_error(NULL, ERR_PIPE));
	cmd->stdout = cmd->pipe_ltor[PIPE_WRITE];
	if (redir_handle(cmd) == ERROR)
		return (ERROR);
	g_exit = execute_fork(cmd);
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
		return (ERROR);
	g_exit = execute_fork(cmd);
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
		fdread = node__cmdpipefirst_controller(ppln->left);
	else
		fdread = node__subpipe_handle(ppln->left);
	fdread = node__cmdpipe_controller(ppln->right, fdread);
	return (fdread);
}

int		node__pipe_handle(t_node *ppln)
{
	node__subpipe_handle(ppln);
	return (pid_save(0, WAIT | FREE));
}
