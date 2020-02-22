/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__node.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 00:39:52 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/22 15:36:18 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS__NODE_H
# define CLASS__NODE_H
# include <minishell.h>
typedef struct		s_node
{
	struct s_node	*right;
	struct s_node	*left;
	struct s_node	*parent;
	t_token			token;

}					t_node;
typedef struct		s_redir
{
	t_token_type	type;
	char			*filename;
}					t_redir;
typedef struct		s_cmd
{
	char			*name;
	int				fd_in;
	int				fd_out;
	t_redir			**av_in;
	char			**av;
	t_redir			**av_out;
}					t_cmd;
t_node				node__new(t_token token);
void				node__del(t_node node);
void				node__print(t_node node);
# include <class__ast.h>

void				node__add_child(t_ast *parent, t_node child, int rl_lever);
#endif
