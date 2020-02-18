/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__ast.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 00:40:38 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/18 02:04:14 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS__AST_H
# define CLASS__AST_H
typedef struct		s_ast
{
	t_lex			lex;
	t_node			*tree;
}					t_ast;
#endif
