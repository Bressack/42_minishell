/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:02:20 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/30 16:11:46 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

void	parser__quote(int *i, int *j)
{
	(*j) = (*i) + 1;
	while (1)
	{
		if (g_line[(*j)] == '\0')
			break ;
		if (g_line[(*j) - 1] != '\\' && g_line[(*j)] == g_line[(*i)])
			break ;
		if (g_line[(*j)] == '\\')
			(*j) += 2;
		else
			(*j)++;
	}
	new_element(ft_strndup(&g_line[(*i)], (*j) - (*i)), g_needling, ISQUOTE,
		!g_line[(*j)] ? QUOTE_OPEN : QUOTE_CLOSE);
	pass_space(i);
}
