/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:27:33 by fredrika          #+#    #+#             */
/*   Updated: 2020/02/25 00:14:45 by tharchen         ###   ########.fr       */
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
	try_free_((void **)&f->name, _FL_);
	i = -1;
	while (f->value[++i])
		try_free_((void **)&f->value[i], _FL_);
	try_free_((void **)&f->value, _FL_);
	try_free_((void **)&f, _FL_);
}
