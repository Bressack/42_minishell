/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node_end_np.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:28:23 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/26 23:04:03 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <double_linked.h>

void		ft_add_node_end_np(t_pnp **begin_list, t_pnp *new)
{
	t_pnp	*tmp;

	if (!(*begin_list))
		*begin_list = new;
	else
	{
		tmp = *begin_list;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	(*begin_list)->prev = new;
}
