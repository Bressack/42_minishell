/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 01:47:33 by fredrika          #+#    #+#             */
/*   Updated: 2020/02/21 02:41:50 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <minishell.h>

/*
** So	export	=	list_push_back
** 		unset	=	list_remove_if
** 		env		=	print_env
*/

typedef struct	s_env
{
	const char		*name;
	char			*value;
	struct s_env	*next;
}				t_env;

t_env	*g_env;

void	print_env()
{
	t_env *trav;

	trav = g_env;
	while (trav)
	{
		ft_fprintf(1, "%s=%s", trav->name, trav->value);
		while (++trav->value)
			ft_fprintf(1, ":%s", trav->value);
		trav = trav->next;
	}
}

char	**ret_env(const char *name)
{
	t_env *trav;

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
	while (e && e[0][i] && e[0][i] != '\n' && e[0][i] != sep)
		i++;
	if (!(ret = (char *)malloc(i + 1)))
		return (NULL);
	i = 0;
	while (e && **e && **e != '\n' && **e != sep)
		ret[i++] = *((*e)++);
	ret[i] = '\0';
	return (ret);
}

void	set_env(t_env *e, char *env)
{
	int		i;
	int		c;

	i = -1;
	c = 0;
	while (env && env[++i] && env[i] != '\n')
		if (env[i] == '=' || env[i] == ':')
			c++;
	t_env->name = ft_copsep(&env, '=');
	if (!(t_env->value = (char **)malloc(sizeof(char *) * c)))
		return ;
	i = 0;
	while (env && *env)
		t_env->value[i++] = ft_copsep(&env, ':');
	t_env->value[i] = NULL;
}

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
			return ;
		set_env(new, env[i]);
		if (prev == NULL) // must be more elegant way?
			g_env = new;
		else
			prev->next = new;
		prev = new;
	}
}

void	env_destructor()
{
	if (g_env)
	{
		free(g_env->name);
		while (g_env->value)
			free(*g_env->value++)
		free(g_env->value)
	}
	env_destructor(g_env->next);
	free(g_env);
}

/*
** TEST TOMORROW
*/

int		main(int ac, char **av, char **env)
{
	get_env(ac, av, env);
	print_env();
}
