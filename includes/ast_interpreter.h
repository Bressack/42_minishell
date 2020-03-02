/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_interpreter.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 03:39:57 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/02 05:48:58 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_INTERPRETER
# define AST_INTERPRETER
# include <minishell.h>
# define PIPE_READ		0 // the side of the pipe where the cmd will read
# define PIPE_WRITE		1 // the side of the pipe where the cmd will write
# define ISTDOUT		0 // where the cmd will write
# define ISTDIN			1 // where the cmd will read
/*
** fd[ISTDOUT] : [PIPE_READ]   [PIPE_WRITE]
** fd[ISTDIN]  : [PIPE_READ]   [PIPE_WRITE]
**
** child reads on fd[ISTDIN][PIPE_READ]
**  and writes on fd[ISTDOUT][PIPE_WRITE]
**
** parent reads on fd[ISTDOUT][PIPE_READ]
**   and writes on fd[ISTDIN][PIPE_WRITE]
**
** yes it's weird for the parent side,
** but more easy for the child process.
*/
typedef enum		e_ast_interpreter_opt
{
	ASTI_SUCCESS,
	ASTI_FAILURE
}					t_ast_interpreter_opt;
typedef enum		e_asti_error_opt
{
	OPEN_ERROR
}					t_asti_error_opt;
int					ast_interpreter(t_node *ast);
int					node__controller(t_node *node);
#endif