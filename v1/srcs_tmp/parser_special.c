/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:49:44 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/30 14:57:41 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

#ifdef BONUS

void				parser__special(int *i, int *j)
{
	if (g_line[*i] == ';')
		parser__special__colon();
	else if (g_line[*i] == '&' && g_line[*i + 1] == '&')
		parser__special__dbland();
	else if (g_line[*i] == '&')
		parser__special__and();
	else if (g_line[*i] == '|' && g_line[*i + 1] == '|')
		parser__special__dblor();
	else if (g_line[*i] == '|')
		parser__special__pipe();
	else if (g_line[*i] == '>' && g_line[*i + 1] == '>')
		parser__special__dblrafters_right();
	else if (g_line[*i] == '<' && g_line[*i + 1] == '<')
		parser__special__dblrafters_left();
	else if (g_line[*i] == '>')
		parser__special__rafters_right();
	else if (g_line[*i] == '<')
		parser__special__rafters_left();
}

#else

void				parser__special(int *i, int *j)
{
	if (g_line[*i] == ';')
		parser__special__colon();
	else if (g_line[*i] == '|')
		parser__special__pipe();
	else if (g_line[*i] == '>' && g_line[*i + 1] == '>')
		parser__special__dblrafters_right();
	else if (g_line[*i] == '>')
		parser__special__rafters_right();
	else if (g_line[*i] == '<')
		parser__special__rafters_left();
	*j += 2;
}

#endif
