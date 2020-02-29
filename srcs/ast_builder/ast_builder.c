/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 02:28:56 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/29 16:36:50 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	astb_error(t_astb *tool, int opt)
{
	printf(TEST);
	if (opt == UNEXPECTED_TOKEN)
		ft_dprintf(2, "error: unexpected token \'%s\' after \'%s\'\n",
			tool->current_token->value, tool->prev_token->value);
	exit(-1);
}

int		print_node(t_node *n)
{
	printf("[ NODE   "C_G_YELLOW"%-4s"C_RES" | "C_G_GREEN"%-14p"C_RES" ] {["C_G_CYAN"%4s"C_RES"] <- ["C_G_RED"%4s"C_RES"] -> ["C_G_CYAN"%4s"C_RES"]}",
		n ? n->type == CMD ? "CMD" : "SEP" : "NULL",
		n,
		n && n->left ? n->left->type == CMD ? n->left->av->value : n->left->sep->value : "NULL",
		n ? n->type == CMD ? n->av->value : n->sep->value : "NULL",
		n && n->right ? n->right->type == CMD ? n->right->av->value : n->right->sep->value : "NULL"
	);
	n = n ? n->parent : NULL;
	printf(" "C_G_MAGENTA"####"C_RES" [ PARENT "C_G_YELLOW"%-4s"C_RES" | "C_G_GREEN"%-14p"C_RES" ] {["C_G_CYAN"%4s"C_RES"] <- ["C_G_RED"%4s"C_RES"] -> ["C_G_CYAN"%4s"C_RES"]}",
		n ? n->type == CMD ? "CMD" : "SEP" : "NULL",
		n,
		n && n->left ? n->left->type == CMD ? n->left->av->value : n->left->sep->value : "NULL",
		n ? n->type == CMD ? n->av->value : n->sep->value : "NULL",
		n && n->right ? n->right->type == CMD ? n->right->av->value : n->right->sep->value : "NULL"
	);
	printf("\n");
	return (0);
}

void	eat(t_astb *tool, t_token_type_m type)
{
	if (!token__istype(tool->current_token, type))
		printf(TEST), printf(TEST), astb_error(tool, UNEXPECTED_TOKEN);
	tool->prev_token = tool->current_token;
	tool->current_token = lexer__get_next_token(tool->lex);
}

t_node	*new_node(t_nodetype type)
{
	t_node		*new;

	new = try_malloc(sizeof(t_node), _FL_);
	new->type = type;
	return (new);
}

void	add_token_into_node(t_astb *tool, t_token **tokendest, t_ast_token type)
{
	if (type == AST_REDIR)
		eat(tool, token__isredir(tool->current_token));
	if (type == AST_WORD)
		eat(tool, token__isword(tool->current_token));
	if (type == AST_SEP)
		eat(tool, token__issep(tool->current_token));
	ft_add_node_end_np((t_pnp **)tokendest, (t_pnp *)tool->prev_token);
}

void	set_root_to_node(t_astb *tool, t_node *node)
{
	node->left = tool->ast;
	node->right = NULL;
	node->parent = NULL;
	if (tool->ast)
	{
		tool->ast->parent = node;
		tool->tree_pos = node;
	}
	tool->ast = node;
}

void	search_place_node(t_astb *tool, t_node *node, t_token_type_m type)
{
	while (tool->tree_pos && (tool->tree_pos->type == CMD ||
		!token__istype(tool->tree_pos->sep, type)))
	{
		dprintf(1, ""C_G_WHITE"tree_pos is on       "C_RES);
		print_node(tool->tree_pos);
		dprintf(1, ""C_G_WHITE"tree_pos is going on "C_RES);
		print_node(tool->tree_pos->parent);
		tool->tree_pos = tool->tree_pos->parent;
	}
	dprintf(1, ""C_G_WHITE"tree_pos is now on   "C_RES);
	print_node(tool->tree_pos);
	if (!tool->tree_pos)
		set_root_to_node(tool, node);
	else
	{
		node->left = tool->tree_pos->right;
		tool->tree_pos->right = NULL;
		node->right = NULL;
		node->parent = tool->tree_pos;
		tool->tree_pos->left = node;
	}
}

void	add_to_ast(t_astb *tool, t_node *node)
{
	/*
** 	printf("tree_pos: "C_G_GREEN"%p"C_RES" ["C_G_CYAN"type:"C_RES" "C_G_RED"%s"C_RES"] ["C_G_CYAN"value:"C_RES" "C_G_RED"%s"C_RES"]\n",
** 	tool->tree_pos,
** 	tool->tree_pos ? tool->tree_pos->type == CMD ? "CMD" : "SEP" : 0,
** 	tool->tree_pos ? tool->tree_pos->type == CMD ? tool->tree_pos->av->value : tool->tree_pos->sep->value : 0
** 	);
** 	printf("node    : "C_G_GREEN"%p"C_RES" ["C_G_CYAN"type:"C_RES" "C_G_RED"%s"C_RES"] ["C_G_CYAN"value:"C_RES" "C_G_RED"%s"C_RES"]\n",
** 	node,
** 	node ? node->type == CMD ? "CMD" : "SEP" : 0,
** 	node ? node->type == CMD ? node->av->value : node->sep->value : 0
** 	);
*/
	if (tool->ast == NULL)
	{
		if (node->type == SEP)
			printf(TEST), astb_error(tool, UNEXPECTED_TOKEN);
		set_root_to_node(tool, node);
	}
	else
	{
		// if (!tool->tree_pos)
		// 	printf(TEST), astb_error(tool, UNEXPECTED_TOKEN);
		if (node->type == CMD)
		{
			tool->tree_pos->right = node;
			node->parent = tool->tree_pos;
		}
		else if (node->type == SEP)
		{
			if (!node->sep)
				printf(TEST), astb_error(tool, UNEXPECTED_TOKEN);
			if (token__istype(node->sep, PIPE))
				search_place_node(tool, node, DBL_AND | DBL_OR | SEMICON);
			else if (token__istype(node->sep, DBL_AND | DBL_OR))
				search_place_node(tool, node, SEMICON);
			else if (token__istype(node->sep, SEMICON))
				set_root_to_node(tool, node);
			tool->tree_pos = node;
		}
	}
	dprintf(1, ""C_G_WHITE"node                 "C_RES);
	print_node(node);
}

void	print_ast(t_node *n, int deep)
{
	printf("%*s", deep * 4, "");
	print_node(n);
	n->left ? print_ast(n->left, deep + 1) : 0;
	n->right ? print_ast(n->right, deep + 1) : 0;
}

void	process(t_astb *tool)
{
	t_node		*cmd;
	t_node		*sep;

	if (token__issep(tool->current_token))
		printf(TEST), astb_error(tool, UNEXPECTED_TOKEN);
	cmd = new_node(CMD);
	while (token__isword(tool->current_token) ||
		token__isredir(tool->current_token))
	{
		if (token__isredir(tool->current_token))
		{
			add_token_into_node(tool, &cmd->redir, AST_REDIR);
			add_token_into_node(tool, &cmd->file, AST_WORD);
			continue ;
		}
		add_token_into_node(tool, &cmd->av, AST_WORD);
	}
	add_to_ast(tool, cmd);
	if (token__issep(tool->current_token))
	{
		sep = new_node(SEP);
		add_token_into_node(tool, &sep->sep, AST_SEP);
		add_to_ast(tool, sep);
		process(tool);
	}
}

int		init_tool(t_astb *tool, int sloc)
{
	tool->lex = lexer__new(sloc);
	tool->current_token = lexer__get_next_token(tool->lex);
	if (!tool->current_token || tool->current_token->type == EOT)
	{
		lexer__del(&tool->lex);
		return (-1);
	}
	tool->prev_token = NULL;
	tool->tree_pos = NULL;
	tool->ast = NULL;
	return (0);
}

t_node	*ast_builder(int sloc)
{
	t_astb		tool;

	if (init_tool(&tool, sloc) == -1)
		return (NULL);
	process(&tool);
	lexer__del(&tool.lex);
	printf("\n===============================================\n");
	print_ast(tool.ast, 0);
	return (tool.ast);
}










