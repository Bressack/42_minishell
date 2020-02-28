/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__tokovore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:43:11 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/28 02:05:40 by tharchen         ###   ########.fr       */
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
	{LPAREN       , ST_ERR}, // pas encore geré
	{RPAREN       , ST_ERR}, // pas encore geré
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
/*
** ************************************************************************** **
** **** node object handle ************************************************** **
** ************************************************************************** **
*/
t_node				*new_node(t_node *root, t_node_pattern *body)
{
	printf("[ START ] new_node         | root: %p | body: %p\n", root, body);
	t_node			*new;

	new = try_malloc(sizeof(t_node), _FL_);
	new->body = body;
	new->parent = root;
	return (new);
}

void				del_node(t_node *node)
{
	printf("[ START ] del_node         | node: %p\n", node);
	del_node_pattern(node->body);
	node->left ? del_node(node->left) : 0;
	node->right ? del_node(node->right) : 0;
	try_free_((void **)&node, _FL_);
}

void				del_node_pattern(t_node_pattern *node)
{
	printf("[ START ] del_node_pattern | node: %p\n", node);
	t_node_cmd		*tmp;

	if (node->selector == NODE_CMD)
	{
		tmp = (t_node_cmd *)node;
		ft_del_list_np((t_pnp **)&tmp->arg);
		ft_del_list_np((t_pnp **)&tmp->redir);
	}
}

void				tokerror(t_ast *ast, int code)
{
	printf("[ START ] tokerror         | ast: %p | code: %d\n", ast, code);
	if (code == UNEXPECTED_TOKEN)
		ft_dprintf(2, ""C_G_RED"error:"C_G_WHITE" unexpected token"
			"\'"C_G_RED"%s"C_G_WHITE"\' after \'"C_G_GREEN"%s"C_G_WHITE"\'\n",
		ast->current_token->value, ast->prev_token->value);
	else if (code == UNEXPECTED_EOT)
		tokerror(ast, UNEXPECTED_TOKEN);
	exit(-1);
}
/*
** ************************************************************************** **
** **** types checker ******************************************************* **
** ************************************************************************** **
*/
int					check(t_ast *ast, t_token_supertype type)
{
	printf("[ START ] check            | ast: %p | type: %d\n", ast, type);
	int	i;

	i = -1;
	while (++i <  NB_DEFINED_TOKEN)
		if (g_stype[i].type == ast->current_token->type)
			break ;
	return (g_stype[i].supertype == type ? 1 : 0);
}
/*
** ************************************************************************** **
** **** peek&eat *** both call lexer__get_next_token ************************ **
** ************************************************************************** **
*/
int					peek(t_ast *ast, t_token_supertype type)
{
	printf("[ START ] peek             | ast: %p | type: %d\n", ast, type);
	if (!ast->current_token)
	{
		ast->current_token = lexer__get_next_token(ast->lex);
		printf("Oopsi, the current_token was NULL, pee refilled it:\n --- ");
		token__print(ast->next_token);
	}
	if (!ast->is_next_token_full)
	{
		ast->is_next_token_full = 1;
		ast->next_token = lexer__get_next_token(ast->lex);
	}
	printf("peek discover a new token:\n --- ");
	token__print(ast->next_token);
	return (check(ast, type));
}

void				eat(t_ast *ast, t_token_supertype type)
{
	printf("[ START ] eat              | ast: %p | type: %d\n", ast, type);
	if (!check(ast, type))
		tokerror(ast, UNEXPECTED_TOKEN);
	printf("is_next_token_full: %d\n", ast->is_next_token_full);
	ast->prev_token = ast->current_token;
	if (ast->is_next_token_full)
	{
		ast->is_next_token_full = 0;
		ast->current_token = ast->next_token;
	}
	else
		ast->current_token = lexer__get_next_token(ast->lex);
}
/*
** ************************************************************************** **
** **** git utility :D *** roooo, laugh ! it's a joke.. uhg ? **** ********** **
** ************************************************************************** **
*/
void				git_add(t_ast *ast, t_token **dest, t_token_supertype type,
	int islist)
{
	printf("[ START ] git_add          | ast: %p | dest: %p | *dest: %p | type: %d\n", ast, dest, dest ? *dest : 0, type);
	if (type == ST_WORD && islist == NOT_A_LIST)
		ft_add_node_end_np((t_pnp **)dest, (t_pnp *)&ast->current_token);
	else
		*dest = ast->current_token;
	eat(ast, type);
	for (t_token *tmp = *dest; tmp; tmp++)
	{
		dprintf(1, "[ %s ] tmp %15p ", type == ST_WORD && islist ? "ARG" : "CMD", tmp);
		token__print(tmp);
	}
}

void				git_add_to_tree(t_ast *ast, t_node_pattern *node)
{
	printf("[ START ] git_add_to_tree  | ast: %p | node: %p\n", ast, node);
	t_node				*new;

	if (node->selector == NODE_EOT && ast->last_recording->selector == NODE_SEP
		&& ((t_node_sep *)ast->last_recording)->sep->type != SEMICON)
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
		if (node->selector == NODE_CMD)
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
	printf("[ START ] git_commit       | ast: %p | node: %p\n", ast, node);
	printf("[ TRY   ] node->selector: %d\n", node->selector);
	if (node->selector == NODE_CMD)
	{
		git_add_to_tree(ast, node);
		if (peek(ast, ST_SEP | ST_WORD | ST_REDIR))
			return (CONTINUE);
	}
	if (node->selector == NODE_SEP)
	{
		git_add_to_tree(ast, node);
		if (peek(ast, ST_WORD | ST_REDIR))
			return (CONTINUE);
	}
	if (node->selector == NODE_EOT)
		git_add_to_tree(ast, node);
	return (BREAK);
}

t_ast				*git_push(t_ast *ast)
{
	printf("[ START ] git_push         | ast: %p\n", ast);
	return (ast);
}
/*
** ************************************************************************** **
** **** grammar unterminals ************************************************* **
** ************************************************************************** **
*/
void				toko_redir(t_ast *ast, t_node_cmd *cmd)
{
	printf("[ START ] toko_redir       | ast: %p | cmd: %p\n", ast, cmd);
	t_subnode_redir	*new;

	new = try_malloc(sizeof(t_subnode_redir), _FL_);;
	new->selector = NODE_REDIR;
	if (check(ast, ST_REDIR) && peek(ast, ST_WORD))
	{
		git_add(ast, &new->type, ST_REDIR, NOT_A_LIST);
		git_add(ast, &new->file, ST_WORD, NOT_A_LIST);
	}
	else
		tokerror(ast, UNEXPECTED_TOKEN);
	cmd->redir = new;
}

void				toko_sep(t_ast *ast)
{
	printf("[ START ] toko_sep         | ast: %p\n", ast);
	t_node_sep		*new;

	new = try_malloc(sizeof(t_node_sep), _FL_);
	new->selector = NODE_SEP;
	if (check(ast, ST_SEP))
		git_add(ast, &new->sep, ST_SEP, NOT_A_LIST);
	if (git_commit(ast, (t_node_pattern *)new) == CONTINUE)
		toko_cmd(ast);
}

void				toko_cmd__debug_print(t_node_cmd *new)
{
	printf("command node current state: \n");
	printf(" --- next     : %p\n", new->next);
	printf(" --- prev     : %p\n", new->prev);
	printf(" --- selector : %d\n", new->selector);
	printf(" --- cmd      : %p\n", new->cmd);
	token__print(new->cmd);
	printf(" --- arg      : %p\n", new->arg);
	for (t_token *tmp = new->arg; tmp ; tmp = tmp->next)
	{
		dprintf(1, " --- --- ");
		token__print(tmp);
	}
	printf(" --- redir    : %p\n", new->redir);
	for (t_subnode_redir *tmp = new->redir; tmp ; tmp = tmp->next)
	{
		dprintf(1, " --- --- ");
		token__print(tmp->type);
		dprintf(1, " --- --- ");
		token__print(tmp->file);
	}
	printf(" --- fd_in    : %d\n", new->fd_in);
	printf(" --- fd_out   : %d\n", new->fd_out);
	printf(" --- av       : %p\n", new->av);
	printf(" --- sloc     : %d\n", new->sloc);
}

void				toko_cmd(t_ast *ast)
{
	printf("[ START ] toko_cmd         | ast: %p\n", ast);
	t_node_cmd		*new;

	new = try_malloc(sizeof(t_node_cmd), _FL_);
	new->selector = NODE_CMD;
	while (check(ast, ST_REDIR))
		toko_redir(ast, new);
	if (check(ast, ST_WORD))
	{
		git_add(ast, &new->cmd, ST_WORD, NOT_A_LIST);
		while (check(ast, ST_REDIR) || check(ast, ST_WORD))
		{
			if (check(ast, ST_REDIR))
				toko_redir(ast, new);
			else
				git_add(ast, &new->arg, ST_WORD, LIST);
		}
	}
	toko_cmd__debug_print(new);
	if (git_commit(ast, (t_node_pattern *)new) == CONTINUE)
		toko_sep(ast);
}
/*
** ************************************************************************** **
** **** body functions ****************************************************** **
** ************************************************************************** **
*/
void				init_ast(t_ast **ast, int sloc)
{
	printf("[ START ] init_ast         | ast: %p | *ast: %p, sloc: %d\n", ast,
		ast ? *ast : 0, sloc);
	if (!(*ast))
		*ast = try_malloc(sizeof(t_ast), _FL_);
	else
		lexer__del(&(*ast)->lex);
	(*ast)->lex = lexer__new(sloc);
	(*ast)->current_token = lexer__get_next_token((*ast)->lex);
	// printf("During the init of the AST we discovered a new token:\n --- ");
	// token__print((*ast)->current_token);
}

t_ast				*toko_master(int sloc)
{
	printf("[ START ] toko_cmd         | sloc: %d\n", sloc);
	static t_ast	*ast = NULL;

	init_ast(&ast, sloc);
	if (check(ast, ST_EOT))
		return (NULL);
	toko_cmd(ast);
	return (git_push(ast));
}
// echo arg1 arg2 arg3 arg4 arg5