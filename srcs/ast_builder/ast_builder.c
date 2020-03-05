/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 18:31:13 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/05 01:06:17 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		astb_error(t_astb *tool, int opt)
{
	if (opt == UNEXPECTED_TOKEN)
	{
		if (tool->current_token->type == EOT)
			ft_dprintf(2, "minishell: syntax error: unexpected end of file\n");
		else
			ft_dprintf(2,
				"minishell: syntax error near unexpected token \'%s\'\n",
				tool->current_token->value);
	}
	return (ERROR);
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

/*
** int		print_node(t_node *n)
** {
** 	ft_printf("[ NODE   "C_G_YELLOW"%-4s"C_RES" | "C_G_GREEN"%-14p"C_RES" ] {["
** 		C_G_CYAN"%4s"C_RES"] <- ["C_G_RED"%4s"C_RES"] -> ["C_G_CYAN"%4s"
** 		C_RES"]}",
** 		n ? n->type == CMD ? "CMD" : "SEP" : "NULL",
** 		n,
** 		n && n->left ? n->left->type == CMD ? n->left->av->value : n->left->sep
** 		->value : "NULL",
** 		n ? n->type == CMD ? n->av->value : n->sep->value : "NULL",
** 		n && n->right ? n->right->type == CMD ? n->right->av->value : n->right->
** 		sep->value : "NULL"
** 	);
** 	n = n ? n->parent : NULL;
** 	ft_printf(" "C_G_MAGENTA"####"C_RES" [ PARENT "C_G_YELLOW"%-4s"C_RES" | "
** 		C_G_GREEN"%-14p"C_RES" ] {["C_G_CYAN"%4s"C_RES"] <- ["C_G_RED"%4s"C_RES
** 		"] -> ["C_G_CYAN"%4s"C_RES"]}",
** 		n ? n->type == CMD ? "CMD" : "SEP" : "NULL",
** 		n,
** 		n && n->left ? n->left->type == CMD ? n->left->av->value : n->left->sep
** 		->value : "NULL",
** 		n ? n->type == CMD ? n->av->value : n->sep->value : "NULL",
** 		n && n->right ? n->right->type == CMD ? n->right->av->value : n->right->
** 		sep->value : "NULL"
** 	);
** 	ft_printf("\n");
** 	return (0);
** }
**
** void	print_ast(t_node *n, int deep)
** {
** 	!deep ? ft_printf("\n") : 0;
** 	if (!n)
** 		ft_printf("("C_G_RED"null"C_RES")\n");
** 	else
** 	{
** 		if (n->type == CMD)
** 		{
** 			if (!n->av)
** 				ft_printf(""C_G_RED"null"C_RES);
** 			else
** 				for (t_token *tmp = n->av ; tmp ; tmp = tmp->next)
** 					ft_printf("{"C_G_YELLOW"%s"C_RES"} ", tmp->value);
** 			ft_printf("\n");
** 		}
** 		else
** 		{
** 			ft_printf("["C_G_CYAN"%s"C_RES"]\n", n->sep ? n->sep->value :
** 			C_G_RED"null"C_RES);
** 			for (int i = 0; i < deep; i++)
** 				ft_printf("|   ");
** 			ft_printf("L - "), print_ast(n->left, deep + 1);
** 			for (int i = 0; i < deep; i++)
** 				ft_printf("|   ");
** 			ft_printf("R - "), print_ast(n->right, deep + 1);
** 		}
** 	}
** }
*/

int		eat(t_astb *tool, t_token_type_m type)
{
	if (!token__istype(tool->current_token, type))
		return (astb_error(tool, UNEXPECTED_TOKEN));
	tool->prev_token = tool->current_token;
	if ((tool->current_token = lexer__get_next_token(tool->lex)) == NULL)
		return (ERROR);
	return (SUCCESS);
}

int		add_token_into_node(t_astb *tool, t_token **tokendest, t_ast_token type)
{
	if (type == AST_REDIR &&
		eat(tool, token__isredir(tool->current_token)) == ERROR)
		return (ERROR);
	if (type == AST_WORD &&
		eat(tool, token__isword(tool->current_token)) == ERROR)
		return (ERROR);
	if (type == AST_SEP &&
		eat(tool, token__issep(tool->current_token)) == ERROR)
		return (ERROR);
	ft_add_node_end_np((t_pnp **)tokendest, (t_pnp *)tool->prev_token);
	return (SUCCESS);
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

int		add_to_ast(t_astb *tool, t_node *node)
{
	if (tool->ast == NULL)
	{
		if (node->type == SEP)
			return (astb_error(tool, UNEXPECTED_TOKEN));
		set_root_to_node(tool, node);
	}
	else
	{
		if (node->type == CMD)
		{
			tool->tree_pos->right = node;
			node->parent = tool->tree_pos;
			node->stdin = STDOUT;
			node->stdout = STDIN;
		}
		else if (node->type == SEP)
		{
			if (!node->sep)
				return (astb_error(tool, UNEXPECTED_TOKEN));
			if (token__istype(node->sep, PIPE))
				search_place_node(tool, node, DBL_AND | DBL_OR | SEMICON);
			else if (token__istype(node->sep, DBL_AND | DBL_OR))
				search_place_node(tool, node, SEMICON);
			else if (token__istype(node->sep, SEMICON))
				set_root_to_node(tool, node);
			tool->tree_pos = node;
		}
	}
	return (SUCCESS);
}

/*
** t_node *cmd; -> new empty node command
** t_node *sep; -> new empty node separator
** Send an error if the first token is a sep. a command cannot begin by a sep
**
** init the node cmd
** loop on each next token could be a redirection ['&&' | '||' | '|' WORD] or an
** arg (cmd name then args)
**
** handle redir (a redir is a redir token following by a WORD (its file)
**
** add the REDIR token into the node and eat the current_token to reveal the
** next one
** add the WORD token into the node and eat the current_token to reveal the next
** one
**
** handle args (cmd och args ...)
** add the WORD token into the node and eat the current_token to reveal the next
** one
**
** add the node cmd to the ast. A cmd is always added to the right child of
** tree_pos (tree_pos is the last position where a node was added)
** if a sep is present after the cmd, then add it to the sep node then into the
**< ast
**
** init the node sep
**
** add the node sep to the ast.
** rerun process to the next cmd
*/

int		process(t_astb *tool)
{
	t_node		*cmd;
	t_node		*sep;

	if (token__issep(tool->current_token) || token__iseot(tool->current_token))
		return (astb_error(tool, UNEXPECTED_TOKEN));
	cmd = new_node(CMD);
	while (token__isword(tool->current_token) ||
		token__isredir(tool->current_token))
	{
		if (token__isredir(tool->current_token))
		{
			if (add_token_into_node(tool, &cmd->redir, AST_REDIR) == ERROR)
				return (ERROR);
			if (add_token_into_node(tool, &cmd->file, AST_WORD) == ERROR)
				return (ERROR);
			continue ;
		}
		if (add_token_into_node(tool, &cmd->av, AST_WORD) == ERROR)
			return (ERROR);
	}
	add_to_ast(tool, cmd);
	if (token__issep(tool->current_token))
	{
		sep = new_node(SEP);
		if (add_token_into_node(tool, &sep->sep, AST_SEP) == ERROR)
			return (ERROR);
		add_to_ast(tool, sep);
		if (process(tool) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int		init_tool(t_astb *tool, int sloc)
{
	ft_bzero(tool, sizeof(t_astb));
	if (!(tool->lex = lexer__new(sloc)))
		return (ERROR);
	if ((tool->current_token = lexer__get_next_token(tool->lex)) == NULL)
		return (ERROR);
	if (!tool->current_token || tool->current_token->type == EOT)
	{
		lexer__del(&tool->lex);
		return (ERROR); // line empty
	}
	tool->prev_token = NULL;
	tool->tree_pos = NULL;
	tool->ast = NULL;
	return (SUCCESS);
}

t_node	*ast_builder(int sloc)
{
	t_astb		tool;

	if (init_tool(&tool, sloc) != ERROR && process(&tool) != ERROR)
	{
		lexer__del(&tool.lex);
		return (tool.ast);
	}
	lexer__del(&tool.lex);
	return (NULL);
}
