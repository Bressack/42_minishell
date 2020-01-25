/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_list_np.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 19:19:19 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/25 19:22:45 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

void		ft_del_list_np(t_pnp **begin_list, void (*f)(t_pnp *curr))
{
	t_pnp	*tmp;
	t_pnp	*next;

	if (!f || !begin_list || !(*begin_list))
		return ;
	tmp = *begin_list;
	while (tmp)
	{
		next = tmp->next;
		f(tmp);
		try_free_(tmp);
		tmp = next;
	}
	*begin_list = NULL;
}
