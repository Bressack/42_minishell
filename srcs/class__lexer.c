/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:59:23 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/16 16:13:43 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lexer				lexer__new(char *line)
{
	t_lexer			lex;

	lex.line = line; // not a duplicated str (if line is freed, lex.line will be freed too)
	lex.len_line = ft_strlen(line);
	lex.pos = 0;
	lex.current_char = lex.line[lex.pos];
	return (lex);
}

void				lexer__error(t_lexer *lex)
{
	printf("Invalid character \'%c\' (%#x)\n",
		lex->current_char, lex->current_char);
}

int					lexer__istype(char c, t_char_type type)
{
	return (g_token_ascii_table[(int)c] == type ? 1 : 0);
}

int					lexer__advance(t_lexer *lex)
{
	printf("advance { from \'"C_G_CYAN"%c"C_RES"\' ("C_G_MAGENTA"%3d"C_RES") at pos "C_G_YELLOW"%d"C_RES" } -> ", lex->current_char, lex->current_char, lex->pos);
	if (lex->current_char == CHR_EOT)
	{
		printf("{ already on "C_G_RED"EOT"C_RES" }\n");
		getchar();
		return (0);
	}
	lex->pos += 1;
	if (lex->pos > lex->len_line - 1)
	{
		lex->current_char = CHR_EOT;
		printf("{ to \'"C_G_CYAN"%c"C_RES"\' ("C_G_MAGENTA"%3d"C_RES") at pos "C_G_YELLOW"%d"C_RES" }\n", lex->current_char, lex->current_char, lex->pos);
		getchar();
		return (0);
	}
	else
	{
		lex->current_char = lex->line[lex->pos];
		printf("{ to \'"C_G_CYAN"%c"C_RES"\' ("C_G_MAGENTA"%3d"C_RES") at pos "C_G_YELLOW"%d"C_RES" }\n", lex->current_char, lex->current_char, lex->pos);
		getchar();
		return (1);
	}
}

void				lexer__skip_whitespace(t_lexer *lex)
{
	while (lexer__istype(lex->current_char, CHR_SPACE) ||
		lexer__istype(lex->current_char, CHR_PASS))
		lexer__advance(lex);
}

t_token				lexer__get_defined_token(t_token_type type)
{
	int				i;

	i = 0;
	while (g_defined_tokens[i].type != NONE && g_defined_tokens[i].type != type)
		i++;
	return (g_defined_tokens[i]);
}

t_token				lexer__get_word_token(t_lexer *lex)
{
	t_token			new;
	int				start_pos;

	start_pos = lex->pos;
	while (	lexer__istype(lex->current_char, CHR_WORD)		||
			lexer__istype(lex->current_char, CHR_BSLASH)	||
			lexer__istype(lex->current_char, CHR_SQUOTE)	||
			lexer__istype(lex->current_char, CHR_DQUOTE))
	{
		if (lexer__istype(lex->current_char, CHR_SQUOTE))
		{
			lexer__advance(lex);
			while (!lexer__istype(lex->current_char, CHR_SQUOTE) && lexer__advance(lex))
				continue ;
		}
		if (lexer__istype(lex->current_char, CHR_DQUOTE))
		{
			lexer__advance(lex);
			while (!lexer__istype(lex->current_char, CHR_DQUOTE) && lexer__advance(lex))
				continue ;
		}
		if (lexer__istype(lex->current_char, CHR_BSLASH))
			lexer__advance(lex);
		lexer__advance(lex);
	}
	new.type = WORD;
	new.len = lex->pos - start_pos;
	new.pos_in_line = start_pos;
	new.value = ft_strsub(lex->line, start_pos, new.len); // malloc = free needed;
	return (new);
}

t_token				lexer__search_defined_token(t_lexer *lex)
{
	int				i;
	int				j_max;
	int				i_max;

	i_max = -1;	// i save
	j_max = -1;	// j save
	i = -1;
	while (g_defined_tokens[++i].type != NONE) // until the end of the array
	{
		if (g_defined_tokens[i].value == NULL)
			continue ; // ERR or EOT
		if (j_max > 0 && g_defined_tokens[i].len < g_defined_tokens[j_max].len)
			continue ; // avoid useless calcules cause g_defined_tokens[i] can't match more than g_defined_tokens[j_max]
		if (!ft_strncmp(g_defined_tokens[i].value, &lex->line[lex->pos], g_defined_tokens[i].len))
		{
			if (j_max <= g_defined_tokens[i].len)
			{
				j_max = g_defined_tokens[i].len;
				i_max = i;
			}
		}
	}
	if (i_max == -1)
		return (lexer__get_defined_token(ERR));
	i = -1;
	while (++i < g_defined_tokens[i_max].len)
		lexer__advance(lex);
	return (g_defined_tokens[i_max]); // if the while statement has found a corresponding token in the table, then return it
}

t_token				lexer__get_next_token(t_lexer *lex)
{
	/* ****************************
	printf("[ %d ]", lex->pos);
	printf("enter lexer__get_next_token\n");
	printf("%s\n", lex->line);
	printf("%*s\n", lex->pos + 1, "^");
	     if (lexer__istype(lex->current_char, CHR_ERR))			printf("type: CHR_ERR        \n");
	else if (lexer__istype(lex->current_char, CHR_EOT))			printf("type: CHR_EOT        \n");
	else if (lexer__istype(lex->current_char, CHR_SPACE))		printf("type: CHR_SPACE      \n");
	else if (lexer__istype(lex->current_char, CHR_WORD))		printf("type: CHR_WORD       \n");
	else if (lexer__istype(lex->current_char, CHR_LPAREN))		printf("type: CHR_LPAREN     \n");
	else if (lexer__istype(lex->current_char, CHR_RPAREN))		printf("type: CHR_RPAREN     \n");
	else if (lexer__istype(lex->current_char, CHR_REDIREC_IN))	printf("type: CHR_REDIREC_IN \n");
	else if (lexer__istype(lex->current_char, CHR_REDIREC_OUT))	printf("type: CHR_REDIREC_OUT\n");
	else if (lexer__istype(lex->current_char, CHR_SQUOTE))		printf("type: CHR_SQUOTE     \n");
	else if (lexer__istype(lex->current_char, CHR_DQUOTE))		printf("type: CHR_DQUOTE     \n");
	else if (lexer__istype(lex->current_char, CHR_AND))			printf("type: CHR_AND        \n");
	else if (lexer__istype(lex->current_char, CHR_PIPE))		printf("type: CHR_PIPE       \n");
	else if (lexer__istype(lex->current_char, CHR_SEMICON))		printf("type: CHR_SEMICON    \n");
	else if (lexer__istype(lex->current_char, CHR_PATHSEP))		printf("type: CHR_PATHSEP    \n");
	printf("\n");
**************************** */

	if (lexer__istype(lex->current_char, CHR_SPACE) ||
		lexer__istype(lex->current_char, CHR_PASS))
		lexer__skip_whitespace(lex);
	else if (lexer__istype(lex->current_char, CHR_EOT))
		return (lexer__get_defined_token(EOT));
	else if (lexer__istype(lex->current_char, CHR_WORD))
		return (lexer__get_word_token(lex));
	else if (lexer__istype(lex->current_char, CHR_ERR))
	{
		lexer__error(lex);
		return (lexer__get_defined_token(ERR));
	}
	return (lexer__search_defined_token(lex));
	// else if (lexer__istype(lex->current_char, CHR_BSLASH))
	// return (lexer__get_word_token(lex));
}
