/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 01:47:33 by fredrika          #+#    #+#             */
/*   Updated: 2020/02/22 00:42:04 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** PRINTS ENV VARS, MEANING THE SAME AS ENV BUILT-IN
*/

void	print_env()
{
	t_env	*trav;
	int		i;

	trav = g_env;
	while (trav)
	{
		i = 0;
		if (trav->value && trav->value[i])
			ft_dprintf(1, "%s=%s", trav->name, trav->value[i++]);
		while (trav->value && trav->value[i])
			ft_dprintf(1, ":%s", trav->value[i++]);
		write(1, "\n", 1);
		trav = trav->next;
	}
}

/*
** FINDS AND RETURNS VALUE WITH 'NAME'
*/

char	**ret_env(char *name)
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

char	*ft_copsep(char **e, char sep)
{
	int		i;
	char	*ret;

	i = 0;
	while (e && e[0][i] && e[0][i] != sep)
		i++;
	if (!(ret = (char *)try_malloc(i + 1, _FL_)))
		return (NULL);
	i = 0;
	while (*e && **e && **e != sep)
		ret[i++] = *((*e)++);
	ret[i] = '\0';
	if (**e == sep)
		(*e)++;
	return (ret);
}

/*
** SET ENV SETS NAME AND ARRAY OF VALUES SEP BY :
*/

void	set_env(t_env *e, char *env)
{
	int		i;
	int		c;

	i = -1;
	c = 0;
	while (env && env[++i])
		if (env[i] == '=' || env[i] == ':')
			c++;
	e->name = ft_copsep(&env, '=');
	if (!(e->value = (char **)try_malloc((c + 1) * sizeof(char *), _FL_)))
		return ;
	i = 0;
	while (env && *env && i < c)
		e->value[i++] = ft_copsep(&env, ':');
	e->value[i] = NULL;
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
	prev = NULL;
	while (env && env[++i])
	{
		if (!(new = (t_env *)try_malloc(sizeof(t_env), _FL_)))
			break ;
		set_env(new, env[i]);
		if (prev == NULL && (new->next = NULL) == NULL) // must be more elegant way?
			g_env = new;
		else
			prev->next = new;
		prev = new;
	}
	// export(ft_strcat("SHELL=", ft_strcat(*ret_env("PWD"), "minishell"))); //pwd
}

void	env_destructor(t_env *f, int flag)
{
	int		i;

	if (f)
	{
		try_free_(f->name, _FL_);
		i = -1;
		while (f->value[++i])
			try_free_(f->value[i], _FL_);
		try_free_(f->value, _FL_);
		if (flag == 1)
		{
			env_destructor(f->next, 1);
			try_free_(f, _FL_);
		}
	}
}
