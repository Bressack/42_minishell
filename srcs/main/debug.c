/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:07:14 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/31 01:17:24 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

void				debug_print_msg(char *f, int l, char *fmt, ...)
{
	char			*s;
	va_list			ap;

	va_start(ap, fmt);
	vasprintf(&s, fmt, ap);
	dprintf(2, ""C_G_RED"[ DEBUG ]"C_RES" ("C_G_MAGENTA"%20s"C_RES":"C_G_CYAN"%4d"C_RES") "C_G_WHITE"%s"C_RES"\n", f, l, s);
}

void				debug__print_data(void)
{
	dprintf(2, "info exp: (g_exp: %p)\n", g_exp);
	for (t_cmd *tmp = g_exp; tmp; tmp = tmp->next)
	{
		dprintf(2, "cmd: \'%s\'\n", tmp->name);
		for (t_arg *tmp2 = tmp->av_in; tmp2; tmp2 = tmp2->next)
		{
			dprintf(2, "     av_in : %s\n", tmp2->name);
		}
		for (t_arg *tmp2 = tmp->av; tmp2; tmp2 = tmp2->next)
		{
			dprintf(2, "     av    : %s\n", tmp2->name);
		}
		for (t_arg *tmp2 = tmp->av_out; tmp2; tmp2 = tmp2->next)
		{
			dprintf(2, "     av_out: %s\n", tmp2->name);
		}
	}

}
