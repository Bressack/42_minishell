/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:08:38 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/03 17:28:29 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define INDEX ((i == 0) ? i : (i - 1))
# define RULES 6
# define ESCAPMENT "\\"
# define STANDARD " \t\n"
# define FRAME "\"\'"
# define SEPARATOR ";&"
# define REDIRECTOR "<>|"

# include "libft.h"

typedef enum		e_vstate
{
	InSynError = -2,
	InLexError = -1,
	Standard,
	InEscapment,
	InFrame,
	InIdentifier,
	InSeparator,
	InRedirector
}					t_vstate;

typedef enum		e_type
{
	None,
	Escapment,
	Frame,
	Identifier,
	Separator,
	Redirector
}					t_type;

typedef struct		s_state
{
	t_vstate		old;
	t_vstate		curr;
}					t_state;

typedef struct		s_token
{
	t_type			type;
	char			*value;
}					t_token;

typedef struct		s_lexer
{
	t_list			*tokenlst;
	int				err;
	int				err_index;
	t_type			err_type;
}					t_lexer;

typedef t_vstate (*t_func)(char *, int);

t_lexer				*str_lex(char *str);
int					maj_tokenlst(t_list **atokenlst, t_state state, char *str, int i);

void				init_rules_tab(t_func *rules_tab);
void				destroy_tokenlst(t_list **atokenlst);
void				destroy_lexed(t_lexer **lexed);

t_vstate			rules_standard(char *str, int i);
t_vstate			rules_frame(char *str, int i);
t_vstate			rules_escapment(char *str, int i);
t_vstate			rules_identifier(char *str, int i);
t_vstate			rules_separator(char *str, int i);
t_vstate			rules_redirector(char *str, int i);

#endif
