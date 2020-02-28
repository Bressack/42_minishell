/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__tokovore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:43:11 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/28 17:39:46 by tharchen         ###   ########.fr       */
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
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] new_node         | root: "C_G_GREEN"%p"C_RES" | body: "C_G_GREEN"%p"C_RES"\n", __LINE__, root, body);
	t_node			*new;

	new = try_malloc(sizeof(t_node), _FL_);
	printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] new_node         | set new->body with body\n", __LINE__);
	new->body = body;
	printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] new_node         | set new->parent with root\n", __LINE__);
	new->parent = root;
	printf("[ END       "C_G_MAGENTA"%4d"C_RES"] new_node         | return: new: "C_G_GREEN"%p"C_RES"\n", __LINE__, new);
	return (new);
}

void				del_node(t_node *node)
{
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] del_node         | node: "C_G_GREEN"%p"C_RES"\n", __LINE__, node);
	del_node_pattern(node->body);
	printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] del_node         | recurcive called to left\n", __LINE__);
	node->left ? del_node(node->left) : 0;
	printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] del_node         | recurcive called to right\n", __LINE__);
	node->right ? del_node(node->right) : 0;
	printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] del_node         | try_free called: node: "C_G_GREEN"%p"C_RES"\n", __LINE__, node);
	try_free_((void **)&node, _FL_);
	printf("[ END       "C_G_MAGENTA"%4d"C_RES"] del_node\n", __LINE__);
}

void				del_node_pattern(t_node_pattern *node)
{
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] del_node_pattern | node: "C_G_GREEN"%p"C_RES"\n", __LINE__, node);
	t_node_cmd		*tmp;

	if (node->selector == NODE_CMD)
	{
		printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] del_node_pattern | if statement (node->selector == NODE_CMD)\n", __LINE__);
		printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] del_node_pattern | set tmp with node\n", __LINE__);
		tmp = (t_node_cmd *)node;
		printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] del_node_pattern | ft_del_list_np called on tmp->arg\n", __LINE__);
		ft_del_list_np((t_pnp **)&tmp->arg);
		printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] del_node_pattern | ft_del_list_np called on tmp->redir\n", __LINE__);
		ft_del_list_np((t_pnp **)&tmp->redir);
	}
	printf("[ END       "C_G_MAGENTA"%4d"C_RES"] del_node_pattern\n", __LINE__);
}

void				tokerror(t_ast *ast, int code)
{
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] tokerror         | ast: "C_G_GREEN"%p"C_RES" | code: "C_G_CYAN"%d"C_RES"\n", __LINE__, ast, code);
	if (code == UNEXPECTED_TOKEN)
		ft_dprintf(2, ""C_G_RED"error:"C_G_WHITE" unexpected token"
			"\'"C_G_RED""C_G_CYAN"%s"C_RES""C_G_WHITE"\' after \'"C_G_GREEN""C_G_CYAN"%s"C_RES""C_G_WHITE"\'\n",
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
	// printf("[ START     "C_G_MAGENTA"%4d"C_RES"] check            | ast: "C_G_GREEN"%p"C_RES" | type: "C_G_CYAN"%d"C_RES"\n", __LINE__, ast, type);
	int	i;

	i = -1;
	// printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] check            | while loop: ", __LINE__);
	while (++i <  NB_DEFINED_TOKEN)
	{
		// printf("["C_G_CYAN"%d"C_RES"]", i);
		if (g_stype[i].type == ast->current_token->type)
			break ;
	}
	if (i >= NB_DEFINED_TOKEN)
		return (-1);
	// printf("\n");
	// printf("[ END       "C_G_MAGENTA"%4d"C_RES"] check            | matching with "C_G_CYAN"%u"C_RES" and return: g_stype[i].supertype == type: "C_G_CYAN"%d"C_RES"\n", __LINE__, g_stype[i].type, g_stype[i].supertype == type ? 1 : 0);
	return (g_stype[i].supertype == type ? 1 : 0);
}
/*
** ************************************************************************** **
** **** peek&eat *** both call lexer__get_next_token ************************ **
** ************************************************************************** **
*/
int					peek(t_ast *ast, t_token_supertype type)
{
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] peek             | ast: "C_G_GREEN"%p"C_RES" | type: "C_G_CYAN"%d"C_RES"\n", __LINE__, ast, type);
	if (!ast->current_token)
	{
		dprintf(1, "    [ BODY  "C_G_MAGENTA"%4d"C_RES"] peek         | current_token is not set, setting current_token. new token: ", __LINE__);
		ast->current_token = lexer__get_next_token(ast->lex);
		ast->current_token->next = NULL;
		ast->current_token->prev = NULL;
		printf("lexer__get_next_token got [%s]\n", ast->current_token->value);
		token__print(ast->current_token);
	}
	if (!ast->is_next_token_set)
	{
		printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] peek         | next_token is not set, setting next_token. new token: ", __LINE__);
		ast->is_next_token_set = 1;
		ast->next_token = lexer__get_next_token(ast->lex);
		ast->next_token->next = NULL;
		ast->next_token->prev = NULL;
		printf("lexer__get_next_token got [%s]\n", ast->next_token->value);
		token__print(ast->next_token);
	}
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] peek             | checking if next token matchs with type\n", __LINE__);
	return (check(ast, type));
}

void				eat(t_ast *ast, t_token_supertype type)
{
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] eat              | ast: "C_G_GREEN"%p"C_RES" | type: "C_G_CYAN"%d"C_RES"\n", __LINE__, ast, type);
	if (!ast->current_token)
	{
		dprintf(1, "    [ BODY  "C_G_MAGENTA"%4d"C_RES"] eat              | current_token is not set, setting current_token. new token: ", __LINE__);
		ast->current_token = lexer__get_next_token(ast->lex);
		printf("lexer__get_next_token got [%s]\n", ast->current_token->value);
		token__print(ast->next_token);
	}
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] eat              | checking if current token matchs with type\n", __LINE__);
	if (!check(ast, type))
		tokerror(ast, UNEXPECTED_TOKEN);
	printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] eat              | is_next_token_set: "C_G_CYAN"%d"C_RES"\n", __LINE__, ast->is_next_token_set);
	ast->prev_token = ast->current_token;
	if (ast->is_next_token_set)
	{
		printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] eat              | next_token is not set, setting next_token. new token: ", __LINE__);
		ast->is_next_token_set = 0;
		ast->current_token = ast->next_token;
	}
	else
		ast->current_token = lexer__get_next_token(ast->lex);
		printf("lexer__get_next_token got [%s]\n", ast->current_token->value);
}
/*
** ************************************************************************** **
** **** git utility :D *** roooo, laugh ! it's a joke.. uhg ? **** ********** **
** ************************************************************************** **
*/
void				git_add(t_ast *ast, t_token **dest, t_token_supertype type,
	int islist)
{
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] git_add          | ast: "C_G_GREEN"%p"C_RES" | dest: "C_G_GREEN"%p"C_RES" | *dest: "C_G_GREEN"%p"C_RES" | type:"
	" "C_G_CYAN"%d"C_RES"\n", __LINE__, ast, dest, dest ? *dest : 0, type);
	token__print(ast->current_token);
	printf("ast->current_token: %s\n", ast->current_token->value);
	if (type == ST_WORD && islist == LIST)
	{
		printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] git_add          | git add an list (currently an arg)\n", __LINE__);
		ft_add_node_end_np((t_pnp **)dest, (t_pnp *)&ast->current_token);
	}
	else
	{
		printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] git_add          | git add a simple token as cmd, redir, file or sep\n", __LINE__);
		*dest = ast->current_token;
	}
	printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] git_add          | going to eat the current_token\n", __LINE__);
	eat(ast, type);
	printf("ast->current_token: %s\n", ast->current_token->value);
	/*
** 	printf("*dest: %s\n", (*dest)->value);
** 	for (t_token *tmp = *dest; tmp; tmp = tmp->next)
** 	{
** 		printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] git_add          | for loop(tmp:"C_G_GREEN"%p"C_RES")\n", __LINE__, tmp);
** 		if (type == ST_WORD && islist)
** 			dprintf(1, "[ "C_G_CYAN"%s"C_RES" ] tmp "C_G_CYAN"%15p"C_RES" ", "ARG  " , tmp);
** 		else if (type == ST_WORD)
** 			dprintf(1, "[ "C_G_CYAN"%s"C_RES" ] tmp "C_G_CYAN"%15p"C_RES" ", "CMD  " , tmp);
** 		else if (type == ST_SEP)
** 			dprintf(1, "[ "C_G_CYAN"%s"C_RES" ] tmp "C_G_CYAN"%15p"C_RES" ", "SEP  " , tmp);
** 		else if (type == ST_REDIR)
** 			dprintf(1, "[ "C_G_CYAN"%s"C_RES" ] tmp "C_G_CYAN"%15p"C_RES" ", "REDIR" , tmp);
** 		token__print(tmp);
** 	}
*/
	printf("[ END       "C_G_MAGENTA"%4d"C_RES"] git_add\n", __LINE__);
}

void				git_add_to_tree(t_ast *ast, t_node_pattern *node)
{
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] git_add_to_tree  | ast: "C_G_GREEN"%p"C_RES" | node: "C_G_GREEN"%p"C_RES"\n", __LINE__, ast, node);
	t_node				*new;

	if (node->selector == NODE_EOT && ast->last_recording->selector == NODE_SEP
		&& ((t_node_sep *)ast->last_recording)->sep->type != SEMICON)
	{
	printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] git_add_to_tree          | \n", __LINE__);
		tokerror(ast, UNEXPECTED_EOT);
	}
	if (!ast->tree)
	{
		printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] git_add_to_tree          | \n", __LINE__);
		if (node->selector != NODE_CMD)
		{
			printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] git_add_to_tree          | \n", __LINE__);
			tokerror(ast, UNEXPECTED_TOKEN);
		}
		ast->tree = new_node(ast->tree, node);
		ast->tree->body = node;
	}
	else
	{
		printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] git_add_to_tree          | \n", __LINE__);
		if (node->selector == ast->last_recording->selector)
		{
			printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] git_add_to_tree          | \n", __LINE__);
			tokerror(ast, UNEXPECTED_TOKEN);
		}
		new = new_node(ast->tree, node);
		if (node->selector == NODE_CMD)
		{
			printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] git_add_to_tree          | \n", __LINE__);
			ast->tree->right = new;
		}
		else
		{
			printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] git_add_to_tree          | \n", __LINE__);
			new->left = ast->tree;
			ast->tree = new;
		}
	}
	ast->last_recording = node;
	printf("    [ BODY  "C_G_MAGENTA"%4d"C_RES"] git_add_to_tree          | \n", __LINE__);
}

int					git_commit(t_ast *ast, t_node_pattern *node)
{
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] git_commit       | ast: "C_G_GREEN"%p"C_RES" | node: "C_G_GREEN"%p"C_RES"\n", __LINE__, ast, node);
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
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] git_push         | ast: "C_G_GREEN"%p"C_RES"\n", __LINE__, ast);
	return (ast);
}
/*
** ************************************************************************** **
** **** grammar unterminals ************************************************* **
** ************************************************************************** **
*/
void				toko_redir(t_ast *ast, t_node_cmd *cmd)
{
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] toko_redir       | ast: "C_G_GREEN"%p"C_RES" | cmd: "C_G_GREEN"%p"C_RES"\n", __LINE__, ast, cmd);
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
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] toko_sep         | ast: "C_G_GREEN"%p"C_RES"\n", __LINE__, ast);
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
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] toko_cmd         | ast: "C_G_GREEN"%p"C_RES"\n", __LINE__, ast);
	t_node_cmd		*new;

	new = try_malloc(sizeof(t_node_cmd), _FL_);
	new->selector = NODE_CMD;
	new->arg = NULL;
	while (check(ast, ST_REDIR))
		toko_redir(ast, new);
	if (check(ast, ST_WORD))
	{
		// git_add(ast, &new->arg, ST_WORD, LIST);
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
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] init_ast         | ast: "C_G_GREEN"%p"C_RES" | *ast: "C_G_GREEN"%p"C_RES", sloc: "C_G_CYAN"%d"C_RES"\n", __LINE__, ast,
		ast ? *ast : 0, sloc);
	if (!(*ast))
		*ast = try_malloc(sizeof(t_ast), _FL_);
	else
		lexer__del(&(*ast)->lex);
	(*ast)->lex = lexer__new(sloc);
	(*ast)->current_token = lexer__get_next_token((*ast)->lex);
	printf("lexer__get_next_token got [%s]\n", (*ast)->current_token->value);
	(*ast)->next_token = lexer__get_next_token((*ast)->lex);
	printf("lexer__get_next_token got [%s]\n", (*ast)->next_token->value);
	// printf("During the init of the AST we discovered a new token:\n --- ");
	// token__print((*ast)->current_token);
}

t_ast				*toko_master(int sloc)
{
	printf("[ START     "C_G_MAGENTA"%4d"C_RES"] toko_cmd         | sloc: "C_G_CYAN"%d"C_RES"\n", __LINE__, sloc);
	printf(" --- ERR          : "C_G_CYAN"%d"C_RES"\n", ERR);
	printf(" --- EOT          : "C_G_CYAN"%d"C_RES"\n", EOT);
	printf(" --- SPACE        : "C_G_CYAN"%d"C_RES"\n", SPACE);
	printf(" --- PASS         : "C_G_CYAN"%d"C_RES"\n", PASS);
	printf(" --- WORD         : "C_G_CYAN"%d"C_RES"\n", WORD);
	printf(" --- SQUOTE       : "C_G_CYAN"%d"C_RES"\n", SQUOTE);
	printf(" --- DQUOTE       : "C_G_CYAN"%d"C_RES"\n", DQUOTE);
	printf(" --- LPAREN       : "C_G_CYAN"%d"C_RES"\n", LPAREN);
	printf(" --- RPAREN       : "C_G_CYAN"%d"C_RES"\n", RPAREN);
	printf(" --- REDIREC_IN   : "C_G_CYAN"%d"C_RES"\n", REDIREC_IN);
	printf(" --- REDIREC_OUT  : "C_G_CYAN"%d"C_RES"\n", REDIREC_OUT);
	printf(" --- DREDIREC_OUT : "C_G_CYAN"%d"C_RES"\n", DREDIREC_OUT);
	printf(" --- DBL_AND      : "C_G_CYAN"%d"C_RES"\n", DBL_AND);
	printf(" --- DBL_OR       : "C_G_CYAN"%d"C_RES"\n", DBL_OR);
	printf(" --- PIPE         : "C_G_CYAN"%d"C_RES"\n", PIPE);
	printf(" --- SEMICON      : "C_G_CYAN"%d"C_RES"\n", SEMICON);
	printf(" --- BSLASH       : "C_G_CYAN"%d"C_RES"\n", BSLASH);
	printf(" --- DOLLAR       : "C_G_CYAN"%d"C_RES"\n", DOLLAR);
	printf(" --- NONE         : "C_G_CYAN"%d"C_RES"\n", NONE);
	printf("*************************\n");
	printf(" --- ST_ERR       : "C_G_CYAN"%d"C_RES"\n", ST_ERR);
	printf(" --- ST_WORD      : "C_G_CYAN"%d"C_RES"\n", ST_WORD);
	printf(" --- ST_REDIR     : "C_G_CYAN"%d"C_RES"\n", ST_REDIR);
	printf(" --- ST_SEP       : "C_G_CYAN"%d"C_RES"\n", ST_SEP);
	printf(" --- ST_EOT       : "C_G_CYAN"%d"C_RES"\n", ST_EOT);
	static t_ast	*ast = NULL;

	init_ast(&ast, sloc);
	if (check(ast, ST_EOT))
		return (NULL);
	toko_cmd(ast);
	return (git_push(ast));
}
// echo arg1 arg2 arg3 arg4 arg5