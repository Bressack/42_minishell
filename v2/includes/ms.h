/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:29:36 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/07 17:01:26 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H
# include <color_shell.h>
# include <double_linked.h>
# include <get_next_line.h>
# include <lexer.h>
# include <try_malloc.h>
# include <utils.h>
# define ERR 1
# define GNL__BADREAD 1
typedef struct		s_arg
{
	struct s_arg	*next;			// next arg
	struct s_arg	*prev;			// prev arg
	char			*name;			// arg name
}					t_arg;
typedef struct		s_cmd
{
	struct s_cmd	*next;			// next cmd
	struct s_cmd	*prev;			// prev cmd
	char			*path;			// path cmd "/path/of/the/cmd/like/ls"
	t_arg			*av_in;			// paths files rafters inputs '<' and '<<'
	t_arg			*av;			// args cmd
	t_arg			*av_out;		// paths files rafters inputs '>' (and '>>' (BONUS))
	int				fd_out;			// fd used by cmd as stdout
	int				fd_in;			// fd used by cmd as stdin
}					t_cmd;
typedef struct		s_env			// "key=value"
{
	struct s_env	*next;			// next env
	struct s_env	*prev;			// prev env
	char			*key;			// key
	char			*value;			// value
}					t_env;
typedef struct		s_all
{
	t_env			env;			// env list
	t_cmd			cmd;			// cmd list
	t_arg			last_arg;		// last arg parsed
	t_cmd			last_cmd;		// last cmd parsed
	int				needling;		// next str is arg or cmd
	char			*current_dir;	// dir actually used by the shell as the current dir
}					t_all;
#endif
