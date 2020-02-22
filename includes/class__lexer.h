/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:09:08 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/21 15:41:09 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS__LEXER_H
# define CLASS__LEXER_H
# include <minishell.h>

# define PROMPT_CASUAL_STR "minishell"
# define PROMPT_SQUOTE_STR "quote"
# define PROMPT_DQUOTE_STR "dquote"
# define PROMPT_BSLASH_STR ""

typedef enum		e_debug
{
	DEBUG_PRINT_CHAR_TYPE,
	DEBUG_RET_CHAR_TYPE,
	DEBUG_POS,
	START,
	POS
}					t_debug;

typedef enum		e_prompt
{
	PROMPT_CASUAL,
	PROMPT_SQUOTE,
	PROMPT_DQUOTE,
	PROMPT_BSLASH
}					t_prompt;

typedef struct		s_lexer
{
	char			*line;
	int				len_line;
	int				start;
	int				pos;
	char			current_char;
	char			start_char;
}					t_lexer;
typedef enum		e_char_type
{
	CHR_ERR			= 0x0,
	CHR_EOT			= 0x1,
	CHR_SPACE		= 0x2,
	CHR_WORD		= 0x4,
	CHR_LPAREN		= 0x8,
	CHR_RPAREN		= 0x10,
	CHR_REDIREC_IN	= 0x20,
	CHR_REDIREC_OUT	= 0x40,
	CHR_SQUOTE		= 0x80,
	CHR_DQUOTE		= 0x100,
	CHR_AND			= 0x200,
	CHR_PIPE		= 0x400,
	CHR_SEMICON		= 0x800,
	CHR_SLASH		= 0x1000,
	CHR_PASS		= 0x2000,
	CHR_DOLLAR		= 0x4000,
	CHR_BSLASH		= 0x8000,
	CHR_QUESMARK	= 0x10000,
	CHR_STAR		= 0x20000
}					t_char_type;
extern t_char_type	g_token_ascii_table[255];
char				*lexer__get_prompt(int prompt_type);
t_lexer				lexer__new(char *line);					// init the t_lexer struct needed by all metodes of the lexer class
void				lexer__error(t_lexer *lex);				// write errors message in the stdout
int					lexer__advance(t_lexer *lex, int n);	// go to the next character in the line and checks potential errors
void				lexer__set_start_pos(t_lexer *lex, int new_pos);
void				lexer__skip_whitespace(t_lexer *lex);	// skip all whitespaces listed by the grammar from line
t_token				lexer__get_next_token(t_lexer *lex);	// get the next token from line and return it into a token node
int					lexer__istype(char c, t_char_type type);
t_token				lexer__get_word_token(t_lexer *lex);
t_token				lexer__get_defined_token(t_token_type type);
int					lexer__isdefined_token(t_lexer *lex);
t_token				lexer__search_defined_token(t_lexer *lex);

char				*lexer__debug(t_lexer *lex, int lever, int opt);
#endif
