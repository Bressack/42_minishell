/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_interpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 22:32:02 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/07 22:53:55 by tharchen         ###   ########.fr       */
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
** THIS FUNCTION RETURN 1 IF THE PARENT OF THE NODE IS A PIPE
** ELSE IT RETURN 0
*/

int		node__parent_ispipe(t_node *node)
{
	return (node && node->parent && node->parent->type == SEP &&
		node->parent->sep->type == PIPE);
}


/*
** THIS FUNCTION OPEN A NEW PIPE AND ASSIGN THE WRITE SIDE TO THE LEFT CHILD
** AND THE READ SIDE TO THE RIGHT ONE.
**
** IT CLOSE THE STDOUT FD OF THE LEFT CHILD IF DIFFERENT STDOUT (1)
** IT CLOSE THE STDIN FD OF THE RIGHT CHILD IF DIFFERENT STDIN (0)
**
** RUN THE LEFT CHILD THEN CLOSE THE WRITE SIDE OF THE PIPE CAUSE THE LEFT CHILD
** HAS FINISHED TO USE IT
**
** RUN THE RIGHT CHILD THEN CLOSE THE READ SIDE OF THE PIPE CAUSE THE RIGHT
** CHILD HAS FINISHED TO USE IT
*/


int		node__pipe_handle(t_node *ppln)
{
	int	sloc;

	sloc = 0;
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
	// waitpid(ppln->left->pid, &sloc, WUNTRACED);
	// waitpid(ppln->right->pid, &sloc, WUNTRACED);
	return (sloc);
}

/*
** THIS FUNCTION RUN THE LEFT CHILD OF THE DBL_AND NODE THEN WAIT FOR ITS END
** IF THE LEFT CHILD SUCCEEDED SO RUN THE RIGHT CHILD AND WAIT FOR ITS END
** RETURN THE RETURN VALUE OF THE LEFT CHILD IF IT HAS FAILED ELSE IT RETURN
** THE RETURN OF THE RIGHT CHILD ELSE
*/

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

	sloc = 0;
	node__controller(cmd_sep->left);
	waitpid(cmd_sep->left->pid, &sloc, WUNTRACED);
	if (sloc != 0)
	{
		node__controller(cmd_sep->right);
		waitpid(cmd_sep->right->pid, &sloc, WUNTRACED);
	}
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

	sloc = 0;
	node__controller(cmd_sep->left);
	waitpid(cmd_sep->left->pid, &sloc, WUNTRACED);
	if (cmd_sep->right)
	{
		node__controller(cmd_sep->right);
		waitpid(cmd_sep->right->pid, &sloc, WUNTRACED);
	}
	return (WEXITSTATUS(sloc));
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
