/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node_end_np.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:28:23 by tharchen          #+#    #+#             */
/*   Updated: 2020/02/28 17:47:34 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <double_linked.h>

void		ft_add_node_end_np(t_pnp **begin_list, t_pnp *new)
{
	t_pnp	*tmp;

	new = new->next;
	// t_token	*new_t = (t_token *)new;
	// t_token	*begin_list_t = (t_token *)*begin_list;
	//
	// printf(""C_G_YELLOW"new        : %p -> %p -> %p\n"C_RES,
	// new_t ? new_t->prev : NULL,
	// new_t,
	// new_t ? new_t->next : NULL);
	//
	// printf(""C_G_YELLOW"new        : %s -> %s -> %s\n"C_RES,
	// new_t && new_t->prev ? new_t->prev->value : NULL,
	// new_t->value,
	// new_t && new_t->next ? new_t->next->value : NULL);
	//
	// new_t = new_t->next;
	// printf(""C_G_YELLOW"new        : %s -> %s -> %s\n"C_RES,
	// new_t && new_t->prev ? new_t->prev->value : NULL,
	// new_t->value,
	// new_t && new_t->next ? new_t->next->value : NULL);
	//
	// printf("begin_list : %p -> %p -> %p\n",
	// begin_list_t ? begin_list_t->prev : NULL,
	// begin_list_t,
	// begin_list_t ? begin_list_t->next : NULL);

	if (!(*begin_list))
	{
		printf(TEST);
		*begin_list = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		printf(TEST);
		tmp = *begin_list;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	printf(""C_G_RED"LIST ARG:"C_RES" ");
	for (t_token *tmp2 = (t_token *)*begin_list ; tmp2 ; tmp2 = tmp2->next)
		printf("[%s]", tmp2->value);
	printf("\n");
}
