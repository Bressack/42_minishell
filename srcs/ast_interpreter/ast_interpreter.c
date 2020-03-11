/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_interpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 22:32:02 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/11 16:49:23 by tharchen         ###   ########.fr       */
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
	// printf("[ CMD %s ] [ parent: %s ] [ left: %s ] [ right: %s ]\n",
	// cmd->av->value,
	// cmd->parent ?
	// 	cmd->parent->type == CMD ?
	// 		cmd->parent->av->value
	// 		:	cmd->parent->type == SEP ?
	// 				cmd->parent->sep->type == PIPE ?
	// 					"PIPE"
	// 				:	cmd->parent->sep->type == SEMICON ?
	// 					"SEMICON"
	// 					:	cmd->parent->sep->type == DBL_AND ?
	// 						"DBL_AND"
	// 						:	cmd->parent->sep->type == DBL_OR ?
	// 							"DBL_OR"
	// 						: "unvalid sep token"
	// 			: "unvalid node"
	// 	: "null",
	// cmd->left   ?
	// 	cmd->left  ->type == CMD ?
	// 		cmd->left  ->av->value
	// 		:	cmd->left  ->type == SEP ?
	// 				cmd->left  ->sep->type == PIPE ?
	// 					"PIPE"
	// 				:	cmd->left  ->sep->type == SEMICON ?
	// 					"SEMICON"
	// 					:	cmd->left  ->sep->type == DBL_AND ?
	// 						"DBL_AND"
	// 						:	cmd->left  ->sep->type == DBL_OR ?
	// 							"DBL_OR"
	// 						: "unvalid sep token"
	// 			: "unvalid node"
	// 	: "null",
	// cmd->right  ?
	// 	cmd->right ->type == CMD ?
	// 		cmd->right ->av->value
	// 		:	cmd->right ->type == SEP ?
	// 				cmd->right ->sep->type == PIPE ?
	// 					"PIPE"
	// 				:	cmd->right ->sep->type == SEMICON ?
	// 					"SEMICON"
	// 					:	cmd->right ->sep->type == DBL_AND ?
	// 						"DBL_AND"
	// 						:	cmd->right ->sep->type == DBL_OR ?
	// 							"DBL_OR"
	// 						: "unvalid sep token"
	// 			: "unvalid node"
	// 	: "null"
	// );
	if (node__parent_ispipe(cmd))
		g_exit = execute_fork(cmd);
	else
		g_exit = execute_simple(cmd);
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
