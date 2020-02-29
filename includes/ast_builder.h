/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 02:37:21 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/29 16:00:55 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_BUILDER
# define AST_BUILDER
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

typedef struct		s_node
{
/*
** 	LINKS
*/
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;
/*
** 	node type (cmd | sep)
*/
	int				type;
/*
** 	cmd data
*/
	t_token			*av;
	t_token			*redir;
	t_token			*file;
/*
** 	sep data
*/
	t_token			*sep;
}					t_node;

typedef struct		s_astb
{
	t_node			*ast;
	t_lexer			*lex;
	t_token			*current_token;
	t_token			*prev_token;
	t_node			*tree_pos;
}					t_astb;
t_node				*ast_builder(int sloc);
#endif