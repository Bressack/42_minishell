/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_valid_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:02:49 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/01 11:49:23 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

void	parser__valid_char(int *i, int *j)
{
	(*j) = (*i) + 1;
	while (g_line[(*j)] && !ft_isspecial(&g_line[(*j)]) && !ft_isspace(g_line[(*j)]))
	{
		if (ft_isquote(g_line[(*j)]) && pass_quotes(i, j) == QUOTE_OPEN)
		{
			preparser(PROMPT_NEXT_NEEDED);
			break ;
		}
		else
			(*j)++;
	}
	new_element(ft_strndup(&g_line[*i], (*j) - (*i)), g_needling, ISNOTQUOTE,
		QUOTE_CLOSE);
	g_needling = ISARG;
	pass_space(i);
}
