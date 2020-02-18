/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__token.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:21:19 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/18 16:44:14 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS__TOKEN_H
# define CLASS__TOKEN_H
# include <minishell.h>
typedef enum		e_token_type
{
	NONE = -1,
	ERR = 0,
	EOT,
	SPACE,
	WORD,
	LPAREN,
	RPAREN,
	REDIREC_IN,
	REDIREC_OUT,
	DREDIREC_OUT,
	SQUOTE,
	DQUOTE,
	DBL_AND,
	DBL_OR,
	PIPE,
	SEMICON,
	BSLASH,
	QUESMARK,
	DOLLAR,
	PASS,
	PATH,
	STAR
}					t_token_type;
typedef struct		s_token
{
	t_token_type	type;
	char			*value;
	int				len;
	int				pos_in_line;
}					t_token;
extern t_token		g_defined_tokens[20];
t_token				token__new(t_token_type type, char *value, int pos);
void				token__del(t_token token);
void				token__print(t_token token);
#endif
