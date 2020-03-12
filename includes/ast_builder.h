/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 02:37:21 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/12 18:48:07 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_BUILDER_H
# define AST_BUILDER_H
# include <minishell.h>

typedef enum		e_error_code
{
	UNEXPECTED_TOKEN
}					t_error_code;
typedef enum		e_nodetype
{
	CMD,
	SEP
}					t_nodetype;
typedef enum		e_ast_token
{
	AST_REDIR,
	AST_WORD,
	AST_SEP
}					t_ast_token;
typedef enum		e_opt_del_node
{
	NORMAL,
	RECURCIVLY
}					t_opt_del_node;

/*
** *****************************************************************************
** **** NODE STRUCTURE *********************************************************
** *****************************************************************************
*/

typedef struct		s_node
{
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;
	int				type;
	t_token			*av;
	t_token			*redir;
	t_token			*file;
	int				stdin;
	int				stdout;
	int				pid;
	t_token			*sep;
	int				pipe_ltor[2];
}					t_node;

typedef struct		s_astb
{
	t_node			*ast;
	t_lexer			*lex;
	t_token			*current_token;
	t_token			*prev_token;
	t_node			*tree_pos;
}					t_astb;
/*
** *****************************************************************************
** **** ast__add_toast.c *******************************************************
** *****************************************************************************
*/
int					add_token_into_node(
	t_astb *tool, t_token **tokendest, t_ast_token type);
void				set_root_to_node(t_astb *tool, t_node *node);
void				search_place_node(
	t_astb *tool, t_node *node, t_token_type_m type);
int					add_to_ast(t_astb *tool, t_node *node);

/*
** *****************************************************************************
** **** ast__eat.c *************************************************************
** *****************************************************************************
*/
int					eat(t_astb *tool, t_token_type_m type);

/*
** *****************************************************************************
** **** ast__process.c *********************************************************
** *****************************************************************************
*/
int					process_call_next(t_astb *tool, t_node **sep);
int					process(t_astb *tool);

/*
** *****************************************************************************
** **** ast__builder.c *********************************************************
** *****************************************************************************
*/
int					astb_error(t_astb *tool, int opt);
t_node				*node__new(t_nodetype type);
void				node__del(t_node **node, int opt);
int					init_tool(t_astb *tool, int sloc);
t_node				*ast_builder(int sloc);

/*
** *****************************************************************************
** *****************************************************************************
** *****************************************************************************
*/
#endif
