/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:09:08 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/15 17:55:32 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS__LEXER_H
# define CLASS__LEXER_H
# include <minishell.h>

typedef struct		s_lexer
{
	char			*line;
	int				len_line;
	int				pos;
	char			current_char;
}					t_lexer;
typedef enum		e_char_type
{
	CHR_ERR = 0,
	CHR_EOT,
	CHR_SPACE,
	CHR_WORD,
	CHR_LPAREN,
	CHR_RPAREN,
	CHR_REDIREC_IN,
	CHR_REDIREC_OUT,
	CHR_SQUOTE,
	CHR_DQUOTE,
	CHR_AND,
	CHR_PIPE,
	CHR_SEMICON,
	CHR_PATHSEP
}					t_char_type;
extern t_char_type	g_token_ascii_table[255];
t_lexer				lexer__new(char *line);					// init the t_lexer struct needed by all metodes of the lexer class
void				lexer__error(t_lexer *lex);				// write errors message in the stdout
int					lexer__advance(t_lexer *lex);			// go to the next character in the line and checks potential errors
void				lexer__skip_whitespace(t_lexer *lex);	// skip all whitespaces listed by the grammar from line
t_token				lexer__get_next_token(t_lexer *lex);	// get the next token from line and return it into a token node
#endif