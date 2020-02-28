/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:09:08 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/28 01:26:33 by tharchen         ###   ########.fr       */
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
	WHILE_ISNOT,
	ADVANCE,
	NOADVANCE
}					t_foreach_opt;
typedef enum		e_error_id
{
	UNEXPECTED_EOT,
	SGLAND_NOT_HANDLED,
	ERR_GNL
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

void				print_prompt(int sloc, int prompt_lever);
/*
** **************************************************************************
** **** lexer object handle *************************************************
** **************************************************************************
*/
t_lexer				*lexer__new(int sloc);
void				lexer__del(t_lexer **lex);
void				lexer__error(int opt, t_lexer *lex);
/*
** **************************************************************************
** **** is something and peek ***********************************************
** **************************************************************************
*/
int					lexer__istype(t_lexer *lex, t_char_type type);
int					lexer__istype_start(t_lexer *lex, t_char_type type);
char				lexer__peek(t_lexer *lex);
int					lexer__isword(t_lexer *lex);
int					lexer__isquote(t_lexer *lex);
int					lexer__isdefined_token(t_lexer *lex, int adv);
/*
** **************************************************************************
** **** advance and pass function *******************************************
** **************************************************************************
*/
int					lexer__advance(t_lexer *lex, int n);
void				lexer__advence_foreach(t_lexer *lex, t_char_type type, int whis);
void				lexer__pass_quotes(t_lexer *lex, t_char_type type);
/*
** **************************************************************************
** **** set and init ********************************************************
** **************************************************************************
*/
void				lexer__set_start_pos(t_lexer *lex, int new_pos);
/*
** **************************************************************************
** **** body functions ******************************************************
** **************************************************************************
*/
void				lexer__refill_line(t_lexer *lex, int sloc, int prompt);
t_token				*lexer__token_grabber(t_lexer *lex, t_token_type_m type);
t_token				*lexer__get_next_token(t_lexer *lex);
#endif
