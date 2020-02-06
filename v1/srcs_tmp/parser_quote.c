/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:02:20 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/01 13:57:37 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

void	parser__quote(int *i, int *j)
{
	char			*tmp;

	(*j) = (*i) + 1;
	while (1)
	{
		if (g_line[(*j)] == g_line[(*i)] && g_line[((*j) - 1)] != '\\')
			break ;
		if (g_line[(*j)] == '\0')
		{
			if (g_line[((*j) - 1)] != '\\')
			{
				tmp = ft_strjoin(2, g_line, "\n");
				try_free_((void **)&g_line, _FL_);
				g_line = tmp;
			}
			preparser(PROMPT_NEXT_NEEDED);
		}
		else
			(*j)++;
	}
	new_element(ft_strndup(&g_line[(*i + 1)], (*j) - (*i) - 1), g_needling, ISQUOTE,
		!g_line[(*j)] ? QUOTE_OPEN : QUOTE_CLOSE);
	(*j)++;
	pass_space(i);
}
