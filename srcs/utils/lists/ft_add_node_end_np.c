/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node_end_np.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:28:23 by tharchen          #+#    #+#             */
/*   Updated: 2020/03/01 13:37:01 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <double_linked.h>

void		ft_add_node_end_np(t_pnp **begin_list, t_pnp *new)
{
	t_pnp	*tmp;

	if (!(*begin_list))
	{
		*begin_list = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		tmp = *begin_list;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	// printf(""C_G_GRAY"\n*********************************************************************************\n"C_G_RED"LIST ARG:"C_RES" ");
	// for (t_token *tmp2 = (t_token *)*begin_list ; tmp2 ; tmp2 = tmp2->next)
	// 	printf("[%s]", tmp2->value);
	// printf("\n");
}
