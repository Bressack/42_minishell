/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__tokovore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:43:11 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/27 00:09:16 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_type_to_supertype	g_stype[NB_DEFINED_TOKEN] =
{
	{ERR          , ST_ERR},
	{EOT          , ST_EOT},
	{SPACE        , ST_ERR},
	{PASS         , ST_ERR},
	{WORD         , ST_WORD},
	{SQUOTE       , ST_WORD},
	{DQUOTE       , ST_WORD},
	{LPAREN       , ST_ERR}, // pas encore gere
	{RPAREN       , ST_ERR}, // pas encore gere
	{REDIREC_IN   , ST_REDIR},
	{REDIREC_OUT  , ST_REDIR},
	{DREDIREC_OUT , ST_REDIR},
	{DBL_AND      , ST_SEP},
	{DBL_OR       , ST_SEP},
	{PIPE         , ST_SEP},
	{SEMICON      , ST_SEP},
	{BSLASH       , ST_WORD},
	{DOLLAR       , ST_WORD},
	{NONE         , ST_ERR}
};

void				tokerror(t_ast *ast, int code)
{
	if (code == UNEXPECTED_TOKEN)
		ft_dprintf(2, ""C_G_RED"error:"C_G_WHITE" unexpected token \'"C_G_RED"%s"C_G_WHITE"\' after \'"C_G_GREEN"%s"C_G_WHITE"\'\n",
		ast->current_token.value, ast->prev_token.value);
}

int					check(t_ast *ast, t_token_supertype type)
{
	int	i;

	i = -1;
	while (++i <  NB_DEFINED_TOKEN)
		if (g_stype[i].type == ast->current_token.type)
			break ;
	return (g_stype[i].supertype == type ? 1 : 0);
}

int					peek(t_ast *ast, t_token_supertype type)
{
	if (!ast->is_next_token_full)
	{
		ast->is_next_token_full = 1;
		ast->next_token = lexer__get_next_token(&ast->lex);
	}
	return (check(ast, type));
}

void				eat(t_ast *ast, t_token_supertype type)
{

	if (!check(ast, type))
		tokerror(ast, UNEXPECTED_TOKEN);
	ast->prev_token = ast->current_token;
	if (ast->is_next_token_full)
	{
		ast->is_next_token_full = 0;
		ast->current_token = ast->next_token;
	}
	else
		ast->current_token = lexer__get_next_token(&ast->lex);
}

void				git_add(t_ast *ast, t_token **addrdest, t_token_supertype type)
{
	if (type == ST_WORD)
		ft_add_node_end_np((t_pnp **)addrdest, (t_pnp *)&ast->current_token);
	else
		**addrdest = ast->current_token;
	eat(ast, type);
}

void				del_node_pattern(t_node_pattern *n)
{
	t_node_cmd		*tmp;

	if (n->selector == NODE_CMD)
	{
		tmp = (t_node_cmd *)n;
		ft_del_list_np((pnp **)&n->arg);
		ft_del_list_np((pnp **)&n->redir);
	}
}

void				del_node(t_node *node)
{
	del_node_pattern(node->body);
	node->left ? del_node(node->left) : 0;
	node->right ? del_node(node->right) : 0;
	try_free_(&node, _FL_);
}

t_node				*new_node(t_node *root, t_node_pattern *body)
{
	t_node			*new;

	new = try_malloc(sizeof(t_node), _FL_);
	new->body = body;
	new->parent = root;
}

void				git_add_to_tree(t_ast *ast, t_node_pattern *node)
{
	t_node				*new;

	if (node->selector == NODE_EOT && ast->last_recording->selector == SEP &&
		((t_node_sep *)ast->last_recording)->sep.type != SEMICON)
		tokerror(ast, UNEXPECTED_EOT);
	if (!ast->tree)
	{
		if (node->selector != NODE_CMD)
			tokerror(ast, UNEXPECTED_TOKEN);
		ast->tree = new_node(ast->tree, node);
		ast->tree->body = node;
	}
	else
	{
		if (node->selector == ast->last_recording->selector)
			tokerror(ast, UNEXPECTED_TOKEN);
		new = new_node(ast->tree, node);
		if (node->selector == CMD)
			ast->tree->right = new;
		else
		{
			new->left = ast->tree;
			ast->tree = new;
		}
	}
	ast->last_recording = node;
}

int					git_commit(t_ast *ast, t_node_pattern *node)
{
	if (node->selector == NODE_CMD)
	{
		git_add_to_tree(node);
		if (peek(ast, ST_SEP | ST_WORD | ST_REDIR))
			return (CONTINUE);
	}
	if (node->selector == NODE_SEP)
	{
		git_add_to_tree(node);
		if (peek(ast, ST_WORD | ST_REDIR))
			return (CONTINUE);
	}
	if (node->selector == NODE_EOT)
		git_add_to_tree(node);
	return (BREAK);
}

inline t_ast		*git_push(t_ast *ast)
{
	return (ast);
}

void				toko_redir(t_ast *ast, t_node_cmd *cmd)
{
	t_subnode_redir	*new;

	new = try_malloc(sizeof(t_subnode_redir), _FL_);;
	new.selector = NODE_REDIR;
	if (check(ast, ST_REDIR) && peek(ast, ST_WORD))
	{
		git_add(ast, &new->type, ST_REDIR);
		git_add(ast, &new->file, ST_WORD);
	}
	else
		tokerror(ast, UNEXPECTED_TOKEN);
	cmd->redir = new;
}

void				toko_sep(t_ast *ast)
{
	t_node_sep		*new;

	new = try_malloc(sizeof(t_node_sep), _FL_);
	new.selector = NODE_SEP;
	if (check(ast, ST_SEP))
		git_add(ast, &new.sep, ST_SEP);
	if (git_commit(ast, (t_node_pattern *)&new) == CONTINUE)
		toko_cmd(ast);
}

void				toko_cmd(t_ast *ast)
{
	t_node_cmd		*new;

	new = try_malloc(sizeof(t_node_cmd), _FL_);
	new.selector = NODE_CMD;
	while (check(ast, ST_REDIR))
		toko_redir(ast, &new);
	if (check(ast, ST_WORD))
	{
		git_add(ast, &new.cmd, ST_WORD);
		while (check(ast, ST_REDIR) || check(ast, ST_WORD))
		{
			if (check(ast, ST_REDIR))
				toko_redir(ast, &new);
			else
				git_add(ast, &new.arg, ST_WORD);
		}
	}
	if (git_commit(ast, (t_node_pattern *)&new) == CONTINUE)
		toko_sep(ast);
}

void				init_ast(t_ast *ast, int sloc)
{
	if (ast->lex->line)
		lexer__del(&ast->lex);
	bzero(ast, sizeof(t_ast));
	ast->lex = lexer__new(sloc);
}

t_ast				*toko_master(int sloc)
{
	static t_ast		ast;

	init_ast(&ast, sloc);
	if (check(&ast, ST_EOT))
	{
		ast.eot.selector = NODE_EOT;
		ast.eot.eot = g_defined_tokens[I_EOT];
		git_commit(&ast, (t_node_pattern *)&ast.eot);
	}
	else
		toko_cmd(&ast);
	return (git_push(&ast));
}
