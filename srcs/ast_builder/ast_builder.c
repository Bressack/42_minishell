/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 18:31:13 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/09 04:13:23 by tharchen         ###   ########.fr       */
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

t_node	*node__new(t_nodetype type)
{
	t_node		*new;

	new = mmalloc(sizeof(t_node));
	new->type = type;
	new->stdin = STDIN;
	new->stdout = STDOUT;
	return (new);
}

void	node__del(t_node **node, int opt)
{
	token__list_del(&(*node)->av);
	token__list_del(&(*node)->redir);
	token__list_del(&(*node)->sep);
	if (opt == RECURCIVLY)
	{
		(*node)->left ? node__del(&(*node)->left, opt) : 0;
		(*node)->right ? node__del(&(*node)->right, opt) : 0;
	}
	mfree((void **)node);
}

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
		if (node->type == CMD && (tool->tree_pos->right = node))
			node->parent = tool->tree_pos;
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

int		process_call_next(t_astb *tool, t_node **sep)
{
	if (token__issep(tool->current_token))
	{
		*sep = node__new(SEP);
		if (add_token_into_node(tool, &(*sep)->sep, AST_SEP) == ERROR)
			return (ERROR);
		add_to_ast(tool, *sep);
		if (process(tool) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int		process(t_astb *tool)
{
	t_node		*cmd;
	t_node		*sep;

	if (tool->prev_token && (token__istype(tool->prev_token, SEMICON) &&
		token__iseot(tool->current_token)))
		return (SUCCESS);
	if (token__issep(tool->current_token) || token__iseot(tool->current_token))
		return (astb_error(tool, UNEXPECTED_TOKEN));
	cmd = node__new(CMD);
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
	return (process_call_next(tool, &sep));
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
