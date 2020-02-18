/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__node.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 00:39:52 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/18 00:46:47 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS__NODE_H
# define CLASS__NODE_H
typedef struct		s_node
{
	struct s_node	*right;
	struct s_node	*left;
	struct s_node	*parent;
	t_token			token;
}					t_node;
#endif
