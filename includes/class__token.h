/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__token.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:21:19 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/21 12:45:31 by tharchen         ###   ########.fr       */
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
	ERR,
	EOT,
	SPACE,
	PASS,
	WORD,
	SQUOTE,
	DQUOTE,
	LPAREN,
	RPAREN,
	REDIREC_IN,
	REDIREC_OUT,
	DREDIREC_OUT,
	DBL_AND,
	SGL_AND,
	DBL_OR,
	PIPE,
	SEMICON,
	BSLASH,
	QUESMARK,
	DOLLAR,
	SLASH,
	STAR,
	NONE
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
#endif
