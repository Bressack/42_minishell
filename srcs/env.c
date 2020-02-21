/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 01:47:33 by fredrika          #+#    #+#             */
/*   Updated: 2020/02/21 20:31:08 by fredrikalindh    ###   ########.fr       */
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
			ft_fprintf(1, "%s=%s", trav->name, trav->value[i++]);
		while (trav->value && trav->value[i])
			ft_fprintf(1, ":%s", trav->value[i++]);
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
	if (!(ret = (char *)malloc(i + 1)))
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
	if (!(e->value = (char **)malloc((c + 1) * sizeof(char *))))
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
		if (!(new = (t_env *)malloc(sizeof(t_env))))
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
		free(f->name);
		i = -1;
		while (f->value[++i])
			free(f->value[i]);
		free(f->value);
		if (flag == 1)
		{
			env_destructor(f->next, 1);
			free(f);
		}
	}
}
