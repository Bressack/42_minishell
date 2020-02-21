/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 17:47:16 by fredrika          #+#    #+#             */
/*   Updated: 2020/02/21 18:27:28 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	export(char *val)
{
	t_env	*trav;
	t_env	*new;

	trav = g_env;
	while (trav && trav->next)
		trav = trav->next;
	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return ;
	set_env(new, val);
	new->next = trav->next;
	trav->next = new;
}
