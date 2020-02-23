/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 00:31:14 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/23 16:09:18 by tharchen         ###   ########.fr       */
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

void		ast__add_node_word(t_ast *ast, t_token token)
{
	
}

void		ast__add_node_redirection(t_ast *ast, t_token token)
{

}

void		ast__add_node_cmdsep(t_ast *ast, t_token token)
{

}

void		ast__add_node_subshell(t_ast *ast, t_token token)
{

}


void		ast__add_node(t_ast *ast, t_token token)
{
	if (token__istype(token, WORD|SQUOTE|DQUOTE|STAR|BSLASH|QUESMARK|DOLLAR|SLASH))	// WORDS
		ast__add_node_word(ast, token);
	if (token__istype(token, REDIREC_IN|REDIREC_OUT|DREDIREC_OUT))					// REDIRECTIONS
		ast__add_node_redirection(ast, token);
	if (token__istype(token, DBL_AND|SGL_AND|DBL_OR|PIPE|SEMICON))					// CMD SEP
		ast__add_node_cmdsep(ast, token);
	if (token__istype(token, LPAREN|RPAREN))										// SUBSHELL
		ast__add_node_subshell(ast, token);
	if (token__istype(token, ERR|EOT|SPACE|PASS|NONE))								// UNEXPECTED
		ast__error();
}



























