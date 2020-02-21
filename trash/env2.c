/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 01:47:33 by fredrika          #+#    #+#             */
/*   Updated: 2020/02/21 17:21:58 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <minishell.h>
#include "../includes/printf.h"
int	ft_strcmp(char *s1, char *s2);


/*
** So	export	=	list_push_back
** 		unset	=	list_remove_if
** 		env		=	print_env
*/

typedef struct	s_env
{
	char			*name;
	char			**value;
	struct s_env	*next;
}				t_env;

t_env	*g_env;

/*
** PRINTS ENV VARS, MEANING THE SAME AS ENV BUILT-IN
*/

void	print_env()
{
	t_env	*trav;
	int		i;

	trav = g_env;
	while (trav != NULL)
	{
		ft_fprintf(1, "%s=%s", trav->name, trav->value[0]);
		i = 0;
		while (trav->value && trav->value[++i])
			ft_fprintf(1, ":%s", trav->value[i]);
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
}

void	env_destructor(t_env *f)
{
	int		i;

	if (f)
	{
		free(f->name);
		i = -1;
		while (f->value[++i])
			free(f->value[i]);
		free(f->value);
		env_destructor(f->next);
		free(f);
	}
}

/*
** TEST TOMORROW
*/

int		main(int ac, char **av, char **env)
{
	get_env(ac, av, env);
	print_env();
	ft_fprintf(1, "PATH=%s\n", (ret_env("PATH"))[2]);
	ft_fprintf(1, "HOME=%s\n", *(ret_env("HOME")));
	env_destructor(g_env);
}
