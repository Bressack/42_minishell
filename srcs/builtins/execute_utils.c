/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 21:49:21 by fredrika          #+#    #+#             */
/*   Updated: 2020/03/12 18:16:32 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** PUTS THE ENVIRONMENT VARS IN A CHAR ARRAR TO PASS ON TO FUNCTIONS.
*/

char	**env_to_arr(t_env *trav)
{
	int		size;
	char	**env;

	size = 0;
	while (trav && ++size != -1)
		trav = trav->next;
	if (!(env = (char **)mmalloc(sizeof(char *) * (size + 2))))
		return (NULL);
	trav = g_env;
	size = 0;
	while (trav)
	{
		if (trav->export && (env[size] =
		(char *)mmalloc(ft_strlen(trav->name) + ft_strlen(trav->value) + 1)))
			env[size++] = cat_value(trav->name, '=', trav->value);
		trav = trav->next;
	}
	env[size] = NULL;
	return (env);
}

void	sig_exec(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		g_exit = 130;
	}
	if (signo == SIGQUIT)
	{
		ft_dprintf(2, "Quit: 3\n");
		g_exit = 131;
	}
}

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
