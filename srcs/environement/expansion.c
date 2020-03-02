/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 15:17:15 by frlindh           #+#    #+#             */
/*   Updated: 2020/03/02 19:21:52 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** ALLOWED CHARACTERS TO FOLLOW A $. MIGHT BE BETTER CHANGING TO JUST
** ALLOWED CHARACTERS IN VARIABLE + ?
*/

int		ok_envchar(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' ||
			(c >= '0' && c <= '9') || c == '@' || c == '*' || c == '#' ||
			c == '-' || c == '!' || c == '{' || c == '(');
}

int		tilde_exp(char *new)
{
	char	*home;
	int		i;

	home = ret_envval("HOME");
	i = 0;
	if (!home)
		new[i++] = '~';
	while (home && *home)
		new[i++] = *home++;
	return (i);
}

int		expand_env(char **args, char *new)
{
	t_env	*trav;
	int		i;
	int		curl;
	char	name[LINE_MAX];

	trav = g_env;
	i = -1;
	curl = 0;
	while ((*args)[++i] && (ok_envchar((*args)[i]) || (*args)[i] == '}'))
		if ((*args)[i] == '{' || (*args)[i] == '}')
			curl = ((*args)[i] == '{') ? curl + 1 : curl - 1;
	(**args == '{' && curl == 0) ? (*args)++ : 0;
	i = 0;
	while (**args && ok_envchar(**args))
		name[i++] = *((*args)++);
	(**args == '}' && curl == 0) ? (*args)++ : 0;
	name[i] = '\0';
	while (trav && ft_strcmp(name, trav->name) != 0)
		trav = trav->next;
	i = 0;
	if (trav && trav->value && (i = -1) == -1)
		while (trav->value[++i])
			new[i] = trav->value[i];
	return (i);
}

int		spec_char(char c)
{
	return (c == '\\' || c == '$' || c == '\"' || c == '`');
}

char	*expand_qt(char *args)
{
	int		quote;
	int		j;
	char	new[LINE_MAX];

	quote = 0;
	j = 0;
	while (args && *args)
	{
		if (quote == 0 && *args == '\'')
			while (args++ && *args && *args != '\'')
				new[j++] = *args;
		else if (*args == '$' && ok_envchar(*(args + 1)) && args++)
			j += expand_env(&args, &new[j]);
		else if (*args == '\"' && args++)
			quote = (quote == 0) ? *args : 0;
		else if (*args == '\\' &&
		(((quote == 0 || spec_char(*(args + 1))) && args++) || 1))
			new[j++] = *args++;
		else if (quote == 0 && *args == '~' && args++)
			j += tilde_exp(&new[j]);
		else
			new[j++] = *args++;
	}
	new[j] = '\0';
	// mfree(args);
	return (j > 0) ? (ft_strdup(new)) : NULL;
}

void	expand_split_env(t_token **args, int *ac)
{
	t_token	*next;
	char	**arr;
	char	*ifs;
	int		i;

	if (!((*args)->value = expand_qt((*args)->value)))
	{
		*args = (*args)->next;
		return ;
	}
	ifs = ret_envval("IFS");
	arr = ifs ? ft_split((*args)->value, ifs) : ft_split((*args)->value, IFS);
	if (!(*arr) && (*args = ((*args)->next)))
		return ;
	(*args)->value = arr[0];
	next = (*args)->next;
	i = 0;
	while (*ac++ != -1 && arr[++i])
	{
		(*args)->next = (t_token *)mmalloc(sizeof(t_token));
		((*args)->next)->value = arr[i];
		args = &((*args)->next);
	}
	(*args)->next = next;
}

int		expand(t_token **args)
{
	int	ac;

	ac = 0;
	while (*args)
	{
		if ((*args)->value[0] == '$' && ok_envchar((*args)->value[1]))
			expand_split_env(args, &ac);
		else if (++ac != -1)
		{
			(*args)->value = expand_qt((*args)->value);
			args = &((*args)->next);
		}
	}
	return (ac);
}
