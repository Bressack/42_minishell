/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:49:44 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/30 14:58:01 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

void				parser__special__pipe(void)
{
	g_last_cmd->link = LINK_PIPE;
	cmd_stop(ISCMD);
}

void				parser__special__dblrafters_right(void)
{
	g_last_cmd->open_flags = O_WRONLY | O_CREAT;
	g_last_cmd->open_flags_rights = OPEN__FLAG_O_CREAT__RIGHTS;
	g_needling = ISARG_OUT;
}

void				parser__special__rafters_right(void)
{
	g_last_cmd->open_flags = O_WRONLY | O_CREAT | O_TRUNC;
	g_last_cmd->open_flags_rights = OPEN__FLAG_O_CREAT__RIGHTS;
	g_needling = ISARG_OUT;
}

void				parser__special__rafters_left(void)
{
	g_last_cmd->open_flags = O_RDONLY;
	g_needling = ISARG_IN;
}
