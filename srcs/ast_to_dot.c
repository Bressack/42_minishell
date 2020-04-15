/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_dot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 09:33:57 by tharchen          #+#    #+#             */
/*   Updated: 2020/04/15 15:40:42 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#define NULL_STR_DOT "(null)"
#if BONUS == 1

char	*get_value(t_node *n)
{
	if (n->type == CMD)
		return (n->av ? n->av->value : NULL_STR_DOT);
	else
		return (n->sep ? n->sep->value : NULL_STR_DOT);
}

void	bst_print_dot_aux(t_node *node, int stream, int deep)
{
	if (node->left)
	{
		ft_dprintf(stream, "    \"[ %s ]_(%d)\" -> \"[ %s ]_(%d)\";\n",
		get_value(node), deep, get_value(node->left), deep * 10 + 1);
		bst_print_dot_aux(node->left, stream, deep * 10 + 1);
	}
	if (node->right)
	{
		ft_dprintf(stream, "    \"[ %s ]_(%d)\" -> \"[ %s ]_(%d)\";\n",
		get_value(node), deep, get_value(node->right), deep * 10 + 2);
		bst_print_dot_aux(node->right, stream, deep * 10 + 2);
	}
}

void	bst_print_dot(t_node *tree, int stream)
{
	ft_dprintf(stream, "digraph BST {\n");
	ft_dprintf(stream, "    node [fontname=\"Arial\"];\n");
	if (!tree)
		ft_dprintf(stream, "\n");
	else if (!tree->right && !tree->left)
		ft_dprintf(stream, "    \"[ %s ]_(%d)\";\n", get_value(tree), 0);
	else
		bst_print_dot_aux(tree, stream, 0);
	ft_dprintf(stream, "}\n");
}

void	tree_draw(t_node *node)
{
	int		stream;

	remove("tree.dot");
	remove("tree.png");
	stream = open("/tmp/tree.dot", (O_CREAT | O_RDWR), 0644);
	if (!stream)
		exit(0);
	bst_print_dot(node, stream);
	close(stream);
}

#endif
