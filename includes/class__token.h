/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__token.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:21:19 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/27 14:29:49 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS__TOKEN_H
# define CLASS__TOKEN_H
# include <minishell.h>

# define NB_DEFINED_TOKEN 19
/*
** this following enum e_token_type MUST to be sorted exactly like the
** global array g_defined_tokens
** 'ERR' must be the first one och
** 'NONE' must be the last one
*/
typedef enum			e_token_type_m
{
	ERR					= 0x0,
	EOT					= 0x1,
	SPACE				= 0x2,
	PASS				= 0x4,
	WORD				= 0x8,
	SQUOTE				= 0x10,
	DQUOTE				= 0x20,
	LPAREN				= 0x40,
	RPAREN				= 0x80,
	REDIREC_IN			= 0x100,
	REDIREC_OUT			= 0x200,
	DREDIREC_OUT		= 0x400,
	DBL_AND				= 0x800,
	DBL_OR				= 0x2000,
	PIPE				= 0x4000,
	SEMICON				= 0x8000,
	BSLASH				= 0x10000,
	DOLLAR				= 0x40000,
	NONE				= 0x200000
}						t_token_type_m;

typedef enum			e_token_type
{
	I_ERR, // 0
	I_EOT, // 1
	I_SPACE, // 2
	I_PASS,
	I_WORD,
	I_SQUOTE,
	I_DQUOTE,
	I_LPAREN,
	I_RPAREN,
	I_REDIREC_IN,
	I_REDIREC_OUT, // 10
	I_DREDIREC_OUT,
	I_DBL_AND,
	I_DBL_OR,
	I_PIPE,
	I_SEMICON,
	I_BSLASH,
	I_DOLLAR,
	I_NONE // 19
}						t_token_type;
typedef struct			s_token
{
	struct s_token		*next;
	struct s_token		*prev;
	t_token_type_m		type;
	char				*value;
	int					len;
	int					pos_in_line;
}						t_token;
typedef struct			s_token_str
{
	t_token_type_m		type;
	char				str[20];
}						t_token_str;
typedef struct			s_assign_id_idx
{
	t_token_type_m		mask;
	t_token_type		idx;
}						t_assign_id_idx;
extern t_token			g_defined_tokens[NB_DEFINED_TOKEN];
extern t_token_str		g_token_str[NB_DEFINED_TOKEN];
extern t_assign_id_idx	g_assign_id_idx[NB_DEFINED_TOKEN];
t_token					*token__new(t_token_type_m type, char *value, int pos);
t_token					*token__copy(t_token *token);
void					token__del(t_token **token);
int						token__istype(t_token *token, t_token_type_m type);
void					token__print(t_token *t);
#endif
