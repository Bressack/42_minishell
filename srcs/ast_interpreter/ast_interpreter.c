/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_interpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:26:24 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/04 16:54:45 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		asti_error(char *name, int opt)
{
	if (opt == OPEN_ERROR)
		printf("minishell (asti_error): %s: %s\n", name, strerror(errno));
	return (ERROR);
}

int		node__pipe_handle(t_node *ppln)
{
	int	sloc;

	if (ppln->parent && ppln->parent->type == SEP && ppln->parent->sep->type == PIPE)
		ppln->right->stdout = ppln->parent->stdin;
	if (pipe(ppln->pipe_ltor) == -1)
		return (ERROR);
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
	if (sloc == SUCCESS)
		sloc = node__controller(cmd_sep->right);
	return (sloc);
}
int		node__dbl_or_handle(t_node *cmd_sep)
{
	int	sloc;

	sloc = node__controller(cmd_sep->left);
	if (sloc != SUCCESS)
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
				return (asti_error(tmp_file->value, OPEN_ERROR));
		}
		else if (tmp_redir->type == REDIR_OUT)
		{
			(cmd->stdout > 2) ? close(cmd->stdout) : 0;
			if ((cmd->stdout = open(tmp_file->value,
				O_TRUNC | O_CREAT | O_RDWR, 0644)) == -1)
				return (asti_error(tmp_file->value, OPEN_ERROR));
		}
		else if (tmp_redir->type == DREDIR_OUT)
		{
			(cmd->stdout > 2) ? close(cmd->stdout) : 0;
			if ((cmd->stdout = open(tmp_file->value,
				O_CREAT | O_RDWR, 0644)) == -1)
					return (asti_error(tmp_file->value, OPEN_ERROR));
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
