/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:09:08 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/14 16:02:52 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS__LEXER_H
# define CLASS__LEXER_H
# include <class__token.h>

typedef struct		s_lexer
{
	char			*line;
	int				len_line;
	int				pos;
	char			current_char;
}					t_lexer;
typedef enum		e_char_type
{
	CHR_ERR				=	0x0,
	CHR_EOT				=	0x1,
	CHR_SPACE			=	0x2,
	CHR_WORD			=	0x4,
	CHR_LPAREN			=	0x8,
	CHR_RPAREN			=	0x10,
	CHR_REDIREC_IN		=	0x20,
	CHR_REDIREC_OUT		=	0x40,
	CHR_SQUOTE			=	0x80,
	CHR_DQUOTE			=	0x100,
	CHR_AND				=	0x200,
	CHR_PIPE			=	0x400,
	CHR_SEMICON			=	0x800,
	CHR_PATHSEP			=	0x1000
}					t_char_type;
t_char_type			g_token_ascii_table[255] = // t_char_type aka int
{
	[ '0' ... '9']		=	CHR_WORD,
	[ 'a' ... 'z']		=	CHR_WORD,
	[ 'A' ... 'Z']		=	CHR_WORD,
	['_']				=	CHR_WORD,
	['/']				=	CHR_PATHSEP,
	['<']				=	CHR_REDIREC_IN,
	['>']				=	CHR_REDIREC_OUT,
	['(']				=	CHR_LPAREN,
	[')']				=	CHR_RPAREN,
	['&']				=	CHR_AND,
	['|']				=	CHR_PIPE,
	[' ']				=	CHR_SPACE,
	['\t']				=	CHR_SPACE,
	['\'']				=	CHR_SQUOTE,
	['\"']				=	CHR_DQUOTE,
	[';']				=	CHR_SEMICON,
	[ 0 ]				=	CHR_EOT
};

t_lexer				lexer__init(char *line);				// init the t_lexer struct needed by all metodes of the lexer class
void				lexer__error(t_lexer *lex);				// write errors message in the stdout
int					lexer__advance(t_lexer *lex);			// go to the next character in the line and checks potential errors
void				lexer__skip_whitespace(t_lexer *lex);	// skip all whitespaces listed by the grammar from line
t_token				lexer__get_next_token(t_lexer *lex);	// get the next token from line and return it into a token node
#endif
