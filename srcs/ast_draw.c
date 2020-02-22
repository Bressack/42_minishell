/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 19:35:18 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/22 19:35:21 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "parser.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
​
void	bst_print_dot_null(char *data, void *key, int nullcount, int stream)
{
	ft_dprintf(stream, "    null%d [shape=point];\n", nullcount);
	ft_dprintf(stream, "    \"%s_%p\" -> null%d;\n", data, key, nullcount);
}
​
void	bst_print_dot_aux(t_node *node, int stream)
{
	static int nullcount = 0;
​
	if (node->left)
	{
		ft_dprintf(stream, "    \"%s_%p\" -> \"%s_%p\";\n", node->data\
				, node, node->left->data, node->left);
		bst_print_dot_aux(node->left, stream);
	}
	else
		bst_print_dot_null(node->data, node, nullcount++, stream);
	if (node->right)
	{
		ft_dprintf(stream, "    \"%s_%p\" -> \"%s_%p\";\n", node->data\
				, node, node->right->data, node->right);
		bst_print_dot_aux(node->right, stream);
	}
	else
		bst_print_dot_null(node->data, node, nullcount++, stream);
}
​
void	bst_print_dot(t_node *tree, int stream)
{
	ft_dprintf(stream, "digraph BST {\n");
	ft_dprintf(stream, "    node [fontname=\"Arial\"];\n");
	if (!tree)
		ft_dprintf(stream, "\n");
	else if (!tree->right && !tree->left)
		ft_dprintf(stream, "    \"%s_%p\";\n", tree->data, tree);
	else
		bst_print_dot_aux(tree, stream);
	ft_dprintf(stream, "}\n");
}
​
void	tree_draw(t_node *node)
{
	int stream;
​
	stream = open("tree.dot", (O_CREAT | O_RDWR), 0644);
	if (!stream)
		exit(0);
	bst_print_dot(node, stream);
	close(stream);
}