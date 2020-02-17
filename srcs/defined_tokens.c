/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defined_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:55:50 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/17 03:58:11 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_char_type			g_token_ascii_table[255] = // t_char_type aka int
{
	[128 ... 254]	= CHR_PASS,
	['\0']			= CHR_EOT,
	[0x01]			= CHR_EOT,
	[0x02]			= CHR_PASS,
	[0x03]			= CHR_PASS,
	[0x04]			= CHR_PASS,
	[0x05]			= CHR_PASS,
	[0x06]			= CHR_PASS,
	['\a']			= CHR_PASS,
	['\b']			= CHR_PASS,
	[0x0e ... 0x1f]	= CHR_PASS,
	[0x7f]			= CHR_PASS,
	['!']			= CHR_WORD,
	['#']			= CHR_WORD,
	['%']			= CHR_WORD,
	['+']			= CHR_WORD,
	[',']			= CHR_WORD,
	['-']			= CHR_WORD,
	['.']			= CHR_WORD,
	['0' ... '9']	= CHR_WORD,
	[':']			= CHR_WORD,
	['=']			= CHR_WORD,
	['@']			= CHR_WORD,
	['A' ... 'Z']	= CHR_WORD,
	['[']			= CHR_WORD,
	[']']			= CHR_WORD,
	['^']			= CHR_WORD,
	['_']			= CHR_WORD,
	['`']			= CHR_WORD,
	['a' ... 'z']	= CHR_WORD,
	['{']			= CHR_WORD,
	['}']			= CHR_WORD,
	['~']			= CHR_WORD,
	['\t']			= CHR_SPACE,
	['\n']			= CHR_SPACE,
	['\v']			= CHR_SPACE,
	['\f']			= CHR_SPACE,
	['\r']			= CHR_SPACE,
	[' ']			= CHR_SPACE,
	['\"']			= CHR_DQUOTE,
	['$']			= CHR_DOLLAR,
	['&']			= CHR_AND,
	['\'']			= CHR_SQUOTE,
	['(']			= CHR_LPAREN,
	[')']			= CHR_RPAREN,
	['*']			= CHR_STAR,
	['/']			= CHR_PATH,
	[';']			= CHR_SEMICON,
	['<']			= CHR_REDIREC_IN,
	['>']			= CHR_REDIREC_OUT,
	['?']			= CHR_QUESMARK,
	['\\']			= CHR_WORD,
	['|']			= CHR_PIPE
};

t_token				g_defined_tokens[20] =
{
	{ERR,			NULL,	0, 0},
	{EOT,			NULL,	0, 0},
	{DBL_AND,		"&&",	2, 0},
	{DBL_OR,		"||",	2, 0},
	{PIPE,			"|",	1, 0},
	{SEMICON,		";",	1, 0},
	{LPAREN,		"(",	1, 0},
	{RPAREN,		")",	1, 0},
	{REDIREC_IN,	"<",	1, 0},
	{REDIREC_OUT,	">",	1, 0},
	{DREDIREC_OUT,	">>",	2, 0},
	{STAR,			"*",	1, 0},
	{DOLLAR,		"$",	1, 0},
	{NONE,			NULL,	0, 0}
};
