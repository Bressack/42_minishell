/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f__del_list_np.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:59:49 by tharchen          #+#    #+#             */
/*   Updated: 2020/01/30 16:00:06 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ms.h>

void				__f__ft_del_node_np__t_arg__(t_pnp *a)
{
	try_free_((void **)&((t_arg *)a)->name, _FL_);
}

void				__f__ft_del_node_np__t_cmd__(t_pnp *a)
{
	try_free_((void **)&((t_arg *)a)->name, _FL_);
	ft_del_list_np((t_pnp **)&((t_cmd *)a)->av, __f__ft_del_node_np__t_arg__);
}
