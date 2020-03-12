/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast__builder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 18:31:13 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/12 16:11:57 by tharchen         ###   ########.fr       */
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
		return (EMPTY); // line empty
	}
	tool->prev_token = NULL;
	tool->tree_pos = NULL;
	tool->ast = NULL;
	return (SUCCESS);
}

t_node	*ast_builder(int sloc)
{
	t_astb		tool;
	int			ret;

	ret = init_tool(&tool, sloc);
	if (ret == EMPTY)
		return (ast_builder(sloc));
	if (ret != ERROR && process(&tool) != ERROR)
	{
		lexer__del(&tool.lex);
		return (tool.ast);
	}
	lexer__del(&tool.lex);
	return (NULL);
}
