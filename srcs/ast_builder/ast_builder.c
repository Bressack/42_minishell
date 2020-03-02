/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 02:28:56 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/02 06:33:53 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	astb_error(t_astb *tool, int opt)
{
	if (opt == UNEXPECTED_TOKEN)
	{
		if (tool->current_token->type == EOT)
			ft_dprintf(2, "error: unexpected \'end of file\'");
		else
			ft_dprintf(2, "error: unexpected token \'%s\'",
			tool->current_token->value);
		if (tool->prev_token)
			ft_dprintf(2, " after \'%s\'", tool->prev_token->value);
		ft_dprintf(2, "\n");
	}
	exit(-1);
}

t_node	*new_node(t_nodetype type)
{
	t_node		*new;

	new = try_malloc(sizeof(t_node), _FL_);
	new->type = type;
	return (new);
}

void	del_node(t_node **node, int opt)
{
	token__list_del(&(*node)->av);
	token__list_del(&(*node)->redir);
	token__list_del(&(*node)->sep);
	if (opt == RECURCIVLY)
	{
		(*node)->left ? del_node(&(*node)->left, opt) : 0;
		(*node)->right ? del_node(&(*node)->right, opt) : 0;
	}
	try_free_((void **)node, _FL_);
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

void	print_ast(t_node *n, int deep)
{
	!deep ? printf("\n") : 0;
	if (!n)
		printf("("C_G_RED"null"C_RES")\n");
	else
	{
		if (n->type == CMD)
		{
			if (!n->av)
				printf(""C_G_RED"null"C_RES);
			else
				for (t_token *tmp = n->av ; tmp ; tmp = tmp->next)
					printf("{"C_G_YELLOW"%s"C_RES"} ", tmp->value);
			printf("\n");
		}
		else
		{
			printf("["C_G_CYAN"%s"C_RES"]\n", n->sep ? n->sep->value : C_G_RED"null"C_RES);
			for (int i = 0; i < deep; i++)
				printf("|   ");
			printf("L - "), print_ast(n->left, deep + 1);
			for (int i = 0; i < deep; i++)
				printf("|   ");
			printf("R - "), print_ast(n->right, deep + 1);
		}
	}
}

void	eat(t_astb *tool, t_token_type_m type)
{
	if (!token__istype(tool->current_token, type))
		astb_error(tool, UNEXPECTED_TOKEN);
	tool->prev_token = tool->current_token;
	tool->current_token = lexer__get_next_token(tool->lex);
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
		tool->tree_pos = tool->tree_pos->parent;
	if (!tool->tree_pos)
		set_root_to_node(tool, node);
	else
	{
		node->left = tool->tree_pos->right;
		node->right = NULL;
		node->parent = tool->tree_pos;
		tool->tree_pos->right = node;
	}
}

void	add_to_ast(t_astb *tool, t_node *node)
{
	if (tool->ast == NULL)
	{
		node->type == SEP ? astb_error(tool, UNEXPECTED_TOKEN) : 0;
		set_root_to_node(tool, node);
	}
	else
	{
		if (node->type == CMD)
		{
			tool->tree_pos->right = node;
			node->parent = tool->tree_pos;
			node->stdio[ISTDOUT] = ISTDOUT;
			node->stdio[ISTDIN] = ISTDIN;
		}
		else if (node->type == SEP)
		{
			if (!node->sep)
				astb_error(tool, UNEXPECTED_TOKEN);
			if (token__istype(node->sep, PIPE))
				search_place_node(tool, node, DBL_AND | DBL_OR | SEMICON);
			else if (token__istype(node->sep, DBL_AND | DBL_OR))
				search_place_node(tool, node, SEMICON);
			else if (token__istype(node->sep, SEMICON))
				set_root_to_node(tool, node);
			tool->tree_pos = node;
		}
	}
	// dprintf(1, ""C_G_WHITE"node                 "C_RES);
	// print_node(node);
}

void	process(t_astb *tool)
{
	t_node		*cmd;                                                           // t_node *cmd; -> new empty node command
	t_node		*sep;                                                           // t_node *sep; -> new empty node separator

	if (token__issep(tool->current_token) || token__iseot(tool->current_token)) // Send an error if the first token is a sep. a command cannot begin by a sep
		astb_error(tool, UNEXPECTED_TOKEN);                                     //
	cmd = new_node(CMD);                                                        // init the node cmd
	while (token__isword(tool->current_token) ||                                // loop on each next token could be a redirection ['&&' | '||' | '|' WORD] or an
		token__isredir(tool->current_token))                                    // arg (cmd name then args)
	{                                                                           //
		if (token__isredir(tool->current_token))                                // handle redir (a redir is a redir token following by a WORD (its file)
		{                                                                       //
			add_token_into_node(tool, &cmd->redir, AST_REDIR);                  // add the REDIR token into the node and eat the current_token to reveal the next one
			add_token_into_node(tool, &cmd->file, AST_WORD);                    // add the WORD token into the node and eat the current_token to reveal the next one
			continue ;                                                          //
		}                                                                       // handle args (cmd och args ...)
		add_token_into_node(tool, &cmd->av, AST_WORD);                          // add the WORD token into the node and eat the current_token to reveal the next one
	}                                                                           //
	add_to_ast(tool, cmd);                                                      // add the node cmd to the ast. A cmd is always added to the right child of tree_pos (tree_pos is the last position where a node was added)
	if (token__issep(tool->current_token))                                      // if a sep is present after the cmd, then add it to the sep node then into the ast
	{                                                                           //
		sep = new_node(SEP);                                                    // init the node sep
		add_token_into_node(tool, &sep->sep, AST_SEP);                          //
		add_to_ast(tool, sep);                                                  // add the node sep to the ast.
		process(tool);                                                          // rerun process to the next cmd
	}                                                                           //
}

int		init_tool(t_astb *tool, int sloc)
{
	ft_bzero(tool, sizeof(t_astb));
	tool->lex = lexer__new(sloc);
	tool->current_token = lexer__get_next_token(tool->lex);
	if (!tool->current_token || tool->current_token->type == EOT ||
		!ft_strcmp(tool->lex->line, "exit"))
	{
		lexer__del(&tool->lex);
		return (-1); // line empty
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
	return (tool.ast);
}










