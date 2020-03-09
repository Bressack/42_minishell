/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 02:44:24 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/09 02:52:26 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		redir_handle__each(t_node *cmd, t_token *tmp_redir, t_token *tmp_file)
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
	return (SUCCESS);
}

/*
** THIS FUNCTION WILL OPEN ALL REDIRECTION AND ASSIGN TO cmd->stdout OR
** cmd->stdin
** THE FD JUST OPENED. BEFORE THE ASSIGNMENT, IT CLOSE THE FD PRESENT IN
** cmd->stdout OR cmd->stdin IF THEY ARE DIFFERENT OF STDOUT OR STDIN
*/

int		redir_handle(t_node *cmd)
{
	t_token	*tmp_redir;
	t_token	*tmp_file;
	int		ret;

	tmp_redir = cmd->redir;
	tmp_file = cmd->file;
	while (tmp_redir && tmp_file)
	{
		if ((ret = redir_handle__each(cmd, tmp_redir, tmp_file)) != SUCCESS)
			return (ret);
		tmp_redir = tmp_redir->next;
		tmp_file = tmp_file->next;
	}
	return (SUCCESS);
}
