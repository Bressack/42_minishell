/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:27:33 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/07 16:06:00 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		is_valid_variable(char *args, int flag)
{
	int i;

	i = -1;
	if (!(is_letter(args[0])) && args[0] != '_')
		return (0);
	while (args[++i] && (flag == 0 || (args[i] != '=' &&
	!(args[i] == '+' && args[i + 1] == '='))))
		if (!(is_letter(args[i])) && args[i] != '_' && !(is_num(args[i])))
			return (0);
	if (flag == 2 && args[i] != '=')
		return (0);
	return (1);
}

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
