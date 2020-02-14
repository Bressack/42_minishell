/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__token.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:21:19 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/14 17:57:04 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS__TOKEN_H
# define CLASS__TOKEN_H
typedef enum		e_token_type
{
	ERR				=	0x0,
	EOT				=	0x1,
	SPACE			=	0x2,
	WORD			=	0x4,
	LPAREN			=	0x8,
	RPAREN			=	0x10,
	REDIREC_IN		=	0x20,
	REDIREC_OUT		=	0x40,
	DREDIREC_OUT	=	0x80,
	SQUOTE			=	0x100,
	DQUOTE			=	0x200,
	DBL_AND			=	0x400,
	DBL_OR			=	0x800,
	PIPE			=	0x1000,
	SEMICON			=	0x2000
}					t_token_type;
typedef struct		s_hshtbl
{
	char			*str;
	t_token_type	*type;
	int				hash;
}					t_hshtbl;
typedef struct		s_token
{
	t_token_type	type;
	char			*value;
	int				len;
	int				pos_in_line;
}					t_token;
t_token				token__init(t_token_type type, int value);
void				token__print(t_token token);
#endif
