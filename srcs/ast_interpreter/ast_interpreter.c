/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_interpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:26:24 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/04 11:08:15 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	asti_error(char *name, int opt)
{
	if (opt == OPEN_ERROR)
		printf("minishell: %s: %s\n", name, strerror(errno));
}

int		node__pipe_handle(t_node *ppln)
{
	int	sloc;

	if (ppln->parent && ppln->parent->type == SEP && ppln->parent->sep->type == PIPE)
		ppln->right->stdout = ppln->parent->stdin;
	if (pipe(ppln->pipe_ltor) == -1)
		return (-1);
	ppln->left->stdout = ppln->pipe_ltor[PIPE_WRITE];
	ppln->right->stdin = ppln->pipe_ltor[PIPE_READ];
	if (!(sloc = node__controller(ppln->left)))
	{
		close(ppln->left->stdout);
		sloc = node__controller(ppln->right);
	}
	close(ppln->right->stdin);
	return (sloc);
}

int		node__dbl_and_handle(t_node *cmd_sep)
{
	int	sloc;

	sloc = node__controller(cmd_sep->left);
	if (sloc == ASTI_SUCCESS)
		sloc = node__controller(cmd_sep->right);
	return (sloc);
}
int		node__dbl_or_handle(t_node *cmd_sep)
{
	int	sloc;

	sloc = node__controller(cmd_sep->left);
	if (sloc != ASTI_SUCCESS)
		sloc = node__controller(cmd_sep->right);
	return (sloc);
}
int		node__semicon_handle(t_node *cmd_sep)
{
	int	sloc;

	sloc = node__controller(cmd_sep->left);
	if (cmd_sep->right)
		sloc = node__controller(cmd_sep->right);
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
		return (ASTI_FAILURE);
	return (0);
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
			(cmd->stdin > 2) ? close(cmd->stdin) : 0;
			if ((cmd->stdin = open(tmp_file->value,
				O_RDWR, 0644)) == -1)
				asti_error(tmp_file->value, OPEN_ERROR);
		}
		else if (tmp_redir->type == REDIR_OUT)
		{
			(cmd->stdout > 2) ? close(cmd->stdout) : 0;
			if ((cmd->stdout = open(tmp_file->value,
				O_TRUNC | O_CREAT | O_RDWR, 0644)) == -1)
				asti_error(tmp_file->value, OPEN_ERROR);
		}
		else if (tmp_redir->type == DREDIR_OUT)
		{
			(cmd->stdout > 2) ? close(cmd->stdout) : 0;
			if ((cmd->stdout = open(tmp_file->value,
				O_CREAT | O_RDWR, 0644)) == -1)
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
		return (ASTI_SUCCESS);
}

int		ast_interpreter(t_node *ast)
{
	return (node__controller(ast));
}
