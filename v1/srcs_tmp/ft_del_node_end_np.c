/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_node_end_np.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:39:11 by tharchen          #+#    #+#             */
/*   Updated: 2019/11/29 15:49:41 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

void		ft_del_node_end_np(t_pnp **begin_list, void (*f)(t_pnp *curr))
{
	t_pnp	*tmp;

	tmp = *begin_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (tmp != *begin_list)
		tmp->prev->next = NULL;
	if (f)
		f(tmp);
	try_free_((void **)&tmp, _FL_);
}
