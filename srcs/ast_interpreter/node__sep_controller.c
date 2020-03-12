/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node__sep_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 02:46:55 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/12 17:51:53 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** THIS FUNCTION RUN THE LEFT CHILD OF THE DBL_AND NODE THEN WAIT FOR ITS END
** IF THE LEFT CHILD SUCCEEDED SO RUN THE RIGHT CHILD AND WAIT FOR ITS END
** RETURN THE RETURN VALUE OF THE LEFT CHILD IF IT HAS FAILED ELSE IT RETURN
** THE RETURN OF THE RIGHT CHILD ELSE
*/

int		node__dbl_and_handle(t_node *cmd_sep)
{
	int	sloc;

	sloc = node__controller(cmd_sep->left);
	if (sloc == 0)
		sloc = node__controller(cmd_sep->right);
	return (WEXITSTATUS(sloc));
}

/*
** THIS FUNCTION RUN THE LEFT CHILD OF THE DBL_OR NODE THEN WAIT FOR ITS END
** IF THE LEFT CHILD FAILED SO RUN THE RIGHT CHILD AND WAIT FOR ITS END
** RETURN THE RETURN VALUE OF THE LEFT CHILD IF IT HAS SUCCEEDED ELSE IT RETURN
** THE RETURN OF THE RIGHT CHILD ELSE
*/

int		node__dbl_or_handle(t_node *cmd_sep)
{
	int	sloc;

	sloc = node__controller(cmd_sep->left);
	if (sloc != 0)
		sloc = node__controller(cmd_sep->right);
	return (WEXITSTATUS(sloc));
}

/*
** THIS FUNCTION RUN THE LEFT CHILD OF THE SEMICON NODE THEN WAIT FOR ITS END
** IF THE RIGHT CHILD EXIST (NOT NULL) THEN RUN IT AND WAIT FOR ITS END
** RETURN THE LAST RETURN LEFT OR RIGHT
*/

int		node__semicon_handle(t_node *cmd_sep)
{
	int	sloc;

	sloc = node__controller(cmd_sep->left);
	if (cmd_sep->right)
		sloc = node__controller(cmd_sep->right);
	return (sloc);
}

/*
** THIS FUNCTION RUN THE GOOD FUNCTION TO HANDLE SEPARATORS.
** node__pipe_handle FOR PIPES
** node__dbl_and_handle FOR DBL_AND SEPARATOR
** node__dbl_or_handle FOR DBL_OR SEPARATOR
** node__semicon_handle FOR SEMICON SEPARATOR
** RETURN ERROR IF THE NODE IS NOT A GOOD SEP
*/

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
}
