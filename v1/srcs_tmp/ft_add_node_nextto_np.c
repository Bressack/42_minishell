/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node_nextto_np.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 14:40:32 by tharchen          #+#    #+#             */
/*   Updated: 2019/11/17 14:56:25 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

void		ft_add_node_nextto_np(t_pnp *prev, t_pnp *new)
{
	new->next = prev->next;
	new->prev = prev;
	prev->next->prev = new;
	prev->next = new;
}
