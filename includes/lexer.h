/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 09:07:56 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/11 12:43:45 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define LPAREN		"("
# define RPAREN		")"
# define SEMICON	";"

typedef enum		e_token_type
{
	CHR_ERR = -1,
	CHR_UNKOWN = 0,
	CHR_WORD,
	CHR_DIGIT,
	CHR_SPACE,
	CHR_SPEC,
	CHR_FRAME
}					t_token_type;

int					char_table[255] =
{
	[ 'a' ... 'z' ] = CHR_WORD,
	[ 'A' ... 'Z' ] = CHR_WORD,
	[ '0' ... '9' ] = CHR_DIGIT,
	' '             = CHR_SPACE,
	'\t'            = CHR_SPACE,
	'>'             = CHR_SPEC,
	'<'             = CHR_SPEC,
	'|'             = CHR_SPEC,
	'&'             = CHR_SPEC,
	';'             = CHR_SPEC,
	'\''            = CHR_FRAME,
	'\"'            = CHR_FRAME,
};

char				*token_redir[6] =
{
	">",
	"<",
	">>",
	"<<",
	"|",
	NULL
};

char				*token_separator[4] =
{
	"||",
	"&&",
	";",
	NULL
};

char				*token_frame[4] =
{
	"\'",
	"\"",
	NULL
};

typedef struct		s_token
{
	struct s_token	next;
	struct s_token	prev;

	char			*value;
	int				len;
}					t_token;
#endif
