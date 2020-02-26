/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__tokovore.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 06:29:24 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/27 00:03:04 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS__TOKOVORE_H
# define CLASS__TOKOVORE_H
# include <minishell.h>
# define TMPS		50
typedef enum		e_bool_return
{
	CONTINUE,
	BREAK
}					t_bool_return;
typedef enum		e_tokerror
{
	UNEXPECTED_TOKEN
}					t_tokerror;
typedef enum				e_selector
{
	NODE_EOT	= 0x0,
	NODE_ERR	= 0x1,
	NODE_REDIR	= 0x2,
	NODE_CMD	= 0x4,
	NODE_SEP	= 0x8
}							t_selector;
typedef enum				e_token_supertype
{
	ST_ERR		= 0x0,
	ST_WORD		= 0x1,
	ST_REDIR	= 0x2,
	ST_SEP		= 0x4,
	ST_EOT		= 0x8
}							t_token_supertype;
typedef struct				s_type_to_supertype
{
	t_token_type_m			type;
	t_token_supertype		supertype;
}							t_type_to_supertype;

extern t_type_to_supertype	g_stype[NB_DEFINED_TOKEN];

/*
** ****************************************************************************
** *
** *         NODE BODY PATTERNS
** *
** ****************************************************************************
*/

typedef struct				s_node_eot
{
/*
** links
*/
	struct s_node_eot		*next;
	struct s_node_eot		*prev;
/*
** 	pattern hangs
*/
	int						selector;
/*
** 	AST datas
*/
	t_token					eot;
/*
** 	INTERPRETER datas
*/

}							t_node_eot;

typedef struct				s_subnode_redir
{
/*
** links
*/
	struct s_subnode_redir	*next;
	struct s_subnode_redir	*prev;
/*
** 	pattern hangs
*/
	int						selector;
/*
** 	AST datas
*/
	t_token					type;
	t_token					file;
/*
** 	INTERPRETER datas
*/
	int						fd;

}							t_subnode_redir;

typedef struct				s_node_cmd
{
/*
** links
*/
	struct s_node_cmd		*next;
	struct s_node_cmd		*prev;
/*
** 	pattern hangs
*/
	int						selector;
/*
** 	AST datas
*/
	t_token					cmd;
	t_token					*arg; // allocated list
	t_subnode_redir			*redir; // allocated list
/*
** 	INTERPRETER datas
*/
	int						fd_in; // where the cmd reads
	int						fd_out; // where the cmd writes
	char					**av; // av[0] == process name // av[1 ~ N] args..
	int						sloc; // return of the cmd
}							t_node_cmd;

typedef struct				s_node_sep
{
/*
** links
*/
	struct s_node_sep		*next;
	struct s_node_sep		*prev;
/*
** 	pattern hangs
*/
	int						selector;
/*
** 	AST datas
*/
	t_token					sep;
/*
** 	INTERPRETER datas
*/

}							t_node_sep;

typedef struct				s_node_pattern
{
/*
** links
*/
	struct s_node_pattern	*next;
	struct s_node_pattern	*prev;
/*
** 	pattern hangs
*/
	int						selector;
}							t_node_pattern;

/*
** ****************************************************************************
** *
** *         NODES
** *
** ****************************************************************************
*/

typedef struct				s_node
{
	struct s_node			*right;
	struct s_node			*left;
	struct s_node			*parent;
	t_node_pattern			*body;
}							t_node;

typedef struct				s_ast
{
	t_node_eot				eot;
	t_node					*tree; // allocated tree
	t_node_pattern			*last_recording;
	t_lexer					lex;
	int						nb_node;
	t_token					current_token;
	t_token					next_token;
	t_token					prev_token;
	int						is_next_token_full;
}							t_ast;
t_ast						*toko_master(int sloc);
void						toko_cmd(t_ast *ast);
#endif
