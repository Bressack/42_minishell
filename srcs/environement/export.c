/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 17:47:16 by fredrika          #+#    #+#             */
/*   Updated: 2020/02/25 00:18:03 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void	update_env(t_env *exists, char *val)
// {
// 	// int		i;
// 	//
// 	// i = -1;
// 	// while (exists->value[++i])
// 	// 	free(exists->value[i]);
// 	// free(exists->value);
//
//
// }

void	export(char *val)
{
	t_env	*trav;
	t_env	*new;
	int		i;

	trav = g_env;
	i = 0;
	while (val[i] && val[i] != '=')
		i++;
	while (trav && trav->next)
	{
		if (ft_strncmp(val, trav->name, i) == 0)
		{
			env_destructor(trav, 0);
			set_env(trav, val);
			return ;
		}
		trav = trav->next;
	}
	if (!(new = (t_env *)try_malloc(sizeof(t_env), _FL_)))
		return ;
	set_env(new, val);
	new->next = trav->next;
	trav->next = new;
}
