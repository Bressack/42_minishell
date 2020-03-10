/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   class__token__is.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 04:37:50 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/10 04:38:16 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int				token__istype(t_token *token, t_token_type_m type)
{
	return (type & token->type);
}

int				token__iseot(t_token *token)
{
	return (token__istype(token, EOT));
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
