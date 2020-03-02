/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_arr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:37:27 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/02 21:03:54 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** JUST TO CONVERT THE LIST OF ARGS TO ARRAY
*/

char	**convert_to_arr(t_token *args, int ac)
{
	char	**av;
	t_token	*prev;
	int		i;

	av = (char **)mmalloc(sizeof(char *) * (ac + 1));
	i = 0;
	while (args)
	{
		av[i++] = args->value;
		prev = args;
		args = args->next;
	}
	av[i] = NULL;
	return (av);
}
