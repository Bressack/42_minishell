/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:53:10 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/29 23:01:07 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_H
# define MS_H
# include <double_linked.h>
# include <get_next_line.h>
# include <try_malloc.h>
# include <utils.h>
# include <color_shell.h>

# define SUCCESS	0
# define FAILURE	1

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

# define LINK_COLON	0
# define LINK_PIPE	1
# define LINK_AND	2 // BONUS
# define LINK_OR	3 // BONUS
# define LINK_THREAD	4 // BONUS

# define NOREDIR		0
# define REDIR_RIGHT	1
# define REDIR_DBLRIGHT	2
# define REDIR_LEFT		3
# define REDIR_DBLLEFT	4

# define OPEN__FLAG_O_CREAT__RIGHTS	0644

typedef struct		s_arg
{
	struct s_arg	*next;
	struct s_arg	*prev;
	char			*name;
	int				isquote;
	int				quote_state;
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
	int				open_flags;
	int				open_flags_rights;
	int				link;
	int				isquote;
	int				quote_state;
}					t_cmd;
extern t_cmd		*g_exp;
extern t_cmd		*g_last_cmd;
extern t_arg		*g_last_arg;
extern int			g_needling;
extern char			*g_line;
extern t_arg		*g_av_in;
extern t_arg		*g_av_out;
extern t_arg		*g_av;
void				preparser(int prompt);
#endif
