/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 08:22:11 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/29 05:39:47 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token			*token__new(t_token_type_m type, char *value, int pos)
{
	t_token		*new;

	new = try_malloc(sizeof(t_token), _FL_);
	new->type = type;
	new->pos_in_line = pos;
	new->value = value; // value can come from a strdup, strsub, etc.
	new->len = 0;
	if (value)
		new->len = ft_strlen(value);
	return (new);
}

t_token			*token__copy(t_token *token) // use this function on defined token. e.g. token__copy(g_defined_tokens[I_WORD])
{
	t_token		*new;

	new = try_malloc(sizeof(t_token), _FL_);
	new->type = token->type;
	new->pos_in_line = token->pos_in_line;
	new->value = ft_strdup(token->value);
	new->len = token->len;
	return (new);
}

void			token__del(t_token **token)
{
	if (*token)
	{
		try_free_((void **)&(*token)->value, _FL_); // free the memory of value
		try_free_((void **)token, _FL_); // free the token
	}
}


int				token__istype(t_token *token, t_token_type_m type)
{
	return (type & token->type);
}

int				token__isword(t_token *token)
{
	return (token__istype(token, WORD));
}

int				token__issep(t_token *token)
{
	return (token__istype(token, SEMICON | DBL_AND | DBL_OR | PIPE));
}

int				token__isredir(t_token *token)
{
	return (token__istype(token, REDIR_IN | REDIR_OUT | DREDIR_OUT));
}

int				token__isparen(t_token *token)
{
	return (token__istype(token, LPAREN | RPAREN));
}

void			token__print(t_token *t) // for debug
{
	printf("[ %s ] --- ", t->value);
	if (t->type == ERR)
	{
		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"ERR         "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
		exit(-1);
	 }
	else if (t->type == EOT)			printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"EOT         "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else if (t->type == SPACE)			printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"SPACE       "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else if (t->type == WORD)			printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"WORD        "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else if (t->type == LPAREN)			printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"LPAREN      "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else if (t->type == RPAREN)			printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"RPAREN      "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else if (t->type == REDIR_IN)		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"REDIR_IN  "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else if (t->type == REDIR_OUT)	printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"REDIR_OUT "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else if (t->type == DREDIR_OUT)	printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"DREDIR_OUT"C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else if (t->type == SQUOTE)			printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"SQUOTE      "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else if (t->type == DQUOTE)			printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"DQUOTE      "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else if (t->type == DBL_AND)		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"DBL_AND     "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else if (t->type == DBL_OR)			printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"DBL_OR      "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else if (t->type == PIPE)			printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"PIPE        "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else if (t->type == SEMICON)		printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"SEMICON     "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else if (t->type == BSLASH)			printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"BSLASH      "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else if (t->type == DOLLAR)			printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"DOLLAR      "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else if (t->type == PASS)			printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"PASS        "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
	else                                printf("[ "C_G_GREEN"TOKEN"C_RES" ] { "C_G_CYAN"type:"C_RES" "C_G_MAGENTA"NONE        "C_RES" } { "C_G_CYAN"value:"C_RES" ["C_G_MAGENTA"%s"C_RES"] }\n", t->value);
}
