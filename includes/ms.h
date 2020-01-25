/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:53:10 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/25 20:56:36 by tharchen         ###   ########.fr       */
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

# define ISQUOTE		0
# define ISNOTQUOTE		1
# define QUOTE_OPEN		0
# define QUOTE_CLOSE	1

# define FD_STDOUT		0
# define FD_STDIN		1

# define SPECIAL_CHAR	"\\/><|:&"
# define LINK_SEMICON	0
# define LINK_PIPE___	1
# define LINK_AND____	2 // BONUS
# define LINK_OR_____	3 // BONUS
# define LINK_THREAD_	4 // BONUS

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
	t_arg			*av;
	int				fd_out;
	int				fd_in;
	int				link;
	int				quote; // quote & 1 -> isquote | quote & 2 -> isquote_closed
}					t_cmd;
#endif
