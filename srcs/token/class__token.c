/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 08:22:11 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/12 18:09:42 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token			*token__new(t_token_type_m type, char *value, int pos)
{
	t_token		*new;

	new = mmalloc(sizeof(t_token));
	new->type = type;
	new->pos_in_line = pos;
	new->value = value;
	new->len = 0;
	if (value)
		new->len = ft_strlen(value);
	return (new);
}

t_token			*token__copy(t_token *token)
{
	t_token		*new;

	new = mmalloc(sizeof(t_token));
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
		mfree((void **)&(*token)->value);
		mfree((void **)token);
	}
}

void			token__list_del(t_token **token)
{
	t_token		*tmp;
	t_token		*tmpnext;

	tmp = *token;
	while (tmp)
	{
		tmpnext = tmp->next;
		token__del(&tmp);
		tmp = tmpnext;
	}
}

int				token__isparen(t_token *token)
{
	return (token__istype(token, LPAREN | RPAREN));
}
