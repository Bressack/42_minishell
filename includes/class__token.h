/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__token.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:21:19 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/22 14:50:16 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS__TOKEN_H
# define CLASS__TOKEN_H
# include <minishell.h>

# define NB_DEFINED_TOKEN 23
/*
** this following enum e_token_type MUST to be sorted exactly like the
** global array g_defined_tokens
** 'ERR' must be the first one och
** 'NONE' must be the last one
*/
typedef enum		e_token_type
{
	ERR				= 0x0 ,
	EOT				= 0x1 ,
	SPACE			= 0x2 ,
	PASS			= 0x4 ,
	WORD			= 0x8 ,
	SQUOTE			= 0x10 ,
	DQUOTE			= 0x20 ,
	LPAREN			= 0x40 ,
	RPAREN			= 0x80 ,
	REDIREC_IN		= 0x100 ,
	REDIREC_OUT		= 0x200 ,
	DREDIREC_OUT	= 0x400 ,
	DBL_AND			= 0x800 ,
	SGL_AND			= 0x1000 ,
	DBL_OR			= 0x2000 ,
	PIPE			= 0x4000 ,
	SEMICON			= 0x8000 ,
	BSLASH			= 0x10000 ,
	QUESMARK		= 0x20000 ,
	DOLLAR			= 0x40000 ,
	SLASH			= 0x80000 ,
	STAR			= 0x100000 ,
	NONE			= 0x200000
}					t_token_type;
typedef struct		s_token
{
	t_token_type	type;
	char			value[LINE_MAX];
	int				len;
	int				pos_in_line;
	int				isunique;
}					t_token;
extern t_token		g_defined_tokens[NB_DEFINED_TOKEN];
t_token				token__new(t_token_type type, char *value, int pos);
void				token__del(t_token token);
void				token__print(t_token token);
int					token__istype(t_token token, t_token_type type);
#endif
