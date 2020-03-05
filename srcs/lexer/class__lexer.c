/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:59:23 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/05 10:35:31 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** **************************************************************************
** **** lexer object handle *************************************************
** **************************************************************************
*/

t_lexer			*lexer__new(int sloc)
{
	t_lexer		*lex;

	lex = try_malloc(sizeof(t_lexer), _FL_);
	if (lexer__refill_line(lex, sloc, PROMPT_CASUAL) == ERROR)
	{
		lexer__del(&lex);
		return (NULL);
	}
	return (lex);
}

void			lexer__del(t_lexer **lex)
{
	if (*lex)
	{
		try_free_((void **)&(*lex)->line, _FL_);
		try_free_((void **)lex, _FL_);
	}
}

int				lexer__error(int opt, t_lexer *lex)
{
	if (opt == ERR_UNEXPECTED_EOT)
		ft_dprintf(2, "minishell: unexpected \'end of line\' after \'%c\'\n",
		lex->prev_char);
	else if (opt == ERR_SGLAND_NOT_HANDLED)
		ft_dprintf(2, "minishell: functionality not supported \'%c\'\n",
		lex->current_char);
	else if (opt == ERR_GNL)
	{
		ft_dprintf(2, "minishell: unable to read on stdout\n");
		exit(0); // if i put that here, I do like bash
	}
	else
		ft_dprintf(2, "minishell: invalid character \'%c\' (%#x)\n",
			lex->current_char, lex->current_char);
	return (ERROR);
}

/*
** **************************************************************************
** **** is something and peek ***********************************************
** **************************************************************************
*/

int				lexer__istype(t_lexer *lex, t_char_type type)
{
	return (type & g_token_ascii_table[(int)(lex->current_char)]);
}

int				lexer__istype_start(t_lexer *lex, t_char_type type)
{
	return (type & g_token_ascii_table[(int)(lex->start_char)]);
}

char			lexer__peek(t_lexer *lex)
{
	return (lex->line[lex->pos + 1]);
}

int				lexer__isword(t_lexer *lex)
{
	return (lexer__istype(lex, CHR_WORD | CHR_SQUOTE | CHR_DQUOTE |
		CHR_BSLASH));
}

int				lexer__isquote(t_lexer *lex)
{
	return (lexer__istype(lex, CHR_SQUOTE | CHR_DQUOTE));
}

/*
** **************************************************************************
** **** advance and pass function *******************************************
** **************************************************************************
*/

/*
** its the 'i++' of the lexer. lexer__advance try to advance the read head in
** line if the current character is already an EOT and return 0, otherwize,
** advance and return 1.
** it's a recurcive function, advance of 1 char and recall itself while n > 0 or
** current_char != EOT.
** PROTECTED: do not go throught the EOT
*/
int				lexer__advance(t_lexer *lex, int n)
{
	if (lex->current_char == CHR_EOT)
		return (0);
	lex->prev_char = lex->current_char;
	lex->pos += 1;
	if (lex->pos > lex->len_line - 1)
	{
		lex->current_char = CHR_EOT;
		return (0);
	}
	else
	{
		lex->current_char = lex->line[lex->pos];
		return (n - 1 > 0 ? lexer__advance(lex, n - 1) : 1);
	}
}

/*
** advance the read head while the current_char is of the same type as the
** variable 'type'
*/
void			lexer__advence_foreach(t_lexer *lex, t_char_type type, int whis)
{
	while (1)
	{
		if (lexer__istype(lex, CHR_BSLASH) && type == CHR_WORD)
			lexer__advance(lex, 1);
		else if (lexer__istype(lex, CHR_BSLASH) && (type == CHR_DQUOTE ||
			type == CHR_SQUOTE) && whis == WHILE_ISNOT)
			lexer__advance(lex, 1);
		if (!lexer__advance(lex, 1))
			break ;
		if (whis == WHILE_ISNOT ? lexer__istype(lex, type) : !lexer__istype(
			lex, type))
			break ;
	}
}

/*
** advance the read head until the current char is not the same quote as the
start of the function. e.g '"' will go to the next '"' and ''' go to the
next '''.
*/
int			lexer__pass_quotes(t_lexer *lex, t_char_type type)
{
	int			found;

	found = 0;
	lexer__advance(lex, 1);
	while (!lexer__istype(lex, type))
	{
		if (lexer__istype(lex, CHR_BSLASH))
			lexer__advance(lex, 1);
		if (!lexer__advance(lex, 1))
			break ;
	}
	if (!lexer__istype(lex, type) &&
		lexer__error(ERR_UNEXPECTED_EOT, lex) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

/*
** **************************************************************************
** **** set and init ********************************************************
** **************************************************************************
*/

void			lexer__set_start_pos(t_lexer *lex, int new_pos)
{
	lex->start = new_pos;
	lex->start_char = lex->line[new_pos];
}

/*
** **************************************************************************
** **** body functions ******************************************************
** **************************************************************************
*/

int				lexer__refill_line(t_lexer *lex, int sloc, int prompt)
{
	try_free_((void **)&lex->line, _FL_);
	print_prompt(sloc, prompt);
	if (get_next_line(0, &lex->line) == -1 &&
		lexer__error(ERR_GNL, lex) == ERROR)
		return (ERROR);
	if (!lex->line)
		return (ERROR);
	lex->pos = 0;
	lex->start = 0;
	lex->len_line = ft_strlen(lex->line);
	lex->current_char = lex->line[lex->pos];
	lex->start_char = lex->line[lex->start];
	return (SUCCESS);
}

/*
** just return the word token just found in lexer__get_next_token. The token
** start at 'start_pos' included until 'pos' excluded (variable included in lex)
*/
t_token			*lexer__token_grabber(t_lexer *lex, t_token_type_m type)
{
	t_token		*new;

	new = token__new(type, ft_strsub(lex->line, lex->start, lex->pos - lex->start),
		lex->start);
	return (new);
}

/*
** Ok then. I would tell you a story.
**
** When you take a call to get_next_token, this last will try to return the next
** token he can found on the line since the end posision of the last returned token
** or since the begining for the first call.
**
** First step, we want to pass all the nasty little spaces and ignored characters
** trying to pretend to be tokens ;)
**
** Second step, we send a short message to the lexer to ask him to reset the
** position of the variable start_pos to the current pos (just afters spaces and
** passed characters). start_pos is used to know the start position of the token we
** want to return.
**
** Third step, if we find a match with the defined token EOT, we return a copy
** of this token it.
**
** Fourth step, if we find a match with a defind token listed in the function
** lexer__isdefined_token in lexer__isdefined_tokens.c, we return a copy of this
** token it.
**
** Fifth step, here, we are trying to grab a word. A word is defined by a string
** of letters [a ... z], [A ... Z], numbers [0 ... 9], and listed specials
** characters. A backslash '\' "transform" the next character as a word
** character. The word ended when we found the end of the line or a defined token
** like '&&', '||', '|', ';', '<', '<<', '>' or '&' ('&' is not a valid token, for
** now, it's an error).
**
** Sixth step, just return the word token just found. the token start at
** 'start_pos' included until 'pos' excluded (variable included in lex)
*/

t_token			*lexer__get_next_token(t_lexer *lex) // NEEDS COMMENTS
{
	int			rtype;

	while (lexer__istype(lex, CHR_SPACE | CHR_PASS))
		lexer__advance(lex, 1);
	lexer__set_start_pos(lex, lex->pos);
	if (lexer__istype(lex, CHR_EOT))
		return (token__copy(&g_defined_tokens[I_EOT]));
	if ((rtype = lexer__isdefined_token(lex, ADVANCE)) != I_NONE)
		return (token__copy(&g_defined_tokens[rtype]));
	while (!lexer__istype(lex, CHR_EOT | CHR_SPACE | CHR_PASS | CHR_ERR))
	{
		if (lexer__istype(lex, CHR_BSLASH))
	 	{
			lexer__advance(lex, 1);
			if (lexer__istype(lex, CHR_EOT) &&
				lexer__error(ERR_UNEXPECTED_EOT, lex) == ERROR)
				return (NULL);

			lexer__advance(lex, 1);
		}
		if (lexer__isdefined_token(lex, NOADVANCE) != I_NONE)
			break ;
		if ((rtype = lexer__isquote(lex)))
			lexer__pass_quotes(lex, rtype);
		lexer__advance(lex, 1);
	}
	return (lexer__token_grabber(lex, WORD));
}
