/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 00:35:06 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/22 16:39:47 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_node		node__new(t_token token)
{
	t_node	new;

	node.left = NULL;
	node.right = NULL;
	node.parent = NULL;
	node.token = token;
	return (node);
}

void		node__del(t_node node)
{
	token__del(node.token)
	if (node.left)
		node__del(node.left);
	if (node.right)
	node__del(node.right);
}

void		node__print(t_node node)
{
	token__print(node.token);
	printf("{ parent: %016p } ", node.parent);
	printf("{ left  : %016p }\n", node.left);
	printf("{ right : %016p } ", node.right);
}


// void		node__add_child(t_ast *parent, t_node child, int rl_lever)
// {
// 	if (rl_lever == RIGHT_CHILD)
// 		ast->tree->
// 	if (rl_lever == LEFT_CHILD)
// 		ast->tree->
// }

t_cmd		node__new_cmd(char *name)
{
	t_cmd	new;

	new.name = name;
	new.fd_in = 1;
	new.fd_out = 0;
	new.av_in = NULL;
	new.av = NULL;
	new.av_out = NULL;
}

t_redir		node__eat_redir()
{

}
