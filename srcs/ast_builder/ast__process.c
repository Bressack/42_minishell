/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast__process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 04:18:58 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/10 04:19:06 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		process_call_next(t_astb *tool, t_node **sep)
{
	if (token__issep(tool->current_token))
	{
		*sep = node__new(SEP);
		if (add_token_into_node(tool, &(*sep)->sep, AST_SEP) == ERROR)
			return (ERROR);
		add_to_ast(tool, *sep);
		if (process(tool) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int		process(t_astb *tool)
{
	t_node		*cmd;
	t_node		*sep;

	if (tool->prev_token && (token__istype(tool->prev_token, SEMICON) &&
		token__iseot(tool->current_token)))
		return (SUCCESS);
	if (token__issep(tool->current_token) || token__iseot(tool->current_token))
		return (astb_error(tool, UNEXPECTED_TOKEN));
	cmd = node__new(CMD);
	while (token__isword(tool->current_token) ||
		token__isredir(tool->current_token))
	{
		if (token__isredir(tool->current_token))
		{
			if (add_token_into_node(tool, &cmd->redir, AST_REDIR) == ERROR)
				return (ERROR);
			if (add_token_into_node(tool, &cmd->file, AST_WORD) == ERROR)
				return (ERROR);
			continue ;
		}
		if (add_token_into_node(tool, &cmd->av, AST_WORD) == ERROR)
			return (ERROR);
	}
	add_to_ast(tool, cmd);
	return (process_call_next(tool, &sep));
}
