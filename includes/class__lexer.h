/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:09:08 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/24 23:57:57 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS__LEXER_H
# define CLASS__LEXER_H
# include <minishell.h>

# define PROMPT_CASUAL_STR "minishell"
# define PROMPT_SQUOTE_STR "quote"
# define PROMPT_DQUOTE_STR "dquote"
# define PROMPT_BSLASH_STR ""

typedef enum		e_foreach_opt
{
	WHILE_IS,
	WHILE_ISNOT
}					t_foreach_opt;
typedef enum		e_error_id
{
	UNEXPECTED_EOF,
	SGLAND_NOT_HANDLED
}					t_error_id;
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
	CHR_PASS		= 0x1000,
	CHR_DOLLAR		= 0x2000,
	CHR_BSLASH		= 0x4000,
	CHR_NONE		= 0x8000,
}					t_char_type;
extern t_char_type	g_token_ascii_table[255];

/*
** class__lexer.c
*/
void				print_prompt(int prompt_lever);
t_lexer				lexer__new(char *line);
void				lexer__error(int opt, t_lexer *lex);
int					lexer__istype(t_lexer *lex, t_char_type type);
char				*lexer__debug(t_lexer *lex, int lever, int opt);
void				lexer__set_start_pos(t_lexer *lex, int new_pos);
int					lexer__advance(t_lexer *lex, int n);
char				lexer__peek(t_lexer *lex);
void			lexer__advence_foreach(
t_lexer *lex, t_char_type type, int be_or_not_to_be);
void				lexer__refill_line(t_lexer *lex, int join_nl, int prompt);
void				lexer__get_word_quote_token(t_lexer *lex, t_char_type ct);
t_token				lexer__get_word_token(t_lexer *lex);

t_token				lexer__get_next_token(t_lexer *lex);
/*
** class__lexer__defined_tokens.c
*/
t_token				lexer__get_defined_token_with_index(int index);
t_token				lexer__get_defined_token(t_token_type type);
int					lexer__isdefined_token(t_lexer *lex);
t_token				lexer__search_defined_token(t_lexer *lex);
#endif
