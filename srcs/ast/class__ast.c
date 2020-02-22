/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 00:31:14 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/22 16:39:53 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast		ast__new(void)
{
	t_ast	new;

	new.tree = NULL;
	return (new);
}

void		ast__del(t_ast ast)
{
	node__del(ast.tree);
}

void		ast__print()
{
	// TODO
}

// ************************************************************************** //

void		ast__new_tree(t_ast *ast, t_token token)
{
	if (token__istype(token, ))
}
