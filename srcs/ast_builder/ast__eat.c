/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast__eat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 04:22:24 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/10 04:22:27 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		eat(t_astb *tool, t_token_type_m type)
{
	if (!token__istype(tool->current_token, type))
		return (astb_error(tool, UNEXPECTED_TOKEN));
	tool->prev_token = tool->current_token;
	if ((tool->current_token = lexer__get_next_token(tool->lex)) == NULL)
		return (ERROR);
	return (SUCCESS);
}
