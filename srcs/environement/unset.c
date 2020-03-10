/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:27:33 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/10 21:58:55 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** SO BASICALLY A LIST REMOVE IF WITH EVERY ARGS
*/

int		unset(int ac, char **args, int out)
{
	int		i;
	t_env	**indir;
	t_env	*f;

	i = 0;
	out = 0;
	while (++i < ac)
	{
		indir = &g_env;
		if (!is_valid_variable(args[i], 0))
		{
			out = bi_error(args[0], args[i], "not a valid identifier", 1);
			continue ;
		}
		while (*indir && ft_strcmp(args[i], (*indir)->name))
			indir = &(*indir)->next;
		if (*indir != NULL && (f = *indir))
		{
			*indir = f->next;
			mfree((void **)&f->name);
			mfree((void **)&f->value);
			mfree((void **)&f);
		}
	}
	return (0);
}
