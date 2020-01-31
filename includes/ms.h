/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:53:10 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/31 01:17:38 by tharchen         ###   ########.fr       */
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
typedef struct		s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*key;
	char			*value;
}					t_env;
extern t_env		*g_env;
extern t_cmd		*g_exp;
extern t_cmd		*g_last_cmd;
extern t_arg		*g_last_arg;
extern int			g_needling;
extern char			*g_line;
extern t_arg		*g_av_in;
extern t_arg		*g_av_out;
extern t_arg		*g_av;
extern int			g_ret_last_cmd;
extern char			*g_curr_dir;
void				preparser(int prompt);
void				parser__valid_char(int *i, int *j);
void				parser__quote(int *i, int *j);
void				parser(void);
void				preparser(int prompt);
void				__f__ft_del_node_np__t_arg__(t_pnp *a);
void				__f__ft_del_node_np__t_cmd__(t_pnp *a);
int					pass_quotes(int *i, int *j);
int					pass_space(int *i);
void				parser__special__pipe(void);
void				parser__special__dblrafters_right(void);
void				parser__special__rafters_right(void);
void				parser__special__rafters_left(void);
void				parser__special__colon(void);
# ifdef BONUS
void				parser__special__dbland(void);
void				parser__special__and(void);
void				parser__special__dblor(void);
void				parser__special__dblrafters_left(void);
# endif
void				parser__special(int *i, int *j);
int					ft_isspace(char c);
int					ft_isquote(char c);
int					ft_isspecial(char *s);
void				new_element(char *data, int type, ...);
void				debug_print_msg(char *f, int l, char *fmt, ...);
void				debug__print_data(void);
void				print_prompt(int select);
void				cmd_stop(int type);
#endif
