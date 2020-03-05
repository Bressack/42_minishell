/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_interpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:26:24 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/05 02:57:00 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		asti_error(char *name, int opt)
{
	if (opt == ERR_OPEN)
		printf("minishell: %s: %s\n", name, strerror(errno));
	else if (opt == ERR_PIPE)
		printf("minishell: %s\n", strerror(errno));
		return (ERROR);
}

typedef struct			s_ppln_pid
{
	struct s_ppln_pid	*next;
	struct s_ppln_pid	*prev;
	int					pid;
}						t_ppln_pid;

/*
** opt: ADD -> add param pid to the end of the list
** opt: CLOSE -> wait all child
*/

int		node__waitnclose(int pid, int opt, int *sloc)
{
	static t_ppln_pid	*ppln_list = NULL;
	t_ppln_pid			*new;
	t_ppln_pid			*tmp;
	int					first;

	first = ppln_list == NULL ? 1 : 0;
	if (opt == ADD)
	{
		new = try_malloc(sizeof(t_ppln_pid), _FL_);
		new->pid = pid;
		ft_add_node_end_np((t_pnp **)&ppln_list, (t_pnp *)new);
	}
	else if (opt == CLOSE)
	{
		tmp = ppln_list;
		while (tmp)
		{
			new = tmp->next;
			if (waitpid(tmp->pid, sloc, WUNTRACED) == -1)
				asti_error("insert_cmd_name_here", ERR_PIPE);
			try_free_((void **)&tmp, _FL_);
		}
		ppln_list = NULL;
	}
	return (first);
}

// [ a | b | c | d ]
//
//             [|]
//            /   \
//         [|]     {d}
//        /   \
//     [|]     {c}
//    /   \
// {a}     {b}
//

int		node__parent_ispipe(t_node *node)
{
	return (node && node->type == SEP && node->sep->type == PIPE);
}

int		node__pipe_handle(t_node *ppln)
{
	int	sloc;
	int	first;

	if (pipe(ppln->pipe) == -1)
		return (asti_error(NULL, ERR_PIPE));
	if (node__parent_ispipe(ppln->parent) && ppln->parent->right)
		ppln->parent->right->stdin = ppln->right->stdout;
	if (!node__parent_ispipe(ppln->parent))
		ppln->left->stdin = 0;
	ppln->left->stdout = ppln->pipe[PIPE_WRITE];
	ppln->right->stdin = ppln->pipe[PIPE_READ];
	node__controller(ppln->left);
	first = node__waitnclose(ppln->left->pid, ADD, &sloc);
	node__controller(ppln->right);
	node__waitnclose(ppln->right->pid, ADD, &sloc);
	if (first == 1)
		node__waitnclose(0, CLOSE, &sloc);
	return (sloc);
}

int		node__dbl_and_handle(t_node *cmd_sep)
{
	int	sloc;

	node__controller(cmd_sep->left);
	if (waitpid(cmd_sep->left->pid, &sloc, WUNTRACED) == -1)
		asti_error("insert_cmd_name_here", ERR_PIPE);
	if (sloc == SUCCESS)
		node__controller(cmd_sep->right);
	if (waitpid(cmd_sep->right->pid, &sloc, WUNTRACED) == -1)
		asti_error("insert_cmd_name_here", ERR_PIPE);
	return (sloc);
}

int		node__dbl_or_handle(t_node *cmd_sep)
{
	int	sloc;

	node__controller(cmd_sep->left);
	if (waitpid(cmd_sep->left->pid, &sloc, WUNTRACED) == -1)
		asti_error("insert_cmd_name_here", ERR_PIPE);
	if (sloc != SUCCESS)
		node__controller(cmd_sep->right);
	if (waitpid(cmd_sep->right->pid, &sloc, WUNTRACED) == -1)
		asti_error("insert_cmd_name_here", ERR_PIPE);
	return (sloc);
}

int		node__semicon_handle(t_node *cmd_sep)
{
	int	sloc;

	node__controller(cmd_sep->left);
	if (waitpid(cmd_sep->left->pid, &sloc, WUNTRACED) == -1)
		asti_error("insert_cmd_name_here", ERR_PIPE);
	if (cmd_sep->right)
		node__controller(cmd_sep->right);
	if (waitpid(cmd_sep->right->pid, &sloc, WUNTRACED) == -1)
		asti_error("insert_cmd_name_here", ERR_PIPE);
	return (sloc);
}

int		node__sep_controller(t_node *sep)
{
	if (token__istype(sep->sep, PIPE))
		return (node__pipe_handle(sep));
	else if (token__istype(sep->sep, DBL_AND))
		return (node__dbl_and_handle(sep));
	else if (token__istype(sep->sep, DBL_OR))
		return (node__dbl_or_handle(sep));
	else if (token__istype(sep->sep, SEMICON))
		return (node__semicon_handle(sep));
	else
		return (ERROR);
	return (SUCCESS);
}

int		redir_handle(t_node *cmd)
{
	t_token	*tmp_redir;
	t_token	*tmp_file;

	tmp_redir = cmd->redir;
	tmp_file = cmd->file;

	while (tmp_redir && tmp_file)
	{
		if (tmp_redir->type == REDIR_IN)
		{
			(cmd->stdin > 2) ? close(cmd->stdin) : 0;
			if ((cmd->stdin = open(tmp_file->value,
				O_RDWR, 0644)) == -1)
				return (asti_error(tmp_file->value, ERR_OPEN));
		}
		else if (tmp_redir->type == REDIR_OUT)
		{
			(cmd->stdout > 2) ? close(cmd->stdout) : 0;
			if ((cmd->stdout = open(tmp_file->value,
				O_TRUNC | O_CREAT | O_RDWR, 0644)) == -1)
				return (asti_error(tmp_file->value, ERR_OPEN));
		}
		else if (tmp_redir->type == DREDIR_OUT)
		{
			(cmd->stdout > 2) ? close(cmd->stdout) : 0;
			if ((cmd->stdout = open(tmp_file->value,
				O_CREAT | O_RDWR, 0644)) == -1)
					return (asti_error(tmp_file->value, ERR_OPEN));
		}
		tmp_redir = tmp_redir->next;
		tmp_file = tmp_file->next;
	}
	return (SUCCESS);
}

int		node__cmd_controller(t_node *cmd)
{
	if (redir_handle(cmd) == ERROR)
		return (ERROR);
	g_exit = execute(cmd);
	return (g_exit);
}

int		node__controller(t_node *node)
{
	if (node->type == SEP)
		return (node__sep_controller(node));
	else if (node->type == CMD)
		return (node__cmd_controller(node));
	else
		return (SUCCESS);
}

int		ast_interpreter(t_node *ast)
{
	return (node__controller(ast));
}
