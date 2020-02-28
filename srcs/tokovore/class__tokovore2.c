/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__tokovore2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:43:11 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/28 19:07:09 by tharchen         ###   ########.fr       */
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
	t_node			*new;

	new = try_malloc(sizeof(t_node), _FL_);
	new->body = body;
	new->parent = root;
	return (new);
}

void				del_node(t_node *node)
{
	del_node_pattern(node->body);
	node->left ? del_node(node->left) : 0;
	node->right ? del_node(node->right) : 0;
	try_free_((void **)&node, _FL_);
}

void				del_node_pattern(t_node_pattern *node)
{
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
	if (code == UNEXPECTED_TOKEN)
		ft_dprintf(2, ""C_G_RED"error:"C_G_WHITE" unexpected token"
			"\'"C_G_RED""C_G_CYAN"%s"C_RES""C_G_WHITE"\' after \'"C_G_GREEN""C_G_CYAN"%s"C_RES""C_G_WHITE"\'\n",
		ast->current_token->value, ast->prev_token->value);
	else if (code == UNEXPECTED_EOT)
		printf(TEST), tokerror(ast, UNEXPECTED_TOKEN);
	exit(-1);
}
/*
** ************************************************************************** **
** **** types checker ******************************************************* **
** ************************************************************************** **
*/
int					check(t_ast *ast, int whichone, t_token_supertype type)
{
	int	i;

	i = -1;
	while (++i <  NB_DEFINED_TOKEN)
	{
		if (whichone == CURRENT && g_stype[i].type == ast->current_token->type)
			break ;
		if (whichone == NEXT && g_stype[i].type == ast->next_token->type)
			break ;
	}
	if (i >= NB_DEFINED_TOKEN)
		return (-1);
	return (g_stype[i].supertype == type ? 1 : 0);
}
/*
** ************************************************************************** **
** **** peek&eat *** both call lexer__get_next_token ************************ **
** ************************************************************************** **
*/
int					peek(t_ast *ast, t_token_supertype type)
{
	if (!ast->next_token)
	{
		ast->next_token = lexer__get_next_token(ast->lex);
		token__print(ast->next_token);
	}
	return (check(ast, NEXT, type));
}

void				eat(t_ast *ast, t_token_supertype type)
{
	if (!ast->current_token)
	{
		ast->current_token = lexer__get_next_token(ast->lex);
		token__print(ast->next_token);
	}
	if (!check(ast, CURRENT, type))
		printf(TEST), tokerror(ast, UNEXPECTED_TOKEN);
	ast->prev_token = ast->current_token;
	if (ast->next_token)
	{
		ast->current_token = ast->next_token;
		ast->next_token = NULL;
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
	token__print(ast->current_token);
	printf("ast->current_token: %s\n", ast->current_token->value);
	if (type == ST_WORD && islist == LIST)
	{
		ft_add_node_end_np((t_pnp **)dest, (t_pnp *)&ast->current_token);
	}
	else
	{
		*dest = ast->current_token;
	}
	eat(ast, type);
	printf("ast->current_token: %s\n", ast->current_token->value);
}

void				git_add_to_tree(t_ast *ast, t_node_pattern *body)
{
	t_node				*new;

	printf("git_add_to_tree: %d\n", body->selector);
	if (body->selector == NODE_EOT && ast->last_recording->selector == NODE_SEP
		&& ((t_node_sep *)ast->last_recording)->sep->type != SEMICON)
	{
		printf(TEST), tokerror(ast, UNEXPECTED_EOT);
	}
	if (!ast->tree)
	{
		if (body->selector != NODE_CMD)
		{
			printf(TEST), tokerror(ast, UNEXPECTED_TOKEN);
		}
		ast->tree = new_node(ast->tree, body);
		ast->tree->body = body;
	}
	else
	{
		if (body->selector == ast->last_recording->selector)
		{
			printf(TEST), tokerror(ast, UNEXPECTED_TOKEN);
		}
		new = new_node(ast->tree, body);
		if (body->selector == NODE_CMD)
		{
			ast->tree->right = new;
		}
		else
		{
			new->left = ast->tree;
			ast->tree = new;
		}
	}
	ast->last_recording = body;
}

int					git_commit(t_ast *ast, t_node_pattern *node)
{
	printf("[ TRY   "C_G_MAGENTA"%4d"C_RES"] node->selector: "C_G_CYAN"%d"C_RES"\n", __LINE__, node->selector);
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
	return (ast);
}
/*
** ************************************************************************** **
** **** grammar unterminals ************************************************* **
** ************************************************************************** **
*/
void				toko_redir(t_ast *ast, t_node_cmd *cmd)
{
	t_subnode_redir	*new;

	new = try_malloc(sizeof(t_subnode_redir), _FL_);;
	new->selector = NODE_REDIR;
	if (check(ast, CURRENT, ST_REDIR) && peek(ast, ST_WORD))
	{
		git_add(ast, &new->type, ST_REDIR, NOT_A_LIST);
		git_add(ast, &new->file, ST_WORD, NOT_A_LIST);
	}
	else
		printf(TEST), tokerror(ast, UNEXPECTED_TOKEN);
	cmd->redir = new;
}

void				toko_sep(t_ast *ast)
{
	t_node_sep		*new;

	new = try_malloc(sizeof(t_node_sep), _FL_);
	new->selector = NODE_SEP;
	if (check(ast, CURRENT, ST_SEP))
		git_add(ast, &new->sep, ST_SEP, NOT_A_LIST);
	if (git_commit(ast, (t_node_pattern *)new) == CONTINUE)
		toko_cmd(ast);
}

void				toko_cmd__debug_print(t_node_cmd *new)
{
	printf("command node current state: \n");
	printf(" --- next     : "C_G_GREEN"%p"C_RES"\n", new->next);
	printf(" --- prev     : "C_G_GREEN"%p"C_RES"\n", new->prev);
	printf(" --- selector : "C_G_CYAN"%d"C_RES"\n", new->selector);
	printf(" --- arg      : "C_G_GREEN"%p"C_RES"\n", new->arg);
	for (t_token *tmp = new->arg; tmp ; tmp = tmp->next)
	{
		dprintf(1, " --- --- ");
		token__print(tmp);
	}
	printf(" --- redir    : "C_G_GREEN"%p"C_RES"\n", new->redir);
	for (t_subnode_redir *tmp = new->redir; tmp ; tmp = tmp->next)
	{
		dprintf(1, " --- --- ");
		token__print(tmp->type);
		dprintf(1, " --- --- ");
		token__print(tmp->file);
	}
	printf(" --- fd_in    : "C_G_CYAN"%d"C_RES"\n", new->fd_in);
	printf(" --- fd_out   : "C_G_CYAN"%d"C_RES"\n", new->fd_out);
	printf(" --- av       : "C_G_GREEN"%p"C_RES"\n", new->av);
	printf(" --- sloc     : "C_G_CYAN"%d"C_RES"\n", new->sloc);
}

void				toko_cmd(t_ast *ast)
{
	t_node_cmd		*new;

	new = try_malloc(sizeof(t_node_cmd), _FL_);
	new->selector = NODE_CMD;
	new->arg = NULL;
	while (check(ast, CURRENT, ST_REDIR))
		toko_redir(ast, new);
	if (check(ast, CURRENT, ST_WORD))
	{
		git_add(ast, &new->arg, ST_WORD, LIST);
		while (check(ast, CURRENT, ST_REDIR) || check(ast, CURRENT, ST_WORD))
		{
			if (check(ast, CURRENT, ST_REDIR))
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

void				print_ast(t_node *root, int deep)
{
	printf("%*s[ NODE ] right  : %p\n", deep * 2, "| ", root->right);
	printf("%*s         left   : %p\n", deep * 2, "| ", root->left);
	printf("%*s         parent : %p\n", deep * 2, "| ", root->parent);
	printf("%*s         body   : %p\n\n", deep * 2, "| ", root->body);
	root->right ? print_ast(root->right, deep + 1) : 0;
	root->left ? print_ast(root->left, deep + 1) : 0;
}

void				init_ast(t_ast **ast, int sloc)
{
	if (*ast)
	{
		lexer__del(&(*ast)->lex);
		try_free_((void **)ast, _FL_);
	}
	*ast = try_malloc(sizeof(t_ast), _FL_);
	(*ast)->lex = lexer__new(sloc);
	(*ast)->current_token = lexer__get_next_token((*ast)->lex);
	(*ast)->next_token = lexer__get_next_token((*ast)->lex);
	// printf("During the init of the AST we discovered a new token:\n --- ");
	// token__print((*ast)->current_token);
}

t_ast				*toko_master(int sloc)
{
	printf("STARTING NEW toko_master =========================================================================\n");
/*
** 	printf(" --- ERR          : "C_G_CYAN"%d"C_RES"\n", ERR);
** 	printf(" --- EOT          : "C_G_CYAN"%d"C_RES"\n", EOT);
** 	printf(" --- SPACE        : "C_G_CYAN"%d"C_RES"\n", SPACE);
** 	printf(" --- PASS         : "C_G_CYAN"%d"C_RES"\n", PASS);
** 	printf(" --- WORD         : "C_G_CYAN"%d"C_RES"\n", WORD);
** 	printf(" --- SQUOTE       : "C_G_CYAN"%d"C_RES"\n", SQUOTE);
** 	printf(" --- DQUOTE       : "C_G_CYAN"%d"C_RES"\n", DQUOTE);
** 	printf(" --- LPAREN       : "C_G_CYAN"%d"C_RES"\n", LPAREN);
** 	printf(" --- RPAREN       : "C_G_CYAN"%d"C_RES"\n", RPAREN);
** 	printf(" --- REDIREC_IN   : "C_G_CYAN"%d"C_RES"\n", REDIREC_IN);
** 	printf(" --- REDIREC_OUT  : "C_G_CYAN"%d"C_RES"\n", REDIREC_OUT);
** 	printf(" --- DREDIREC_OUT : "C_G_CYAN"%d"C_RES"\n", DREDIREC_OUT);
** 	printf(" --- DBL_AND      : "C_G_CYAN"%d"C_RES"\n", DBL_AND);
** 	printf(" --- DBL_OR       : "C_G_CYAN"%d"C_RES"\n", DBL_OR);
** 	printf(" --- PIPE         : "C_G_CYAN"%d"C_RES"\n", PIPE);
** 	printf(" --- SEMICON      : "C_G_CYAN"%d"C_RES"\n", SEMICON);
** 	printf(" --- BSLASH       : "C_G_CYAN"%d"C_RES"\n", BSLASH);
** 	printf(" --- DOLLAR       : "C_G_CYAN"%d"C_RES"\n", DOLLAR);
** 	printf(" --- NONE         : "C_G_CYAN"%d"C_RES"\n", NONE);
** 	printf("*************************\n");
** 	printf(" --- ST_ERR       : "C_G_CYAN"%d"C_RES"\n", ST_ERR);
** 	printf(" --- ST_WORD      : "C_G_CYAN"%d"C_RES"\n", ST_WORD);
** 	printf(" --- ST_REDIR     : "C_G_CYAN"%d"C_RES"\n", ST_REDIR);
** 	printf(" --- ST_SEP       : "C_G_CYAN"%d"C_RES"\n", ST_SEP);
** 	printf(" --- ST_EOT       : "C_G_CYAN"%d"C_RES"\n", ST_EOT);
*/
	static t_ast	*ast = NULL;

	printf("ast: %p\n", ast);
	init_ast(&ast, sloc);
	printf("ast: %p\n", ast);
	if (check(ast, CURRENT, ST_EOT))
		return (NULL);
	toko_cmd(ast);
	return (git_push(ast));
}
// echo arg1 arg2 arg3 arg4 arg5