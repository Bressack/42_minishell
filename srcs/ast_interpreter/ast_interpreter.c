/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_interpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 22:32:02 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/12 17:24:23 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** THIS FUNCTION PRINT ERRORS ON STDERR
**
** ERR_OPEN : ERROR FROM open() (strerror() RETURN THE MESSAGE)
** ERR_PIPE : ERROR FROM pipe() (strerror() RETURN THE MESSAGE)
*/

int		asti_error(char *name, int opt)
{
	if (opt == ERR_OPEN)
		ft_dprintf(2, "minishell: %s: %s\n", name, strerror(errno));
	else if (opt == ERR_PIPE)
		ft_dprintf(2, "minishell: %s\n", strerror(errno));
		return (ERROR);
}

/*
** THIS FUNCTION WILL HANDLE REDIRECTION OF THE CMD FIRST (THAT WILL OVERWRITES
** PIPES WHO COULD BE OPENED BEFORE) AND THEN RUN THE GOOD FUNCTION TO RUN A
** COMMAND
*/

int		node__cmd_controller(t_node *cmd)
{
	if (redir_handle(cmd) == ERROR)
		return (ERROR);
	if (node__parent_ispipe(cmd))
		g_exit = execute_fork(cmd);
	else
		g_exit = execute_simple(cmd);
	cmd->stdout != STDOUT ? close(cmd->stdout) : 0;
	cmd->stdin != STDIN ? close(cmd->stdin) : 0;
	return (g_exit);
}

/*
** THIS FUNCTION WILL RUN THE GOOD FUNCTION TO HANDLE THE CURRENT NODE
** IF SEP -> RUN node__sep_controller
** ELSE IF CMD -> RUN node__cmd_controller
** ELSE JUST RETURN SUCCESS (EMPTY EXPRESSION)
*/

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
