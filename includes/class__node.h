/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__node.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 00:39:52 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/24 13:18:56 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS__NODE_H
# define CLASS__NODE_H
# include <minishell.h>
typedef struct		s_node
{
	struct s_node	*right;		// next
	struct s_node	*left;		// next
	struct s_node	*parent;	// prev
	int				type;		// node type: CMD || PIPE || CMDSEP
	t_cmd			*cmd;		// cmd struct
	t_pipe			*pipe;		// pipe struct
	t_cmdsep		*cmdsep;	// cmdsep struct
}					t_node;
typedef struct		s_cmd
{
	t_token			token;
	int				fd_in;		// fd used by the cmd for output (default: stdout)
	int				fd_out;		// fd used by the cmd for input (default: stdin)
	t_redir			*av_in;	// list of all input redirection (REDIREC_IN)
	t_arg			*av;		// cmd args (av)
	t_redir			*av_out;	// list of all output redirection (REDIREC_OUT || DREDIREC_OUT)
}					t_cmd;
typedef struct		s_pipe
{
	t_token			token;
}					t_pipe;
typedef struct		s_redir
{
	t_token			token;
}					t_redir;
typedef struct		s_arg
{
	t_token			token;
}					t_arg;
t_node				node__new(t_token token);
void				node__del(t_node node);
void				node__print(t_node node);
# include <class__ast.h>

void				node__add_child(t_ast *parent, t_node child, int rl_lever);
#endif
