/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:53:10 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/29 19:29:11 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H
# include <double_linked.h>
# include <get_next_line.h>
# include <try_malloc.h>
# include <utils.h>
# include <color_shell.h>
# define PROMPT_ARROW		"➜"

# define PROMPT_NORMAL		0
# define PROMPT_NEXT_NEEDED	1

# define ISCMD			0
# define ISARG			1
# define ISARG_IN		2
# define ISARG_OUT		3

# define ISQUOTE		0
# define ISNOTQUOTE		1
# define QUOTE_OPEN		0
# define QUOTE_CLOSE	1

# define FD_STDOUT		0
# define FD_STDIN		1

# define LINK_COLON_	0
# define LINK_PIPE__	1
# define LINK_AND___	2 // BONUS
# define LINK_OR____	3 // BONUS
# define LINK_THREAD	4 // BONUS

# define NOREDIR_______	0
# define REDIR_RIGHT___	1
# define REDIR_DBLRIGHT	2
# define REDIR_LEFT____	3
# define REDIR_DBLLEFT_	4

typedef struct		s_arg
{
	struct s_arg	*next;
	struct s_arg	*prev;
	char			*data;
	int				quote; // quote & 1 -> isquote | quote & 2 -> isquote_closed

}					t_arg;
typedef struct		s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;
	char			*name;
	t_arg			*av_in;
	t_arg			*av;
	t_arg			*av_out;
	int				fd_out;
	int				fd_in;
	int				link;
	int				quote; // quote & 1 -> isquote | quote & 2 -> isquote_closed
}					t_cmd;
extern t_cmd		*g_exp;
extern t_cmd		*g_last_cmd;
extern t_cmd		*g_last_arg;
extern int			g_needling;
#endif
