/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node__pipe_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 02:45:12 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/12 19:09:56 by frlindh          ###   ########.fr       */
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

int		waitallpipes(int pipe[2], int opt)
{
	static t_pipe_save	*list[2] = {NULL, NULL};
	static int			nb_cmd = 1;

	return (0);
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

int		execute_pipes(t_node *node);

int		execute_pipe(t_node *node, int last)
{
	pid_t	pid;
	int		pfd[2];
	int		in;

	in = execute_pipes(node->left);
	if (!last && pipe(pfd) < 0)
		return (asti_error(NULL, ERR_PIPE));
	if ((pid = fork()) < 0)
		return (asti_error(NULL, ERR_PIPE));
	if (pid == 0)
	{
		if (dup2(in, 0) == -1)
			return (asti_error(NULL, ERR_PIPE));
		close(in);
		if (!last)
		{
			if (dup2(pfd[1], 1) == -1)
				return (asti_error(NULL, ERR_PIPE));
			close(pfd[0]);
			close(pfd[1]);
		}
		execute_nofork(node->right);
	}
	if (!last)
		close(pfd[1]);
	close(in);
	pid_save(pid, ADD);
	return (last) ? (0) : (pfd[0]);
}

int		execute_pipes(t_node *node)
{
	if (node->type == PIPE)
		return (execute_pipe(node, 0));
	if (node->type == CMD)
		return (execute_fork(node));
	return (0);
}

int		node__pipe_handle(t_node *ppln)
{
	int sig;

	execute_pipe(ppln, 1);
	sig = pid_save(0, WAIT | FREE);
	return (WEXITSTATUS(sig));
}
