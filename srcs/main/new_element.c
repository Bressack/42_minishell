/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 16:04:51 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/30 16:05:29 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

void				add_new_arg(char *data, int type, va_list ap)
{
	t_arg			*new;

	new = try_malloc(sizeof(t_arg), _FL_);
	new->name = data;
	new->isquote = va_arg(ap, int);
	new->quote_state = va_arg(ap, int);
	if (type == ISARG_IN)
	{
		ft_add_node_end_np((t_pnp **)(&g_av_in), (t_pnp *)new);
		!new ? g_last_cmd->av_in = new : 0;
	}
	else if (type == ISARG_OUT)
	{
		ft_add_node_end_np((t_pnp **)(&g_av_out), (t_pnp *)new);
		!new ? g_last_cmd->av_out = new : 0;
	}
	else
	{
		ft_add_node_end_np((t_pnp **)(&g_av), (t_pnp *)new);
		!new ? g_last_cmd->av = new : 0;
	}
	g_last_arg = new;
}

void				add_new_cmd(char *data, va_list ap)
{
	t_cmd			*new;

	new = try_malloc(sizeof(t_cmd), _FL_);
	new->name = data;
	new->fd_in = FD_STDIN;
	new->fd_out = FD_STDOUT;
	new->av_in = g_av_in;
	new->av_out = g_av_out;
	new->av = g_av;
	new->isquote = va_arg(ap, int);
	new->quote_state = va_arg(ap, int);
	ft_add_node_end_np((t_pnp **)&g_exp, (t_pnp *)new);
	g_last_cmd = new;
}

void				new_element(char *data, int type, ...)
{
	va_list			ap;

	va_start(ap, type);
	if (type == ISARG)
		add_new_arg(data, ISARG, ap);
	else if (type == ISARG_IN)
		add_new_arg(data, ISARG_IN, ap);
	else if (type == ISARG_OUT)
		add_new_arg(data, ISARG_OUT, ap);
	else if (type == ISCMD)
		add_new_cmd(data, ap);
}
