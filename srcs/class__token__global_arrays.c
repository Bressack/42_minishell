/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__token__global_arrays.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 00:27:40 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/20 01:32:55 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** this array tag all ascii character with en kod used to group characters
** having the same sence (in our lexicon)
**
** to see tag given to the '#' character, do g_token_ascii_table['#'];
**
** /!\ g_token_ascii_table need an unsigned char index /!\
**
** ex:
**		unsigned char	c;
**
**		c = 'A';
**      if (g_token_ascii_table[c] == CHR_WORD)
**			return (SUCCESS);
**
** see also: class__token.h
**
*/
t_char_type			g_token_ascii_table[255] = // t_char_type aka int
{
	['\0']			= CHR_EOT,
	[0x01]			= CHR_EOT,
	/* *********************** */
	[128 ... 254]	= CHR_PASS,
	[0x02]			= CHR_PASS,
	[0x03]			= CHR_PASS,
	[0x04]			= CHR_PASS,
	[0x05]			= CHR_PASS,
	[0x06]			= CHR_PASS,
	['\a']			= CHR_PASS,
	['\b']			= CHR_PASS,
	[0x0e ... 0x1f]	= CHR_PASS,
	[0x7f]			= CHR_PASS,
	/* *********************** */
	['\t']			= CHR_SPACE,
	['\n']			= CHR_SPACE,
	['\v']			= CHR_SPACE,
	['\f']			= CHR_SPACE,
	['\r']			= CHR_SPACE,
	[' ']			= CHR_SPACE,
	/* *********************** */
	['\"']			= CHR_DQUOTE,
	['\'']			= CHR_SQUOTE,
	/* *********************** */
	['(']			= CHR_LPAREN,
	[')']			= CHR_RPAREN,
	/* *********************** */
	['&']			= CHR_AND,
	['|']			= CHR_PIPE,
	/* *********************** */
	['<']			= CHR_REDIREC_IN,
	['>']			= CHR_REDIREC_OUT,
	/* *********************** */
	['$']			= CHR_DOLLAR,
	['*']			= CHR_STAR,
	['?']			= CHR_QUESMARK,
	/* *********************** */
	[';']			= CHR_SEMICON,
	/* *********************** */
	['0' ... '9']	= CHR_WORD,
	['a' ... 'z']	= CHR_WORD,
	['A' ... 'Z']	= CHR_WORD,
	['!']			= CHR_WORD,
	['#']			= CHR_WORD,
	['%']			= CHR_WORD,
	['+']			= CHR_WORD,
	[',']			= CHR_WORD,
	['-']			= CHR_WORD,
	['.']			= CHR_WORD,
	[':']			= CHR_WORD,
	['=']			= CHR_WORD,
	['@']			= CHR_WORD,
	['[']			= CHR_WORD,
	[']']			= CHR_WORD,
	['^']			= CHR_WORD,
	['_']			= CHR_WORD,
	['`']			= CHR_WORD,
	['{']			= CHR_WORD,
	['}']			= CHR_WORD,
	['/']			= CHR_WORD,
	['~']			= CHR_WORD,
	['\\']			= CHR_WORD
};

/*
** this following array g_defined_tokens MUST to be sorted exactly
** like the enum e_token_type
** 'ERR' must be the first one och
** 'NONE' must be the last one
*/
t_token				g_defined_tokens[NB_DEFINED_TOKEN] =
{
	{ ERR          , ""   , 0, 0 },
	{ EOT          , ""   , 0, 0 },
	{ SPACE        , ""   , 0, 0 },
	{ PASS         , ""   , 0, 0 },
	{ WORD         , ""   , 0, 0 },
	{ SQUOTE       , "\'" , 1, 0 },
	{ DQUOTE       , "\"" , 1, 0 },
	/* ************************* */
	{ LPAREN       , "("  , 1, 0 },
	{ RPAREN       , ")"  , 1, 0 },
	{ REDIREC_IN   , "<"  , 1, 0 },
	{ REDIREC_OUT  , ">"  , 1, 0 },
	{ DREDIREC_OUT , ">>" , 2, 0 },
	{ DBL_AND      , "&&" , 2, 0 },
	{ DBL_OR       , "||" , 2, 0 },
	{ PIPE         , "|"  , 1, 0 },
	{ SEMICON      , ";"  , 1, 0 },
	{ BSLASH       , "\\" , 1, 0 },
	{ QUESMARK     , "?"  , 1, 0 },
	{ DOLLAR       , "$"  , 1, 0 },
	{ SLASH        , "/"  , 1, 0 },
	{ STAR         , "*"  , 1, 0 },
	{ NONE         , ""   , 0, 0 }
};
