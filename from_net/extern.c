/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:13:51 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/03 17:15:04 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void   init_rules_tab(t_func *rules_tab)
{
	rules_tab[Standard] = rules_standard;
	rules_tab[InFrame] = rules_frame;
	rules_tab[InEscapment] = rules_escapment;
	rules_tab[InIdentifier] = rules_identifier;
	rules_tab[InSeparator] = rules_separator;
	rules_tab[InRedirector] = rules_redirector;
}

void   destroy_tokenlst(t_list **atokenlst)
{
	t_list  *tmp;

	while (*atokenlst != NULL)
	{
		tmp = (*atokenlst)->next;
		free(((t_token *)(*atokenlst)->content)->value);
		((t_token *)(*atokenlst)->content)->value = NULL;
		free((*atokenlst)->content);
		(*atokenlst)->content = NULL;
		free(*atokenlst);
		(*atokenlst) = tmp;
	}
}

void   destroy_lexed(t_lexer **alexed)
{
	destroy_tokenlst(&((*alexed)->tokenlst));
	free(*alexed);
	(*alexed) = NULL;
}
