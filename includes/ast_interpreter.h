/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_interpreter.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 03:39:57 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/09 02:52:34 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_INTERPRETER_H
# define AST_INTERPRETER_H
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
typedef struct			s_pid_save
{
	struct s_pid_save	*next;
	struct s_pid_save	*prev;
	pid_t				pid;
}						t_pid_save;
typedef enum			e_ast_interpreter_opt
{
	ASTI_SUCCESS,
	ASTI_FAILURE
}						t_ast_interpreter_opt;
typedef enum			e_asti_error_opt
{
	ERR_OPEN,
	ERR_PIPE
}						t_asti_error_opt;
typedef enum			e_waitnclose_opt
{
	ADD,
	WAIT
}						t_waitnclose_opt;

/*
** ast_interpreter.c
*/
int						asti_error(char *name, int opt);
int						node__cmd_controller(t_node *cmd);
int						node__controller(t_node *node);
int						ast_interpreter(t_node *ast);

/*
** node__sep_controller.c
*/
int						node__dbl_and_handle(t_node *cmd_sep);
int						node__dbl_or_handle(t_node *cmd_sep);
int						node__semicon_handle(t_node *cmd_sep);
int						node__sep_controller(t_node *sep);

/*
** node__pipe_handle.c
*/
int						node__parent_ispipe(t_node *node);
int						waitallpipes(pid_t pid, int opt);
int						node__pipe_handle(t_node *ppln);

/*
** redir_handle.c
*/
int						redir_handle__each(
	t_node *cmd, t_token *tmp_redir,t_token *tmp_file);
int						redir_handle(t_node *cmd);
#endif
