/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach_node_f_np.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:57:26 by tharchen          #+#    #+#             */
/*   Updated: 2019/11/17 14:56:25 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

void		ft_foreach_node_f_np(t_pnp **begin_list, int (*f)(t_pnp *curr))
{
	t_pnp	*tmp;

	tmp = *begin_list;
	while (tmp->next)
	{
		f(tmp);
		tmp = tmp->next;
	}
}
