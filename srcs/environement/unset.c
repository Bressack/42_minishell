/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:27:33 by fredrika          #+#    #+#             */
/*   Updated: 2020/02/21 19:38:24 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	unset(char *name)
{
	t_env	**indir;
	t_env	*f;
	int		i;

	indir = &g_env;
	while (*indir && ft_strcmp(name, (*indir)->name))
		indir = &(*indir)->next;
	if (*indir == NULL)
		return ;
	f = *indir;
	*indir = f->next;
	free(f->name);
	i = -1;
	while (f->value[++i])
		free(f->value[i]);
	free(f->value);
	free(f);
}