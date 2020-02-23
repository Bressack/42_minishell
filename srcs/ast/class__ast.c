/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 00:31:14 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/23 20:33:13 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_ast		ast__new(t_lexer lex)
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

void		ast__error(int err_type, void *arg)
{
	if (err_type == AST__UNEXPECTED_TOKEN)
		ft_dprintf(2, "error: unexpected token \'%s\'\n", (char *)arg);
}

void		ast__print_deep(t_node *n, int deep)
{
	printf("%*s%s\n", deep * 2, "", n->token.value);
	ast__print_deep(n->left, deep + 1);
	ast__print_deep(n->right, deep + 1);
}

void		ast__print(t_ast ast)
{
	if (!ast.node)
		printf("error: empty AST\n");
	else
	{
		printf("AST read in infix\n");
		printf("expr: %s\n", ast.expr);
		ast__print_deep(ast, 0);
	}
}

// ************************************************************************** //


t_token		ast__token_eater(t_ast ast, t_token_type expected_token_type)
{
	t_token	token_crumbs;

	token_crumbs = lexer__get_next_token(&ast.lex);
	if (!token__istype(token_crumbs, expected_token_type))
		ast__error(AST__UNEXPECTED_TOKEN,
		(char *)token__get_type_str(token_crumbs));
	return (token_crumbs);
}

void		ast__expr()
{
	
}











