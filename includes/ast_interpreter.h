/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_interpreter.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 03:39:57 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/05 02:38:13 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_INTERPRETER
# define AST_INTERPRETER
# include <minishell.h>
# define PIPE_READ			0 // the side of the pipe where the cmd will read
# define PIPE_WRITE			1 // the side of the pipe where the cmd will write
# define STDIN				0 // where the cmd will read
# define STDOUT				1 // where the cmd will write
/*
** fd[STDOUT] : [PIPE_READ]   [PIPE_WRITE]
** fd[STDIN]  : [PIPE_READ]   [PIPE_WRITE]
**
** child reads on fd[STDIN][PIPE_READ]
**  and writes on fd[STDOUT][PIPE_WRITE]
**
** parent reads on fd[STDOUT][PIPE_READ]
**   and writes on fd[STDIN][PIPE_WRITE]
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
	ERR_OPEN,
	ERR_PIPE
}					t_asti_error_opt;
typedef enum		e_waitnclose_opt
{
	ADD,
	CLOSE
}					t_waitnclose_opt;
int					ast_interpreter(t_node *ast);
int					node__controller(t_node *node);
#endif
