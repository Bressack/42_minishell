/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node__pipe_handle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 02:45:12 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/09 19:50:36 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** THIS FUNCTION RETURN 1 IF THE PARENT OF THE NODE IS A PIPE
** ELSE IT RETURN 0
*/

int		node__parent_ispipe(t_node *node)
{
	// dprintf(2, "parent is pipe ? %d && %d && %d && %d\n", node ? 1 : 0, node && node->parent ? 1 : 0, node && node->parent && node->parent->type == SEP ? 1 : 0, node && node->parent && node->parent->type == SEP && node->parent->sep->type == PIPE ? 1 : 0);
	return (node && node->parent && node->parent->type == SEP &&
		node->parent->sep->type == PIPE);
}

/*
** int		waitallpipes(pid_t pid, int opt)
** {
** 	static t_pid_save	*pids = NULL;
** 	t_pid_save			*new;
** 	int					sloc[2];
**
** 	sloc[0] = 0;
** 	sloc[1] = 0;
** 	if (opt == ADD)
** 	{
** 		new = mmalloc(sizeof(t_pid_save));
** 		new->pid = pid;
** 		ft_add_node_end_np((t_pnp **)&pids, (t_pnp *)new);
** 	}
** 	else if (opt == WAIT && (new = pids))
** 	{
** 		while (new->next)
** 			new = new->next;
** 		waitpid(new->pid, &sloc[0], WUNTRACED);
** 		while ((new = new->prev))
** 			waitpid(new->pid, &sloc[1], 0);
** 		}
** 		ft_del_list_np((t_pnp **)&pids);
** 	}
** 	return (sloc[0]);
** }
*/

int		waitallpipes(int pipe[2], int opt)
{
	static t_pid_save	*list = NULL;
	static int			nb_cmd = 0;
	t_pid_save			*new;
	int					sloc;

	sloc = 0;
	if (opt == ADD)
	{
		new = mmalloc(sizeof(t_pid_save));
		new->pipe[PIPE_WRITE] = pipe[PIPE_WRITE];
		new->pipe[PIPE_READ] = pipe[PIPE_READ];
		nb_cmd += 2;
		ft_add_node_end_np((t_pnp **)&list, (t_pnp *)new);
	}
	else if (opt == WAIT)
	{
		new = list;
		while (new)
		{
			printf("[PIPE { %d } ] closed !\n", new->pipe[PIPE_WRITE]);
			printf("[PIPE { %d } ] closed !\n", new->pipe[PIPE_READ]);
			close(new->pipe[PIPE_WRITE]);
			close(new->pipe[PIPE_READ]);
			new = new->next;
		}
		ft_del_list_np((t_pnp **)list);
		dprintf(2, ""C_G_RED"nb_cmd: "C_G_BLUE"%d\n"C_RES, nb_cmd);
		while (nb_cmd)
		{
			printf(TEST);
			wait(&sloc);
			printf(TEST);
			nb_cmd--;
		}
	}
	return (sloc);
}

/*
cat /dev/random | head -c 100
*/

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

int		node__pipe_handle(t_node *ppln)
{
	int	sloc;
	int	head;

	head = 0;
	sloc = 0;
	if (!node__parent_ispipe(ppln))
		head = 1;
	if (pipe(ppln->pipe_ltor) == -1)
		return (asti_error(NULL, ERR_PIPE));
	printf("[PIPE { %d } ] opened !\n", ppln->pipe_ltor[PIPE_WRITE]);
	printf("[PIPE { %d } ] opened !\n", ppln->pipe_ltor[PIPE_READ]);
	ppln->left->stdout != STDOUT ? close(ppln->left->stdout) : 0;
	ppln->right->stdin != STDIN ? close(ppln->right->stdin) : 0;
	ppln->left->stdout = ppln->pipe_ltor[PIPE_WRITE];
	ppln->right->stdin = ppln->pipe_ltor[PIPE_READ];
	ppln->right->stdout = ppln->stdout;
	node__controller(ppln->left);
	node__controller(ppln->right);
	waitallpipes(ppln->pipe_ltor, ADD);
	if (head == 1)
		sloc = waitallpipes(ppln->pipe_ltor, WAIT);
	return (WEXITSTATUS(sloc));
}