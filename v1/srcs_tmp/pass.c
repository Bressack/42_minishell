/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:01:01 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/30 15:01:14 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

int					pass_quotes(int *i, int *j)
{
	while (g_line[*j] && ft_isquote(g_line[*j]))
		(*j)++;
	return (!g_line[*j] ? QUOTE_OPEN : QUOTE_CLOSE);
	(void)i;
}

int					pass_space(int *i)
{
	int				nb;

	nb = 0;
	while (ft_isspace(g_line[*i]) && ++nb)
		(*i)++;
	return (nb);
}
