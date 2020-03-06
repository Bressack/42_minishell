/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_interpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:26:24 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/06 22:56:08 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		asti_error(char *name, int opt)
{
	if (opt == ERR_OPEN)
		ft_dprintf(2, "minishell: %s: %s\n", name, strerror(errno));
	else if (opt == ERR_PIPE)
		ft_dprintf(2, "minishell: %s\n", strerror(errno));
		return (ERROR);
}

int		node__parent_ispipe(t_node *node)
{
	return (node && node->parent && node->parent->type == SEP &&
		node->parent->sep->type == PIPE);
}

int		node__pipe_handle(t_node *ppln)
{
	int	sloc;

	if (pipe(ppln->pipe_ltor) == -1)
		return (asti_error(NULL, ERR_PIPE));
	ppln->left->stdout != STDOUT ? close(ppln->left->stdout) : 0;
	ppln->right->stdin != STDIN ? close(ppln->right->stdin) : 0;
	ppln->left->stdout = ppln->pipe_ltor[PIPE_WRITE];
	ppln->right->stdin = ppln->pipe_ltor[PIPE_READ];
	ppln->right->stdout = ppln->stdout;
	node__controller(ppln->left);
	close(ppln->pipe_ltor[PIPE_WRITE]);
	node__controller(ppln->right);
	close(ppln->pipe_ltor[PIPE_READ]);
	waitpid(ppln->left->pid, &sloc, WUNTRACED);
	waitpid(ppln->right->pid, &sloc, WUNTRACED);
	return (sloc);
}

int		node__dbl_and_handle(t_node *cmd_sep)
{
	int	sloc;

	sloc = 0;
	node__controller(cmd_sep->left);
	waitpid(cmd_sep->left->pid, &sloc, WUNTRACED);
	if (sloc == 0)
	{
		node__controller(cmd_sep->right);
		waitpid(cmd_sep->right->pid, &sloc, WUNTRACED);
	}
	return (sloc);
}

int		node__dbl_or_handle(t_node *cmd_sep)
{
	int	sloc;

	sloc = 0;
	node__controller(cmd_sep->left);
	waitpid(cmd_sep->left->pid, &sloc, WUNTRACED);
	if (sloc != 0)
	{
		node__controller(cmd_sep->right);
		waitpid(cmd_sep->right->pid, &sloc, WUNTRACED);
	}
	return (sloc);
}

int		node__semicon_handle(t_node *cmd_sep)
{
	int	sloc;

	sloc = 0;
	node__controller(cmd_sep->left);
	waitpid(cmd_sep->left->pid, &sloc, WUNTRACED);
	if (cmd_sep->right)
	{
		node__controller(cmd_sep->right);
		waitpid(cmd_sep->right->pid, &sloc, WUNTRACED);
	}
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
			(cmd->stdin != STDIN) ? close(cmd->stdin) : 0;
			if ((cmd->stdin = open(tmp_file->value,
				O_RDWR, 0644)) == -1)
				return (asti_error(tmp_file->value, ERR_OPEN));
		}
		else if (tmp_redir->type == REDIR_OUT)
		{
			(cmd->stdout != STDOUT) ? close(cmd->stdout) : 0;
			if ((cmd->stdout = open(tmp_file->value,
				O_TRUNC | O_CREAT | O_RDWR, 0644)) == -1)
				return (asti_error(tmp_file->value, ERR_OPEN));
		}
		else if (tmp_redir->type == DREDIR_OUT)
		{
			(cmd->stdout != STDOUT) ? close(cmd->stdout) : 0;
			if ((cmd->stdout = open(tmp_file->value,
				O_APPEND | O_CREAT | O_RDWR, 0644)) == -1)
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
	g_exit = execute_fork(cmd);
	if (!node__parent_ispipe(cmd))
		waitpid(cmd->pid, (int *)&g_exit, WUNTRACED);
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

// cat /dev/urandom | head -c 100 > /dev/null
// cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom |cat /dev/urandom
