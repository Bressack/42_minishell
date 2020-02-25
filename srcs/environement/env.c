/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:06:47 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/25 14:13:05 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** SET ENV SETS NAME AND ARRAY OF VALUES SEP BY :
*/

void	print_env(char *val)
{
	t_env	*trav;
	(void)val;

	trav = g_env;
	while (trav != NULL)
	{
		if (trav->value != NULL)
			ft_dprintf(1, "%s=%s\n", trav->name, trav->value);
		trav = trav->next;
	}
}

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

void	set_env(t_env *e, char *env)
{
	int		i;
	int		c;

	i = 0;
	while (env && env[i] && env[i] != '=')
		i++;
	if (!(e->name = (char *)malloc(i + 1)))
		return ;
	i = -1;
	while (env && env[++i] && env[i] != '=')
		e->name[i] = env[i];
	e->name[i] = '\0';
	c = 0;
	while (env && env[i + c])
		c++;
	if (!(e->value = (char *)malloc(c + 1)))
		return ;
	c = 0;
	while (env && env[++i])
		e->value[c++] = env[i];
	e->value[c] = '\0';
}

/*
** START OF PUTTING ENVS INTO LINKED LIST, CALLS set_env for each element in the char array.
*/

void	get_env(int ac, char **av, char **env)
{
	t_env	*new;
	t_env	*prev;
	int		i;
	(void)	ac;
	(void)	av;

	i = -1;
	g_env = NULL;
	while (env && env[++i])
	{
		if (!(new = (t_env *)malloc(sizeof(t_env))))
			break ;
		set_env(new, env[i]);
		if (g_env == NULL && (new->next = NULL) == NULL)
			g_env = new;
		else
			prev->next = new;
		prev = new;
	}
	// export(ft_strcat("SHELL=", ft_strcat(*ret_env("PWD"), "minishell"))); //pwd
}
