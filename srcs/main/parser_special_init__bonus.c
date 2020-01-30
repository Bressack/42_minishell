/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special_init__bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:49:02 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/30 14:58:52 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

void				parser__special__colon(void)
{
	g_last_cmd->link = LINK_COLON;
	cmd_stop(ISCMD);
}

#ifdef BONUS

void				parser__special__dbland(void)
{
	g_last_cmd->link = LINK_AND;
	cmd_stop(ISCMD);
}

void				parser__special__and(void)
{
	g_last_cmd->link = LINK_THREAD;
	cmd_stop(ISCMD);
}

void				parser__special__dblor(void)
{
	g_last_cmd->link = LINK_OR;
	cmd_stop(ISCMD);
}

void				parser__special__dblrafters_left(void)
{
	g_last_cmd->link = REDIR_DBLLEFT;
	g_needling = ISARG_RAFTER;
}
#endif
