/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defined_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:55:50 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/15 15:36:12 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_char_type			g_token_ascii_table[255] = // t_char_type aka int
{
	[ '0' ... '9']	=	CHR_WORD,
	[ 'a' ... 'z']	=	CHR_WORD,
	[ 'A' ... 'Z']	=	CHR_WORD,
	['_']			=	CHR_WORD,
	['/']			=	CHR_PATHSEP,
	['<']			=	CHR_REDIREC_IN,
	['>']			=	CHR_REDIREC_OUT,
	['(']			=	CHR_LPAREN,
	[')']			=	CHR_RPAREN,
	['&']			=	CHR_AND,
	['|']			=	CHR_PIPE,
	[' ']			=	CHR_SPACE,
	['\t']			=	CHR_SPACE,
	['\'']			=	CHR_SQUOTE,
	['\"']			=	CHR_DQUOTE,
	[';']			=	CHR_SEMICON,
	[ 0 ]			=	CHR_EOT
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
	{SQUOTE,		"\'",	1, 0},
	{DQUOTE,		"\"",	1, 0},
	{NONE,			NULL,	0, 0}
};
