/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 00:31:14 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/18 14:16:31 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast		ast__new(t_lex lex)
{
	t_ast	new;

	new.lex = lex;
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
