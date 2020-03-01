/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:27:33 by fredrika          #+#    #+#             */
/*   Updated: 2020/02/27 20:46:04 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** SO BASICALLY A LIST REMOVE IF WITH EVERY ARGS
*/

int		unset(int ac, char **args)
{
	int		i;
	t_env	**indir;
	t_env	*f;

	i = 0;
	while (++i < ac)
	{
		indir = &g_env;
		while (*indir && ft_strcmp(args[i], (*indir)->name))
			indir = &(*indir)->next;
		if (*indir != NULL)
		{
			f = *indir;
			*indir = f->next;
			mfree(f->name);
			mfree(f->value);
			mfree(f);
		}
	}
	return (0);
}
