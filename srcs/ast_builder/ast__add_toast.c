/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast__add_toast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 04:18:03 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/10 04:23:31 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
