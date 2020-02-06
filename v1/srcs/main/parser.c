/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:45:42 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/31 01:34:41 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

void				parser(void)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	debug_print_msg(_FL_, "Parser:");
	debug_print_msg(_FL_, "{");
	while (1)
	{
		if (!g_line || !g_line[i]) // end of g_line, loop break
			break ;
		pass_space(&i); // pass all spaces while isspace(g_line[i]) is true
		if (g_line[i] == '\\') // if backslash next char is a cmd or an arg
			parser__valid_char(&i, &j);
		if (g_line[i] == '\"' || g_line[i] == '\'') // strsub the string into quotes ["] will search next ["] and ['] will search next [']
			parser__quote(&i, &j);
		else if (ft_isspecial(&g_line[i])) // & or | or ; or > or < // special effect
			parser__special(&i, &j);
		else
			parser__valid_char(&i, &j);
		i = j;
	}
	debug_print_msg(_FL_, "}");
}

void				preparser(int prompt)
{
	char			*str;
	char			*tmp;

	print_prompt(prompt);
	get_next_line(0, &str);
	if (str && ft_strlen(str))
	{
		tmp = ft_strjoin(2, g_line, str);
		try_free_((void **)&g_line, _FL_);
		g_line = tmp;
	}
	try_free_((void **)&str, _FL_);
}
