/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__token__global_arrays.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 00:27:40 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/12 18:15:33 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** this array tag all ascii character with en kod used to group characters
** having the same sence (in our lexicon)
*/

t_char_type			g_token_ascii_table[255] =
{
	['\0'] = CHR_EOT,
	[0x01] = CHR_EOT,
	[128 ... 254] = CHR_PASS,
	[0x02] = CHR_PASS,
	[0x03] = CHR_PASS,
	[0x04] = CHR_PASS,
	[0x05] = CHR_PASS,
	[0x06] = CHR_PASS,
	['\a'] = CHR_PASS,
	['\b'] = CHR_PASS,
	[0x0e ... 0x1f] = CHR_PASS,
	[0x7f] = CHR_PASS,
	['\t'] = CHR_SPACE,
	['\n'] = CHR_SPACE,
	['\v'] = CHR_SPACE,
	['\f'] = CHR_SPACE,
	['\r'] = CHR_SPACE,
	[' '] = CHR_SPACE,
	['\"'] = CHR_DQUOTE,
	['\''] = CHR_SQUOTE,
	['('] = CHR_LPAREN,
	[')'] = CHR_RPAREN,
	['&'] = CHR_AND,
	['|'] = CHR_PIPE,
	['<'] = CHR_REDIREC_IN,
	['>'] = CHR_REDIREC_OUT,
	['$'] = CHR_DOLLAR,
	['*'] = CHR_WORD,
	['?'] = CHR_WORD,
	[';'] = CHR_SEMICON,
	['0' ... '9'] = CHR_WORD,
	['a' ... 'z'] = CHR_WORD,
	['A' ... 'Z'] = CHR_WORD,
	['!'] = CHR_WORD,
	['#'] = CHR_WORD,
	['%'] = CHR_WORD,
	['+'] = CHR_WORD,
	[','] = CHR_WORD,
	['-'] = CHR_WORD,
	['.'] = CHR_WORD,
	[':'] = CHR_WORD,
	['='] = CHR_WORD,
	['@'] = CHR_WORD,
	['['] = CHR_WORD,
	[']'] = CHR_WORD,
	['^'] = CHR_WORD,
	['_'] = CHR_WORD,
	['`'] = CHR_WORD,
	['{'] = CHR_WORD,
	['}'] = CHR_WORD,
	['/'] = CHR_WORD,
	['~'] = CHR_WORD,
	['\\'] = CHR_BSLASH
};

/*
** this following array g_defined_tokens MUST to be sorted exactly
** like the enum e_token_type
** 'ERR' must be the first one och
** 'NONE' must be the last one
*/

t_token				g_defined_tokens[NB_DEFINED_TOKEN] =
{
	{NULL, NULL, ERR, "", 0, 0},
	{NULL, NULL, EOT, "", 0, 0},
	{NULL, NULL, SPACE, "", 0, 0},
	{NULL, NULL, PASS, "", 0, 0},
	{NULL, NULL, WORD, "", 0, 0},
	{NULL, NULL, SQUOTE, "\'", 1, 0},
	{NULL, NULL, DQUOTE, "\"", 1, 0},
	{NULL, NULL, LPAREN, "(", 1, 0},
	{NULL, NULL, RPAREN, ")", 1, 0},
	{NULL, NULL, REDIR_IN, "<", 1, 0},
	{NULL, NULL, REDIR_OUT, ">", 1, 0},
	{NULL, NULL, DREDIR_OUT, ">>", 2, 0},
	{NULL, NULL, DBL_AND, "&&", 2, 0},
	{NULL, NULL, DBL_OR, "||", 2, 0},
	{NULL, NULL, PIPE, "|", 1, 0},
	{NULL, NULL, SEMICON, ";", 1, 0},
	{NULL, NULL, BSLASH, "/", 1, 0},
	{NULL, NULL, DOLLAR, "$", 1, 0},
	{NULL, NULL, NONE, "", 0, 0}
};

t_token_str			g_token_str[NB_DEFINED_TOKEN] =
{
	{ERR, "ERR"},
	{EOT, "EOT"},
	{SPACE, "SPACE"},
	{PASS, "PASS"},
	{WORD, "WORD"},
	{SQUOTE, "SQUOTE"},
	{DQUOTE, "DQUOTE"},
	{LPAREN, "LPAREN"},
	{RPAREN, "RPAREN"},
	{REDIR_IN, "REDIR_IN"},
	{REDIR_OUT, "REDIR_OUT"},
	{DREDIR_OUT, "DREDIR_OUT"},
	{DBL_AND, "DBL_AND"},
	{DBL_OR, "DBL_OR"},
	{PIPE, "PIPE"},
	{SEMICON, "SEMICON"},
	{BSLASH, "BSLASH"},
	{DOLLAR, "DOLLAR"},
	{NONE, "NONE"}
};

t_assign_id_idx		g_assign_id_idx[NB_DEFINED_TOKEN] =
{
	{ERR, I_ERR},
	{EOT, I_EOT},
	{SPACE, I_SPACE},
	{PASS, I_PASS},
	{WORD, I_WORD},
	{SQUOTE, I_SQUOTE},
	{DQUOTE, I_DQUOTE},
	{LPAREN, I_LPAREN},
	{RPAREN, I_RPAREN},
	{REDIR_IN, I_REDIREC_IN},
	{REDIR_OUT, I_REDIREC_OUT},
	{DREDIR_OUT, I_DREDIREC_OUT},
	{DBL_AND, I_DBL_AND},
	{DBL_OR, I_DBL_OR},
	{PIPE, I_PIPE},
	{SEMICON, I_SEMICON},
	{BSLASH, I_BSLASH},
	{DOLLAR, I_DOLLAR},
	{NONE, I_NONE}
};
