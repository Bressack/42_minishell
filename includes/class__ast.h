/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__ast.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 00:40:38 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/24 13:18:52 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS__AST_H
# define CLASS__AST_H
# include <minishell.h>
typedef struct		s_ast
{
	t_lexer			lex;
	t_node			*tree;
	t_node			*last_added;
}					t_ast;
t_ast				ast__new(t_lexer lex);
void				ast__del(t_ast ast);
void				ast__print();
void				ast__new_tree(t_ast *ast, t_token token);
#endif
