/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_interpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:26:24 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/02 15:05:21 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	asti_error(char *name, int opt)
{
	if (opt == OPEN_ERROR)
		printf("minishell: %s: %s\n", name, strerror(errno));
}

int		node__pipe_handle(t_node *cmd_sep)
{
	int		fd[2];                                                              // pipe between the output of the left child and the input on the right one
	int		ret;                                                                // the return of the two commands (second call (l:31) overwrite ret, but its normal)

	if (pipe(fd) != 0)                                                          // create pipe
		exit(-1); // TODO error function;                                       // (TODO) add a correct message into asti_error() to delete this warning
	cmd_sep->left->stdio[ISTDOUT] = fd[ISTDIN];                                 // (not sure about that) assign the pipe to left child's output
	cmd_sep->right->stdio[ISTDIN] = fd[ISTDOUT];                                // (not sure about that) assign the pipe to right child's input
	ret = node__controller(cmd_sep->left);                                      //
	ret = node__controller(cmd_sep->right);                                     //
	return (ret);                                                               //
}

int		node__dbl_and_handle(t_node *cmd_sep)
{
	int	ret;

	ret = node__controller(cmd_sep->left);
	if (ret == ASTI_SUCCESS)
		ret = node__controller(cmd_sep->right);
	return (ret);
}
int		node__dbl_or_handle(t_node *cmd_sep)
{
	int	ret;

	ret = node__controller(cmd_sep->left);
	if (ret != ASTI_SUCCESS)
		ret = node__controller(cmd_sep->right);
	return (ret);
}
int		node__semicon_handle(t_node *cmd_sep)
{
	int	ret;

	ret = node__controller(cmd_sep->left);
	ret = node__controller(cmd_sep->right);
	return (ret);
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
		return (ASTI_FAILURE);
}

void	redir_handle(t_node *cmd)
{
	t_token	*tmp_redir;
	t_token	*tmp_file;

	tmp_redir = cmd->redir;
	tmp_file = cmd->file;

	while (tmp_redir && tmp_file)
	{
		if (tmp_redir->type == REDIR_IN)
		{
			(cmd->fd[ISTDIN][PIPE_READ] > 2) ? close(cmd->fd[ISTDIN][PIPE_READ]) : 0;
			if ((cmd->fd[ISTDIN][PIPE_READ] = open(tmp_file->value,
				O_RDWR, 0644)) == -1)
				asti_error(tmp_file->value, OPEN_ERROR);
		}
		else if (tmp_redir->type == REDIR_OUT)
		{
			(cmd->fd[ISTDOUT][PIPE_WRITE] > 2) ? close(cmd->fd[ISTDOUT][PIPE_WRITE]) : 0;
			if ((cmd->fd[ISTDOUT][PIPE_WRITE] = open(tmp_file->value,
				O_TRUNC | O_CREAT | O_RDWR)) == -1)
				asti_error(tmp_file->value, OPEN_ERROR);
		}
		else if (tmp_redir->type == DREDIR_OUT)
		{
			(cmd->fd[ISTDOUT][PIPE_WRITE] > 2) ? close(cmd->fd[ISTDOUT][PIPE_WRITE]) : 0;
			if ((cmd->fd[ISTDOUT][PIPE_WRITE] = open(tmp_file->value,
				O_CREAT | O_RDWR)) == -1)
				asti_error(tmp_file->value, OPEN_ERROR);
		}
		tmp_redir = tmp_redir->next;
		tmp_file = tmp_file->next;
	}
}

int		node__cmd_controller(t_node *cmd)
{
	redir_handle(cmd);
	return (execute(cmd));
}

int		node__controller(t_node *node)
{
	if (node->type == SEP)
		return (node__sep_controller(node));
	else if (node->type == CMD)
		return (node__cmd_controller(node));
	else
		return (FAILURE);
}

int		ast_interpreter(t_node *ast)
{
	return (node__controller(ast));
}
