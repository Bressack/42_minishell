/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:06:47 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/02 20:42:05 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*g_env = NULL;

/*
** ENV BUILTIN
*/
int		print_env(int ac, char **args)
{
	t_env	*trav;

	(void)args;
	if (ac > 1)
		return (bi_error(args[0], NULL, "too many arguments", 0));
	trav = g_env;
	while (trav != NULL)
	{
		if (trav->value != NULL && trav->export == 1)
			ft_dprintf(1, "%s=%s\n", trav->name, trav->value);
		trav = trav->next;
	}
	return (0);
}

/*
** FUNCTIONS THAT RETURN AN ENV VARIABLE.
** 1. Returns full structure 2. Returns just the value
*/
t_env	*ret_env(char *name)
{
	t_env	*trav;

	trav = g_env;
	while (trav)
	{
		if (ft_strcmp(name, trav->name) == 0)
			return (trav);
		trav = trav->next;
	}
	return (NULL);
}

char	*ret_envval(char *name)
{
	t_env	*trav;

	trav = g_env;
	while (trav)
	{
		if (ft_strcmp(name, trav->name) == 0)
			return (trav->value);
		trav = trav->next;
	}
	return (NULL);
}

void	set_env(t_env *e, char *env)
{
	int		i;
	int		c;

	i = 0;
	while (env && env[i] && env[i] != '=')
		i++;
	if (!(e->name = (char *)mmalloc(i + 1)))
		return ;
	i = -1;
	while (env && env[++i] && env[i] != '=')
		e->name[i] = env[i];
	c = 0;
	while (env && env[i + c])
		c++;
	if (!(e->value = (char *)mmalloc(c + 1)))
		return ;
	c = 0;
	while (env && env[++i])
		e->value[c++] = env[i];
	e->export = 1;
}

/*
** START OF PUTTING ENVS INTO LINKED LIST, CALLS set_env for
** each element in the char array.
*/

void	get_env(int ac, char **av, char **env)
{
	t_env	*new;
	t_env	*prev;
	int		i;

	(void)ac;
	(void)av;
	i = -1;
	g_env = NULL;
	while (env && env[++i])
	{
		if (!(new = (t_env *)mmalloc(sizeof(t_env))))
			break ;
		set_env(new, env[i]);
		if (g_env == NULL && (new->next = NULL) == NULL)
			g_env = new;
		else
			prev->next = new;
		prev = new;
	}
}
